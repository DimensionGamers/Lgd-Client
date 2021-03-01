PlayerCustomData g_PlayerCustomData;

uint32 UpdateThreadTime = 0;

CrownSwitchData g_CrownSwitchData[2];
bool CastleSiegeMiniMap = false;

void DebugLog(const char * file, const char * msg, ...)
{
	FILE* fp = fopen(file, "a+");

	if (fp)
	{
		char DEST[2048];
		memset(DEST, 0, sizeof(DEST));
		va_list pArguments;
		va_start(pArguments, msg);
		vsprintf_s(DEST, msg, pArguments);
		va_end(pArguments);

		fprintf(fp, "%s \n", DEST);
		fclose(fp);
	}
}

int CheckIntegrity()
{
	return 1;
}

void InitCommon()
{
	ResetCrownSwitchData();

	g_PlayerCustomData.Reset();

	SetCompleteHook(0xE8, MAIN_OFFSET_SIEGE_SWITCH_HOOK, &PrintCrownSwitchData);

	for ( int i = 0; MainOffsetSiegeSwitchClear[i] != 0; ++i )
	{
		SetCompleteHook(0xE8, MainOffsetSiegeSwitchClear[i], &ClearCrownSwitchData);
	}

	for ( int i = 0; MainOffsetCheckIntegrity[i] != 0; ++i )
	{
		SetCompleteHook(0xE8, MainOffsetCheckIntegrity[i], &CheckIntegrity);
	}

	SetCompleteHook(0xE9, MAIN_OFFSET_PARTY_PK_HOOK, &PartyPK);

	SetCompleteHook(0xE8, MAIN_OFFSET_INIT_WINDOW_HOOK, (DWORD)&InitWindow);

	//SetCompleteHook(0xE9, MAIN_OFFSET_WELCOME_TO_WORLD_HOOK_1, &WelcomeToWorld1);
	SetCompleteHook(0xE9, MAIN_OFFSET_WELCOME_TO_WORLD_HOOK_2, &WelcomeToWorld2);

	//SetCompleteHook(0xE9, MAIN_OFFSET_LOAD_TEXTURE_HOOK, &LoadTextureHook);
	//SetCompleteHook(0xE9, MAIN_OFFSET_DRAW_TEXTURE_HOOK, &DrawTextureHook);
	
	SetCompleteHook(0xE8, MAIN_OFFSET_MAIN_LOOP_INIT_HOOK, (DWORD)&UpdateThread);
}

void FixPerformance()
{
	static DWORD TickCount = GetTickCount();

	if ( (GetTickCount() - TickCount) > 10000 )
	{
		TickCount = GetTickCount();

		SetProcessWorkingSetSize(GetCurrentProcess(), 0xFFFFFFFF, 0xFFFFFFFF);
		SetThreadPriority(GetCurrentProcess(), -2);
	}
}

#include <Rpc.h>
#pragma comment(lib, "Rpcrt4")

void GetMac(char* mac)
{
	memset(mac, 0, 17);

	UUID uuid;
	UuidCreateSequential(&uuid);    // Ask OS to create UUID

	sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X",
		uuid.Data4[2],uuid.Data4[3],uuid.Data4[4],
		uuid.Data4[5],uuid.Data4[6],uuid.Data4[7]);
}

DWORD GetMachineID()
{
    DWORD dwSerial = 0;
    BOOL success = GetVolumeInformation(LPCTSTR("C:\\"), NULL, 255, &dwSerial, NULL, NULL, NULL, 255);

    if ( !success )
	{
		dwSerial = 0;
    }

    return dwSerial;
}

void FixDataSend(BYTE * Source, BYTE * Dest, DWORD & Len)
{
	if ( Source[0] == 0xC3 )
	{
		Source[0] = 0xC1;
	}

	if ( Source[0] == 0xC4 )
	{
		Source[0] = 0xC2;
	}

	BYTE headcode = GET_HEADCODE(Source);

	if ( headcode == 0xF4 )
	{
		memcpy(Dest, Source, Len);
	}
	else
	{
		if( Source[0] == 0xC1 || Source[0] == 0xC3 )
		{
			Len = Source[1];
		}
		else if( Source[0] == 0xC2 || Source[0] == 0xC4 )
		{
			Len = Source[1] * 256;
			Len |= Source[2];
		}

		BYTE EncBuff[8192];
		memcpy(EncBuff, Source, Len);

		muPacket* Recv = (muPacket*)EncBuff;
		MU_DecodeC1C2(Recv);

		memcpy(EncBuff, Recv, Len);

		BYTE pct_headcode = GET_HEADCODE(EncBuff);
		BYTE pct_subcode = GET_SUBCODE(EncBuff);

		PBMSG_HEAD* lpHead = (PBMSG_HEAD*)EncBuff;

		switch ( pct_headcode )
		{
		case 0xF1:
			{
				switch ( pct_subcode )
				{
				case 0x01:
					{
						LOGIN_REQUEST * lpMsg = (LOGIN_REQUEST*)EncBuff;
						lpMsg->h.size = sizeof(LOGIN_REQUEST);
						memset(lpMsg->mac, 0, 18);
						GetMac(lpMsg->mac);
						lpMsg->disk_serial = GetMachineID();
						memcpy(lpMsg->client_serial, ClientSerial, 16);

						g_Reconnect.SetData(lpMsg->account, lpMsg->password);

						Len = sizeof(LOGIN_REQUEST);
					} break;
				}
			} break;

		case 0xF3:
			{
				switch ( pct_subcode )
				{
				case 0x03:
					{
						CHARACTER_SELECT_REQUEST * lpMsg = (CHARACTER_SELECT_REQUEST*)EncBuff;

						memcpy(g_Reconnect.CharacterName, lpMsg->character_name, 10);
						g_Reconnect.CharacterIndex = lpMsg->index;
					} break;
				}
			} break;

		case 0xB1:
			{
				switch ( pct_subcode )
				{
				case 0x01:
					{
						SERVER_CHANGE_AUTH * lpMsg = (SERVER_CHANGE_AUTH*)EncBuff;
						lpMsg->h.size = sizeof(SERVER_CHANGE_AUTH);
						memset(lpMsg->account, 0, 12);
						memset(lpMsg->name, 0, 12);
						memcpy(lpMsg->serial, ClientSerial, 16);
						lpMsg->auth[0] = g_Reconnect.ServerMoveAuth[0];
						lpMsg->auth[1] = g_Reconnect.ServerMoveAuth[1];
						lpMsg->auth[2] = g_Reconnect.ServerMoveAuth[2];
						lpMsg->auth[3] = g_Reconnect.ServerMoveAuth[3];

						PacketArgumentEncrypt(lpMsg->account, g_Reconnect.Account, 10);

						memcpy(lpMsg->name, g_Reconnect.CharacterName, 10);

						Len = sizeof(SERVER_CHANGE_AUTH);
					} break;
				}
			} break;

		case 0xD7:
		case 0xD3:
		//case 0x4A:
		case 0x4B:
			{
				if ( g_PlayerCustomData.FixSpeed() )
				{
					Len = 0;
					return;
				}
			} break;

		case 0x19:
		case 0x1E:
		case 0xDF:
			{
				if ( g_PlayerCustomData.FixSpeed() )
				{
					Len = 0;
					return;
				}

				if(!g_AntiCheat.IsSkillBindKeyAllowed(4))
				{
					Len = 0;
					return;
				}

				uint32 add_time = getMSTimeMain();
				memcpy(&EncBuff[Len], &add_time, 4);
				Len += 4;

				PBMSG_HEAD* pHead =(PBMSG_HEAD*)EncBuff;
				pHead->size += 4;
			} break;
		}

		muPacket* pointer = (muPacket*)&EncBuff;
		MU_EncodeC1C2(pointer);

		if ( !g_EncodeDecode.Encode((BYTE*)pointer, Dest, Len) )
		{
			Len = 0;	
		}
	}
}

BOOL DataSendHOOK(BYTE * Packet, DWORD Len)
{
	BYTE SendPacket[8192];

	FixDataSend(Packet, SendPacket, Len);

	if ( !Len )
	{
		return 1;
	}

	DataSendASM(SendPacket, Len);

	return 1;
}

void DataSendASM(BYTE * Packet, DWORD Len)
{
	static DWORD DataSendCall = MAIN_OFFSET_DATASEND;

	_asm
	{
		PUSH Len
		PUSH DWORD PTR SS:[Packet]
		MOV ECX,DWORD PTR DS:[MAIN_OFFSET_DATASEND_POINTER]
		CALL [DataSendCall]
	}
}

bool CheckSocketPort(SOCKET s)
{
	SOCKADDR_IN addr;
	int addr_len = sizeof(addr);

	if(getpeername(s,(SOCKADDR*)&addr,&addr_len) == SOCKET_ERROR)
	{
		return false;
	}

	if( ntohs(addr.sin_port) == 0 )
	{
		return false;
	}

	return true;
}

void CloseSocket()
{
	static DWORD CloseSocketCall = MAIN_OFFSET_CLOSE_SOCKET_CALL;

	_asm
	{
		Mov Ecx, MAIN_OFFSET_CLOSE_SOCKET_POINTER
		Call [CloseSocketCall]
	}
}

__declspec(naked) void PartyPK()
{
	static DWORD PartyPKJMP = MAIN_OFFSET_PARTY_PK_JMP;

	_asm
	{
		Jmp [PartyPKJMP]
	}
}

__declspec(naked) void WelcomeToWorld1()
{
	static const DWORD WelcomeToWorldJUMP = MAIN_OFFSET_WELCOME_TO_WORLD_JUMP_1;
	static char * Text;
	
	_asm
	{
		Lea Eax, Dword Ptr Ss:[Ebp - MAIN_OFFSET_WELCOME_TO_WORLD_DATA_1_2]
		Mov Text, Eax
	}

	sprintf(Text, "%s%s", GetTextBMD(484), WzGetWorldName(*(DWORD*)MAIN_CHARACTER_MAP));

	_asm
	{
		Jmp [WelcomeToWorldJUMP]
	}
}

__declspec(naked) void WelcomeToWorld2()
{
	static const DWORD WelcomeToWorldJUMP = MAIN_OFFSET_WELCOME_TO_WORLD_JUMP_2;
	static char * Text;
	
	_asm
	{
		Lea Eax, Dword Ptr Ss:[Ebp - MAIN_OFFSET_WELCOME_TO_WORLD_DATA_2_2]
		Mov Text, Eax
	}
	
	sprintf(Text, "%s%s", GetTextBMD(484), WzGetWorldName(*(DWORD*)MAIN_CHARACTER_MAP));

	_asm
	{
		Jmp [WelcomeToWorldJUMP]
	}
}

bool ventanaVisible = true;
HANDLE hThread = NULL;
HINSTANCE gInstance = NULL;
HWND gHWND = NULL;

void UpdateThread()
{
	((void(*)())MAIN_OFFSET_MAIN_LOOP_INIT_CALL)();

	UpdateThreadTime = getMSTimeMain();

	MainLoopInit();

	if (GetMainState() == MAIN_STATE_PLAYING)
	{
		if ( CC_MAP_RANGE() )
		{
			sInputOutput.render_fix_1 = false;
			SetByte(MAIN_OFFSET_RENDER_MONSTERS, 0x55); // Render Monsters
		}

		if (IsIconic(gHWND))
		{
			FixPerformance();

			if (ventanaVisible) 
			{
				SetByte(MAIN_OFFSET_PLAY_RENDER, MAIN_STATE_DESTROY);
				ventanaVisible = false;

				CLIENT_MINIMIZE pMsg(1);
				DataSend((BYTE*)&pMsg, pMsg.h.size);
			}
		}
		else
		{
			if (ventanaVisible == false)
			{
				SetByte(MAIN_OFFSET_PLAY_RENDER, MAIN_STATE_PLAYING);
				ventanaVisible = true;

				CLIENT_MINIMIZE pMsg(0);
				DataSend((BYTE*)&pMsg, pMsg.h.size);
			}
		}

		CGAttackSpeed();

		g_AntiCheat.UpdateOffsetMap();

		static DWORD print_zoom = GetTickCount();

		if((GetTickCount() - print_zoom) > 1000)
		{
			print_zoom = GetTickCount();

			if(*(float*)MAIN_OFFSET_ZOOM != 1000.0f)
			{
				CGHackCheckDoubleModified(MAIN_OFFSET_ZOOM, *(float*)MAIN_OFFSET_ZOOM);
			}
		}
	}
	else
	{
		if(!ventanaVisible)
		{
			SetByte(MAIN_OFFSET_PLAY_RENDER, MAIN_STATE_PLAYING);
			ventanaVisible = true;
		}
	}

	CGMainFramePing();

	g_CustomObjectMgr.Update();

	g_Reconnect.Update();
}

HWND InitWindow(HINSTANCE hInstance)
{
	gInstance = hInstance;
	sInputOutput.Init(gInstance);
	gHWND = INIT_WINDOW_REAL(gInstance);

	return gHWND;
}

void PrintCrownSwitchData()
{
	if ( *(DWORD*)(MAIN_CHARACTER_MAP) != 30 )
	{
		ResetCrownSwitchData();
		return;
	}

	for ( int i = 0; i < 2; ++i )
	{
		if ( !g_CrownSwitchData[i].state )
		{
			continue;
		}

		char switch_message[150];
		memset(switch_message, 0, 150);

		sprintf(switch_message, "%s %d / %s / %s", GetTextBMD(1981), i + 1, g_CrownSwitchData[i].guild, g_CrownSwitchData[i].name);

		MU_SetFont(CDC_This(), *(HGDIOBJ*)(MAIN_OFFSET_FONT_OFFSET));
		MU_SetTextColor(CDC_This(), -1, -1, -1, -1);
		MU_4200F0(CDC_This(), 0);
		MU_TabbedTextOut(CDC_This(), 0, 15 * i + 395, switch_message, 640, 0, 3, 0);
	}
}

void ResetCrownSwitchData()
{
	for ( int i = 0; i < 2; ++i )
	{
		if ( !g_CrownSwitchData[i].state )
		{
			continue;
		}

		g_CrownSwitchData[i].Reset();
	}
}

void ClearCrownSwitchData(void* ptr)
{

}

DWORD PlayerCustomData::GetAttackSpeed() const
{
	BYTE tmp_attack_speed[4];
	memcpy(tmp_attack_speed, this->attack_speed, 4);
	tmp_attack_speed[0] -= 0x20;
	tmp_attack_speed[1] -= 0x21;
	tmp_attack_speed[2] -= 0x22;
	tmp_attack_speed[3] -= 0x23;

	return MAKE_NUMBERDW(MAKE_NUMBERW(tmp_attack_speed[0], tmp_attack_speed[1]), MAKE_NUMBERW(tmp_attack_speed[2], tmp_attack_speed[3]));
}

DWORD PlayerCustomData::GetMagicSpeed() const
{
	BYTE tmp_magic_speed[4];
	memcpy(tmp_magic_speed, this->magic_speed, 4);
	tmp_magic_speed[0] -= 0x24;
	tmp_magic_speed[1] -= 0x25;
	tmp_magic_speed[2] -= 0x26;
	tmp_magic_speed[3] -= 0x27;

	return MAKE_NUMBERDW(MAKE_NUMBERW(tmp_magic_speed[0], tmp_magic_speed[1]), MAKE_NUMBERW(tmp_magic_speed[2], tmp_magic_speed[3]));
}

#define pPlayerData ((ObjectCharacter*)(*(DWORD*)MAIN_CHARACTER_STRUCT))

bool PlayerCustomData::FixSpeed()
{
	DWORD attack_speed_tmp = pPlayerData->AttackSpeed;
	DWORD magic_speed_tmp = pPlayerData->MagicSpeed;
	DWORD my_attack_speed = this->GetAttackSpeed();
	DWORD my_magic_speed = this->GetMagicSpeed();

	if ( attack_speed_tmp > my_attack_speed )
	{
		pPlayerData->AttackSpeed = my_attack_speed;

		if ( (attack_speed_tmp - my_attack_speed) > 50 )
		{
			CGHackCheckByteModified(0, 0, 0);
			return true;
		}
	}

	if ( magic_speed_tmp > my_magic_speed )
	{
		pPlayerData->MagicSpeed = my_magic_speed;

		if ( (magic_speed_tmp - my_magic_speed) > 50 )
		{
			CGHackCheckByteModified(1, 1, 1);
			return true;
		}
	}

	return false;
}