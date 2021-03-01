BOOL ProtocolCoreEx(BYTE head,BYTE* lpMsg, DWORD size,int key)
{
	if ( !g_Reconnect.IsConnectServerConnected )
	{
		if(head != 0xF4)
		{
			BYTE start_encode = (lpMsg[0] == 0xC1 || lpMsg[0] == 0xC3) ? 3: (lpMsg[0] == 0xC2 || lpMsg[0] == 0xC4) ? 4: 0;

			if ( !start_encode )
			{
				return 0;
			}

			for ( DWORD i = start_encode; i < size; ++i )
			{
				lpMsg[i] -= head;
			}
		}
	}

	CapturePacket(head, lpMsg, size);

	switch(head)
	{
	case 0xF4:
		{
			switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
			{
			case 0x03:
				{
					SERVER_INFO_RESULT * lpData = (SERVER_INFO_RESULT*)lpMsg;

					g_Reconnect.SetConnectionInfo(lpData->ip, lpData->port);
				} break;
			}
		} break;

	case 0x14:
		{
			g_CustomObjectMgr.GCRemoveMonsterData(lpMsg);
		} break;

	case 0xB2:
		{
			switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
			{
			case 0x14:
				{
					CASTLE_SIEGE_SWITCH_STATE * lpData = (CASTLE_SIEGE_SWITCH_STATE*)lpMsg;
					g_CastleSiege.SetSwitchData(lpData->state, lpData->playerH * 512 + lpData->playerL, lpData->switchH * 512 + lpData->switchL);
					return 1;
				} break;

			case 0x15:
				{
					CROWN_ACCESS_STATE * lpData = (CROWN_ACCESS_STATE*)lpMsg;
					g_CastleSiege.SetCrownMasterData(lpData->state, lpData->accumulated_time);
					return 1;
				} break;

			case 0x16:
				{
					CROWN_STATE * lpData = (CROWN_STATE*)lpMsg;
					g_CastleSiege.SetCrownData(lpData->state);
					return 1;
				} break;
			case 0x20:
				{
					GCSetCrownSwitchData(lpMsg);
					return 1;
				} break;
			}
		} break;

	case 0x48:
		{
			if(sInputOutput.render_fix_2)
			{
				SEND_EFFECT * lpData = (SEND_EFFECT*)lpMsg;

				WORD index = lpData->index[0] * 512 + lpData->index[1];

				if(index != ViewIndex && (lpData->effect == 3 || lpData->effect == 17))
				{
					return 1;
				}
			}
		} break;

	case 0x17:
		GCUserDieRecv((PMSG_USER_DIE_RECV*)lpMsg);
		break;

	case 0xB1:
		switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
		{
			case 0x00:
				GCMapServerMoveRecv((PMSG_MAP_SERVER_MOVE_RECV*)lpMsg);
				break;
			case 0x01:
				GCMapServerMoveAuthRecv((PMSG_MAP_SERVER_MOVE_AUTH_RECV*)lpMsg);
				break;
		}
		break;


	case 0xBF:
		{
			switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
			{
			case 0x51:
				{
#if RECONNECT_ENABLED == 1
					if ( g_Reconnect.Progress == RECONNECT_PROGRESS_NONE )
					{
						HELPER_OPEN_RESULT * pData = (HELPER_OPEN_RESULT*)lpMsg;
						g_Reconnect.HelperOn = (pData->result == 0) ? true : false;
					}
#endif
				} break;
			}
		} break;

	case 0xF1:
		switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
		{
			case 0x00:
				{
					GCConnectClientRecv((PMSG_CONNECT_CLIENT_RECV*)lpMsg);
				} break;
			case 0x01:
				GCConnectAccountRecv((PMSG_CONNECT_ACCOUNT_RECV*)lpMsg);
				break;
			case 0x02:
				if(!GCCloseClientRecv((PMSG_CLOSE_CLIENT_RECV*)lpMsg))
				{
					return 1;
				}
				break;
		}
		break;

	case CLIENT_CONNECT_CUSTOM_HEADER:
	{
										 CustomConnect(lpMsg);
										 return 1;
	} break;

	case HEADCODE_CASH_SHOP:
		{
			switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
			{
			case SUBCODE_CASH_SHOP_DATE_ITEM:
				{
					g_CashShop.HandleItemData(lpMsg);
				}
				break;

			case SUBCODE_CASH_SHOP_CATEGORY:
				{
					g_CashShop.HandleCategory(lpMsg);
					return 1;
				}
				break;

			case SUBCODE_CASH_SHOP_PACKAGE:
				{
					g_CashShop.HandlePackage(lpMsg);
					return 1;
				}
				break;

			case SUBCODE_CASH_SHOP_PRODUCT:
				{
					g_CashShop.HandleProduct(lpMsg);
					return 1;
				}
				break;
			}
		}
		break;

	case 0xD8:
		{
			HandleElementalDamage(lpMsg);
		} break;

	case 0xDF:
		{
			HandleDamage(lpMsg);
		} break;

	case 0x26:
		{
			HandleHP(lpMsg);
		} break;

	case 0x27:
		{
			HandleMP(lpMsg);
		} break;

	case 0xF3:
		switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
		{
			case 0x00:
				GCCharacterListRecv();
#if RECONNECT_ENABLED == 1
				if(g_Reconnect.Status == RECONNECT_STATUS_RECONNECT)
				{
					return 1;
				}
#endif
				break;
			case 0x03:
				GCCharacterInfoRecv(lpMsg);
#if RECONNECT_ENABLED == 1
				if(g_Reconnect.Status == RECONNECT_STATUS_RECONNECT)
				{
					return 1;
				}
#endif
				break;

			case 0x04:
				{
					HandleRespawn(lpMsg);
				} break;

			case 0x05:
				{
					HandleLevelUp(lpMsg);
				} break;

			case 0x50:
				{
					HandleMasterStatus(lpMsg);
				} break;

			case 0x51:
				{
					HandleMasterLevelUp(lpMsg);
				} break;

			case 0xE2:
				return 1;
				// Custom
			case 0xA5:
				{
					g_CashShop.HandleData(lpMsg);
				} break;

			case 0xB0:
				{
					GCNewMessageRecv(lpMsg);
					return 1;
				} break;

			case 0xB4:
				{
					return 1;
				} break;

			case 189:
				{
					g_CustomObjectMgr.GCSetMonsterData(lpMsg);
					return 1;
				} break;

			case 190:
				{
					GCSetAttackSpeed(lpMsg);
					return 1;
				} break;

			case 197:
				{
					return 1;
				} break;

			case 198:
				{
					SetShopPrice(lpMsg);
					return 1;
				} break;

			case 199:
				{
					return 1;
				} break;

			case 200:
				{
					GCMessageBox(lpMsg);
					return 1;
				} break;

			case 201:
				{
					GCOffsetFPS(lpMsg);
					return 1;
				} break;

			case 204:
				{
					g_AntiCheat.SetAntiMacroData(lpMsg);
					return 1;
				} break;
		}
		break;
	}

	return ProtocolCore(head, lpMsg, size, 1);
}

void GCUserDieRecv(PMSG_USER_DIE_RECV* lpMsg)
{
	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;

	if(ViewIndex == aIndex)
	{
		ViewHP = 0;
	}
}

void GCMapServerMoveRecv(PMSG_MAP_SERVER_MOVE_RECV* lpMsg)
{
#if RECONNECT_ENABLED == 1
	g_Reconnect.OnMapServerMove(lpMsg->IpAddress,lpMsg->ServerPort);
#endif
	g_Reconnect.ServerMoveAuth[0] = lpMsg->AuthCode1;
	g_Reconnect.ServerMoveAuth[1] = lpMsg->AuthCode2;
	g_Reconnect.ServerMoveAuth[2] = lpMsg->AuthCode3;
	g_Reconnect.ServerMoveAuth[3] = lpMsg->AuthCode4;
}

void GCMapServerMoveAuthRecv(PMSG_MAP_SERVER_MOVE_AUTH_RECV* lpMsg)
{
#if RECONNECT_ENABLED == 1
	g_Reconnect.OnMapServerMoveAuth(lpMsg->result);
#endif
}

void GCConnectClientRecv(PMSG_CONNECT_CLIENT_RECV* lpMsg)
{
	ViewIndex = MAKE_NUMBERW(lpMsg->indexH,lpMsg->indexL);

	if(g_Reconnect.Status == RECONNECT_STATUS_RECONNECT && g_Reconnect.Progress == RECONNECT_PROGRESS_NONE)
	{
		g_Reconnect.SetInfo(RECONNECT_STATUS_RECONNECT, RECONNECT_PROGRESS_CONNECTED);
	}
}

void GCConnectAccountRecv(PMSG_CONNECT_ACCOUNT_RECV* lpMsg)
{
#if RECONNECT_ENABLED == 1
	g_Reconnect.OnConnectAccount(lpMsg->result);
#endif
}

bool GCCloseClientRecv(PMSG_CLOSE_CLIENT_RECV* lpMsg)
{
	if(lpMsg->result == 0)
	{
		ExitProcess(0);
		return false;
	}

#if RECONNECT_ENABLED == 1
	g_Reconnect.OnCloseClient(lpMsg->result);
#endif

	return true;
}

void GCCharacterListRecv()
{
#if RECONNECT_ENABLED == 1
	g_Reconnect.OnCharacterList();
#endif
}

void GCCharacterInfoRecv(BYTE* Packet)
{
	CHARACTER_JOIN_RESULT * lpMsg = (CHARACTER_JOIN_RESULT*)Packet;

	ViewHP = lpMsg->ViewHP;
	ViewMP = lpMsg->ViewMP;
	ViewSD = lpMsg->ViewSD;
	ViewAG = lpMsg->ViewAG;

	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewMaxAG = lpMsg->ViewMaxAG;

#if RECONNECT_ENABLED == 1
	g_Reconnect.OnCharacterInfo();
#endif
}

void GCNewMessageRecv(BYTE * Packet)
{
	CUSTOM_MESSAGE * lpMsg = (CUSTOM_MESSAGE*)Packet;

	WzMessageSend(lpMsg->type, lpMsg->message, "");
}

void GCNewMessageRecv(BYTE type, const char * message, ...)
{
	ARG(buffer, message);

	WzMessageSend(type, buffer, "");
}

void GCSetCrownSwitchData(BYTE * Packet)
{
	CASTLE_SIEGE_SWITCH_INFO * lpMsg = (CASTLE_SIEGE_SWITCH_INFO*)Packet;

	if ( lpMsg->id >= 2 )
	{
		return;
	}

	g_CrownSwitchData[lpMsg->id].index = lpMsg->switch_index;
	g_CrownSwitchData[lpMsg->id].state = lpMsg->state;
	g_CrownSwitchData[lpMsg->id].join_side = lpMsg->join_side;
	
	if ( !g_CrownSwitchData[lpMsg->id].state )
	{
		g_CrownSwitchData[lpMsg->id].Reset();
	}
	else
	{
		memcpy(g_CrownSwitchData[lpMsg->id].name, lpMsg->user, 11);
		memcpy(g_CrownSwitchData[lpMsg->id].guild, lpMsg->guild, 9);
	}
}

void DataSend(BYTE* lpMsg, DWORD size)
{
	BYTE EncBuff[8192];
	memcpy(EncBuff, lpMsg, size);

	muPacket* pointer = (muPacket*)&EncBuff;
	MU_EncodeC1C2(pointer);

	memcpy(EncBuff, pointer, size);

	DataSendHOOK(EncBuff, size);
}

void GCSetAttackSpeed(BYTE * Packet)
{
	ATTACK_SPEED_DATA * lpMsg = (ATTACK_SPEED_DATA*)Packet;

	memcpy(g_PlayerCustomData.attack_speed, lpMsg->attack_speed, 4);
	memcpy(g_PlayerCustomData.magic_speed, lpMsg->magic_speed, 4);
}

void CGAttackSpeed()
{
	static DWORD UpdateTick = GetTickCount();

	if ( (GetTickCount() - UpdateTick) > 10000 )
	{
		UpdateTick = GetTickCount();

		ATTACK_SPEED_DATA pMsg(g_PlayerCustomData.GetAttackSpeed(), g_PlayerCustomData.GetMagicSpeed());
		DataSend((BYTE*)&pMsg, pMsg.h.size);
	}
}

void GCMessageBox(BYTE * Packet)
{
	MESSAGE_BOX_SEND * lpMsg = (MESSAGE_BOX_SEND*)Packet;

	WzMessageBox(lpMsg->caption, lpMsg->message, lpMsg->type);
}

void GCMessageBox(BYTE type, const char * caption, const char * message, ...)
{
	ARG(buffer, message);

	WzMessageBox(caption, buffer, type);
}

void NormalMessage(BYTE type, const char * msg, ...)
{
	ARG(message, msg);

	PMSG_NOTICE pMsg;
	pMsg.type = type;
	memcpy(pMsg.Notice,message,strlen(message));
	pMsg.h.size += strlen(message);

	ProtocolCoreEx(0x0D, (BYTE*)&pMsg, pMsg.h.size, 1);
}

void GCOffsetFPS(BYTE * Packet)
{
	
}

void ApplyFPSOffset(bool value)
{
	sInputOutput.render_fix_2 = value;

	if (sInputOutput.render_fix_2)
	{
		for ( OffsetFPSMap::iterator it = offset_fps_map.begin(); it != offset_fps_map.end(); ++it )
		{
			if ( it->second.offset != 0 )
			{
				SetByte(it->second.offset, it->second.mod);
			}
		}

		for ( int i = 0; g_MainOffsetPerformanceFix[i].offset != 0; ++i )
		{
			SetByte(g_MainOffsetPerformanceFix[i].offset, g_MainOffsetPerformanceFix[i].value);
		}
	}
	else 
	{
		for ( OffsetFPSMap::iterator it = offset_fps_map.begin(); it != offset_fps_map.end(); ++it )
		{
			if ( it->second.offset != 0 )
			{
				SetByte(it->second.offset, it->second.original);
			}
		}

		for ( int i = 0; g_MainOffsetPerformanceFix[i].offset != 0; ++i )
		{
			SetByte(g_MainOffsetPerformanceFix[i].offset, g_MainOffsetPerformanceFix[i].original);
		}
	}
}

void TestPacketRecv(BYTE* Packet)
{

}

void CustomConnect(BYTE* Packet)
{
	CLIENT_CONNECT_CUSTOM* lpMsg = (CLIENT_CONNECT_CUSTOM*)Packet;

	CLIENT_CONNECT_CUSTOM_RESULT pMsg;
	pMsg.result = 1;
	pMsg.time = lpMsg->time;

	DataSend((uint8*)&pMsg, pMsg.GetSize());
}

void HandleRespawn(BYTE* Packet)
{
	PLAYER_RESPAWN* lpMsg = (PLAYER_RESPAWN*)Packet;

	ViewHP = lpMsg->ViewHP;
	ViewMP = lpMsg->ViewMP;
	ViewSD = lpMsg->ViewSD;
	ViewAG = lpMsg->ViewAG;
}

void HandleLevelUp(BYTE* Packet)
{
	NORMAL_LEVELUP_SEND* lpMsg = (NORMAL_LEVELUP_SEND*)Packet;

	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewMaxAG = lpMsg->ViewMaxAG;
}

void HandleElementalDamage(BYTE* Packet)
{
	ELEMENTAL_DAMAGE_SEND* lpMsg = (ELEMENTAL_DAMAGE_SEND*)Packet;

	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;

	if(ViewIndex == aIndex)
	{
		ViewHP = lpMsg->ViewHP;
		ViewSD = lpMsg->ViewSD;
	}
}

void HandleDamage(BYTE* Packet)
{
	DAMAGE_SEND* lpMsg = (DAMAGE_SEND*)Packet;

	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;

	if(ViewIndex == aIndex)
	{
		ViewHP = lpMsg->ViewHP;
		ViewSD = lpMsg->ViewSD;
	}
}

void HandleMasterStatus(BYTE* Packet)
{
	MASTER_STATUS_SEND* lpMsg = (MASTER_STATUS_SEND*)Packet;

	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewMaxAG = lpMsg->ViewMaxAG;
}

void HandleMasterLevelUp(BYTE* Packet)
{
	MASTER_LEVELUP_SEND* lpMsg = (MASTER_LEVELUP_SEND*)Packet;

	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewMaxAG = lpMsg->ViewMaxAG;
}

void HandleHP(BYTE* Packet)
{
	LIFE_SEND* lpMsg = (LIFE_SEND*)Packet;

	if(lpMsg->type == 0xFE)
	{
		ViewMaxHP = lpMsg->ViewHP;
		ViewMaxSD = lpMsg->ViewSD;
	}
	else if(lpMsg->type == 0xFF)
	{
		ViewHP = lpMsg->ViewHP;
		ViewSD = lpMsg->ViewSD;
	}
}

void HandleMP(BYTE* Packet)
{
	MANA_SEND* lpMsg = (MANA_SEND*)Packet;

	if(lpMsg->type == 0xFE)
	{
		ViewMaxMP = lpMsg->ViewMP;
		ViewMaxAG = lpMsg->ViewAG;
	}
	else if(lpMsg->type == 0xFF)
	{
		ViewMP = lpMsg->ViewMP;
		ViewAG = lpMsg->ViewAG;
	}
}