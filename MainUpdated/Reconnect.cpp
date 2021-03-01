#if RECONNECT_ENABLED == 1

Reconnect g_Reconnect;

Reconnect::Reconnect()
{
	memset(this->Account, 0, 11);
	memset(this->Password, 0, 21);
	memset(this->CharacterName, 0, 11);
	this->CharacterIndex = 0;
	this->HelperOn = false;

	for(int i = 0; i < 4; ++i)
	{
		this->ServerMoveAuth[i] = 0;
	}

	this->Progress = RECONNECT_PROGRESS_NONE;
	this->Status = RECONNECT_STATUS_NONE;
	
	this->IsConnectServerConnected = false;
	this->AuthSend = false;

	this->InterfaceTime.Init();
	this->ProcessTime.Init();
}

Reconnect::~Reconnect()
{

}

char GameServerAddress[16];
WORD GameServerPort = 0;

//
void InitReconnect()
{
	memset(GameServerAddress, 0, 16);

	SetCompleteHook(0xE9,MAIN_OFFSET_RECONNECT_CHECK_CONNECTION_HOOK,&ReconnectCheckConnection);
	SetCompleteHook(0xE9,MAIN_OFFSET_RECONNECT_CLOSE_SOCKET_HOOK,&ReconnectCloseSocket);

	for ( size_t i = 0; MainOffsetReconnectCreateConnection[i] != 0; ++i )
	{
		SetCompleteHook(0xE8,MainOffsetReconnectCreateConnection[i],&ReconnectCreateConnection);
	}
	
	SetCompleteHook(0xE8, MAIN_OFFSET_RECONNECT_DRAW_INTERFACE_HOOK, &Reconnect::DrawInterfaceHook);
}


void Reconnect::DrawInterfaceHook()
{
	((void(*)())MAIN_OFFSET_RECONNECT_DRAW_INTERFACE)();

	if(GetMainState() != MAIN_STATE_PLAYING)
	{
		return;
	}

	g_CastleSiege.PrintSwitch();
	g_CastleSiege.PrintCrown();
	g_CastleSiege.PrintMasterCrown();

	if(g_Reconnect.Status != RECONNECT_STATUS_RECONNECT)
	{
		return;
	}

	g_Reconnect.Draw();
}

void Reconnect::Update()
{
	if(GetMainState() != MAIN_STATE_PLAYING)
	{
		return;
	}

	if(this->Status != RECONNECT_STATUS_RECONNECT)
	{
		return;
	}

	if(!this->ProcessTime.Elapsed())
	{
		return;
	}

	this->ProcessTime.Start(10000);

	switch(this->Progress)
	{
	case RECONNECT_PROGRESS_NONE:
		{
			SetByte(MAIN_OFFSET_RECONNECT_MAIN_PROC_CHECK, 0xC3);
			this->GameServerLoad();
		} break;

	case RECONNECT_PROGRESS_CONNECTED:
		{
			SetByte(MAIN_OFFSET_RECONNECT_MAIN_PROC_CHECK, 0x55);
			this->GameServerAuth();
		} break;

	default:
		{
			SetByte(MAIN_OFFSET_RECONNECT_MAIN_PROC_CHECK, 0x55);
		} break;
	}
}

void Reconnect::Draw()
{
	if(this->InterfaceTime.Elapsed())
	{
		this->InterfaceTime.Start(5000);
	}

	float StartX = (MAX_WIN_WIDTH/2.0f)-(160.0f/2.0f);

	float StartY = 100.0f;

	float progress = (this->InterfaceTime.GetRemain() * 150.0f)/(float)this->InterfaceTime.Time;

	progress = ((progress>150)?150:progress);

	DrawInterface(0x7A65,StartX,StartY,160.0f,18.0f);

	DrawInterface(0x7A66,(StartX+5.0f),(StartY+5.0f),progress,8.0f);

	char buff[256];
	sprintf(buff, "Reconnecting");
	DrawInterfaceText(buff,(int)StartX,(int)(StartY+5.0f),0xFFFFFFFF,0,3,160.0f,0);
}

void Reconnect::SetInfo(eReconnectStatus status, eReconnectProgress progress)
{
	this->Status = status;

	this->Progress = progress;

	this->AuthSend = ((status == RECONNECT_STATUS_NONE) ? false : this->AuthSend);
}

void Reconnect::GameServerLoad()
{
	SERVER_INFO_RESULT pMsg;
	pMsg.h.set(0xF4, 0x03, sizeof(SERVER_INFO_RESULT));
	pMsg.port = GameServerPort;
	memcpy(pMsg.ip, GameServerAddress, 16);

	ProtocolCoreEx(0xF4, (BYTE*)&pMsg, pMsg.h.size, 0);
}

void Reconnect::GameServerAuth()
{
	if(this->AuthSend)
	{
		return;
	}

	this->AuthSend = true;

	LOGIN_REQUEST pMsg;

	pMsg.h.set(0xF1,0x01,sizeof(pMsg));

	PacketArgumentEncrypt(pMsg.account, this->Account, 10);

	PacketArgumentEncrypt(pMsg.password, this->Password, 20);

	pMsg.TickCount = GetTickCount();

	pMsg.client_version[0] = (*(BYTE*)(MAIN_OFFSET_CLIENT_VERSION)) - 1;
	pMsg.client_version[1] = (*(BYTE*)(MAIN_OFFSET_CLIENT_VERSION + 1)) - 2;
	pMsg.client_version[2] = (*(BYTE*)(MAIN_OFFSET_CLIENT_VERSION + 2)) - 3;
	pMsg.client_version[3] = (*(BYTE*)(MAIN_OFFSET_CLIENT_VERSION + 3)) - 4;
	pMsg.client_version[4] = (*(BYTE*)(MAIN_OFFSET_CLIENT_VERSION + 4)) - 5;

	memcpy(pMsg.client_serial, ClientSerial, 16);

	pMsg.language_code = 0;
	memset(pMsg.mac, 0, 18);
	GetMac(pMsg.mac);
	pMsg.disk_serial = GetMachineID();
	
	DataSend((BYTE*)&pMsg,pMsg.h.size);
}

void Reconnect::OnCloseSocket()
{
	this->SetInfo(RECONNECT_STATUS_RECONNECT, RECONNECT_PROGRESS_NONE);
	this->AuthSend = false;
}

void Reconnect::OnMapServerMove(char* address,WORD port)
{
	if( this->Status != RECONNECT_STATUS_RECONNECT || this->Progress == RECONNECT_PROGRESS_CHAR_LIST )
	{
		this->SetInfo(RECONNECT_STATUS_DISCONNECT, ((this->Progress==RECONNECT_PROGRESS_CHAR_LIST)?this->Progress:RECONNECT_PROGRESS_NONE));
	}
}

void Reconnect::OnMapServerMoveAuth(BYTE result)
{
	if(this->Status != RECONNECT_STATUS_RECONNECT)
	{
		if(result == 1)
		{
			this->SetInfo(((this->Progress==RECONNECT_PROGRESS_CHAR_LIST)?RECONNECT_STATUS_RECONNECT:RECONNECT_STATUS_NONE),((this->Progress==RECONNECT_PROGRESS_CHAR_LIST)?this->Progress:RECONNECT_PROGRESS_NONE));
		}
		else
		{
			this->SetInfo(RECONNECT_STATUS_DISCONNECT, RECONNECT_PROGRESS_NONE);
		}
	}
}

void Reconnect::OnConnectAccount(BYTE result)
{
	if(this->Progress == RECONNECT_PROGRESS_CONNECTED)
	{
		if( this->AuthSend )
		{
			if(result == 1)
			{
				PMSG_CHARACTER_LIST_SEND pMsg;

				pMsg.header.set(0xF3,0x00,sizeof(pMsg));

				DataSend((BYTE*)&pMsg,pMsg.header.size);

				this->SetInfo(RECONNECT_STATUS_RECONNECT, RECONNECT_PROGRESS_JOINED);
			}
			else
			{
				if( result == 3 )
				{
					this->SetInfo(RECONNECT_STATUS_RECONNECT, RECONNECT_PROGRESS_CONNECTED);
					this->AuthSend = false;
				}
				else
				{
					this->SetInfo(RECONNECT_STATUS_DISCONNECT, RECONNECT_PROGRESS_NONE);
					CloseSocket();
				}
			}
		}
	}
}

void Reconnect::OnCloseClient(BYTE result)
{
	this->SetInfo(RECONNECT_STATUS_DISCONNECT, RECONNECT_PROGRESS_NONE);
}

void Reconnect::OnCharacterList()
{
	if(this->Progress == RECONNECT_PROGRESS_JOINED)
	{
		PARTY_USER_DELETE pPartyDelete;
		ProtocolCoreEx(0x43, (BYTE*)&pPartyDelete, pPartyDelete.h.size, -1);

		CHARACTER_SELECT_REQUEST pMsg;
		pMsg.h.set(0xF3, 0x03, sizeof(CHARACTER_SELECT_REQUEST));
		memcpy(pMsg.character_name, g_Reconnect.CharacterName, 10);
		pMsg.index = g_Reconnect.CharacterIndex;

		DataSend((BYTE*)&pMsg,pMsg.h.size);

		this->SetInfo(RECONNECT_STATUS_RECONNECT, RECONNECT_PROGRESS_CHAR_LIST);
	}
}

void Reconnect::OnCharacterInfo()
{
	if(this->Progress == RECONNECT_PROGRESS_CHAR_LIST)
	{
		if(this->HelperOn)
		{
			PMSG_HELPER_START_SEND pMsg;

			pMsg.header.set(0xBF,0x51,sizeof(pMsg));

			pMsg.type = 0;

			DataSend((BYTE*)&pMsg,pMsg.header.size);
		}
	}

	this->SetInfo(RECONNECT_STATUS_NONE, RECONNECT_PROGRESS_NONE);
}

void Reconnect::SetConnectionInfo(char* address,WORD port)
{
	memset(GameServerAddress, 0, 16);
	sprintf(GameServerAddress,"%s",address);

	GameServerPort = port;
}

void Reconnect::ViewportDestroy()
{
	for( int i = 0; i < MAX_MAIN_VIEWPORT; ++i )
	{
		BYTE send[256];
		PMSG_VIEWPORT_DESTROY_HEAD * head = (PMSG_VIEWPORT_DESTROY_HEAD*)send;
		PMSG_VIEWPORT_DESTROY_BODY * body = (PMSG_VIEWPORT_DESTROY_BODY*)&send[sizeof(PMSG_VIEWPORT_DESTROY_HEAD)];
		head->count = 0;

		ObjectViewport* pObject = WzGetObjectStructByPos(i);

		if ( !pObject )
		{
			continue;
		}

		if (!WzIsObjectLoaded(*(DWORD*)pObject))
		{
			continue;
		}

		body[head->count].index[0] = HIBYTE(pObject->index);
		body[head->count].index[1] = LOBYTE(pObject->index);
		++head->count;

		head->header.set(0x14, sizeof(PMSG_VIEWPORT_DESTROY_HEAD) + (sizeof(PMSG_VIEWPORT_DESTROY_BODY) * head->count));
		ProtocolCoreEx(0x14, send, head->header.size, -1);
	}
}

BOOL ReconnectCreateConnection(char* address, WORD port)
{
	g_Reconnect.IsConnectServerConnected = false;

	char ip_address[100];
	sprintf(ip_address, IpAddress, sizeof(IpAddress));

	g_EncodeDecode.SerialSEND = 0;
	g_EncodeDecode.SerialRECV = 0;

	((BOOL(*)(char*,WORD))MAIN_OFFSET_RECONNECT_CREATE_CONNECTION)(ip_address,port);
	return 1;
}

__declspec(naked) void ReconnectCheckConnection()
{
	static DWORD ReconnectCheckConnectionAddress1 = MAIN_OFFSET_RECONNECT_CHECK_CONNECTION_1;
	static DWORD ReconnectCheckConnectionAddress2 = MAIN_OFFSET_RECONNECT_CHECK_CONNECTION_2;

	if(SocketCheck() != -1 || g_Reconnect.Status == RECONNECT_STATUS_RECONNECT)
	{
		_asm
		{
			Jmp[ReconnectCheckConnectionAddress1]
		}
	}
	else
	{
		_asm
		{
			Jmp[ReconnectCheckConnectionAddress2]
		}
	}
}

__declspec(naked) void ReconnectCloseSocket()
{
	static DWORD ReconnectCloseSocketAddress1 = MAIN_OFFSET_RECONNECT_CLOSE_SOCKET;
	static DWORD ReconnectCloseSocketAddress2 = MAIN_OFFSET_RECONNECT_CLOSE_SOCKET_JUMP2;

	if(*(DWORD*)(MAIN_CONNECTION_STATUS) == 0 || g_Reconnect.Status == RECONNECT_STATUS_DISCONNECT || GetMainState() != MAIN_STATE_PLAYING)
	{
		*(DWORD*)(MAIN_CONNECTION_STATUS) = 0;
		_asm
		{
			Jmp [ReconnectCloseSocketAddress1]
		}
	}
	else
	{
		g_Reconnect.OnCloseSocket();
		_asm
		{
			Mov Eax, 0
			Jmp [ReconnectCloseSocketAddress2]
		}
	}
}

void Reconnect::SetData(const char * account, const char * password)
{
	memset(this->Account, 0, 11);
	memset(this->Password, 0, 21);

	char AccData[11];
	memset(AccData, 0, 11);
	char PswData[21];
	memset(PswData, 0, 21);
	
	memcpy(AccData, account, 10);
	memcpy(PswData, password, 20);

	PacketArgumentEncrypt(AccData, AccData, 10);
	PacketArgumentEncrypt(PswData, PswData, 20);

	strcpy(this->Account, AccData);
	strcpy(this->Password, PswData);
}

#endif