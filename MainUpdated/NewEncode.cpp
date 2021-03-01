BYTE NewEncPacket[8192];
WORD PacketSize = 0;

__declspec(naked) void FixItemGet()
{
	static const DWORD JMP_1 = MAIN_FIX_ITEM_GET_JMP;

	_asm
	{
		Lea Eax, NewEncPacket
		Mov Dword Ptr Ss:[Ebp-MAIN_FIX_ITEM_GET_VALUE], Eax
	}

	_asm
	{
		Jmp [JMP_1]
	}
}

__declspec(naked) void FixItemMove()
{
	static const DWORD JMP_1 = MAIN_FIX_ITEM_MOVE_JMP;

	_asm
	{
		Lea Eax, NewEncPacket
		Mov Dword Ptr Ss:[Ebp-MAIN_FIX_ITEM_MOVE_VALUE], Eax
	}

	_asm
	{
		Jmp [JMP_1]
	}
}

__declspec(naked) void FixItemGetMuun()
{
	static const DWORD JMP_1 = MAIN_FIX_ITEM_GET_MUUN_JMP;

	_asm
	{
		Lea Eax, NewEncPacket
		Mov Dword Ptr Ss:[Ebp-MAIN_FIX_ITEM_GET_MUUN_VALUE], Eax
	}

	_asm
	{
		Jmp [JMP_1]
	}
}

__declspec(naked) void FixItemGetEvent()
{
	static const DWORD JMP_1 = MAIN_FIX_ITEM_GET_EVENT_JMP;

	_asm
	{
		Lea Eax, NewEncPacket
		Mov Dword Ptr Ss:[Ebp-MAIN_FIX_ITEM_GET_EVENT_VALUE], Eax
	}

	_asm
	{
		Jmp [JMP_1]
	}
}

__declspec(naked) void FixItemModify()
{
	static const DWORD JMP_1 = MAIN_FIX_ITEM_MODIFY_JMP;

	_asm
	{
		Lea Eax, NewEncPacket
		Mov Dword Ptr Ss:[Ebp-MAIN_FIX_ITEM_MODIFY_VALUE], Eax
	}

	_asm
	{
		Jmp [JMP_1]
	}
}

__declspec(naked) void FixItemModifyMuun()
{
	static const DWORD JMP_1 = MAIN_FIX_ITEM_MODIFY_MUUN_JMP;

	_asm
	{
		Lea Eax, NewEncPacket
		Mov Dword Ptr Ss:[Ebp-MAIN_FIX_ITEM_MODIFY_MUUN_VALUE], Eax
	}

	_asm
	{
		Jmp [JMP_1]
	}
}

__declspec(naked) void FixItemModifyEvent()
{
	static const DWORD JMP_1 = MAIN_FIX_ITEM_MODIFY_EVENT_JMP;

	_asm
	{
		Lea Eax, NewEncPacket
		Mov Dword Ptr Ss:[Ebp-MAIN_FIX_ITEM_MODIFY_EVENT_VALUE], Eax
	}

	_asm
	{
		Jmp [JMP_1]
	}
}

__declspec(naked) void FixItemChangeEvent()
{
	static const DWORD JMP_1 = MAIN_FIX_ITEM_CHANGE_EVENT_JMP;

	_asm
	{
		Lea Eax, NewEncPacket
		Mov Dword Ptr Ss:[Ebp-MAIN_FIX_ITEM_CHANGE_EVENT_VALUE], Eax
	}

	_asm
	{
		Jmp [JMP_1]
	}
}

__declspec(naked) void FixLogin()
{
	static const DWORD JMP_1 = MAIN_FIX_LOGIN_JMP;

	_asm
	{
		Lea Eax, NewEncPacket
		Mov Dword Ptr Ss:[Ebp-MAIN_FIX_LOGIN_VALUE], Eax
	}

	_asm
	{
		Jmp [JMP_1]
	}
}

__declspec(naked) void FixQuestMUList1()
{
	static const DWORD JMP_1 = MAIN_FIX_QUEST_MU_LIST_1_JMP;

	_asm
	{
		Lea Eax, NewEncPacket
		Mov Dword Ptr Ss:[Ebp-MAIN_FIX_QUEST_MU_LIST_1_VALUE], Eax
	}

	_asm
	{
		Jmp [JMP_1]
	}
}

__declspec(naked) void FixQuestMUList2()
{
	static const DWORD JMP_1 = MAIN_FIX_QUEST_MU_LIST_2_JMP;

	_asm
	{
		Lea Eax, NewEncPacket
		Mov Dword Ptr Ss:[Ebp-MAIN_FIX_QUEST_MU_LIST_2_VALUE], Eax
	}

	_asm
	{
		Jmp [JMP_1]
	}
}

void ItemUseBind(BYTE slot, char key)
{
	if(g_AntiCheat.IsBindKeyAllowed(key))
	{
		WzSendItemUse(slot, key);
	}
}

void ApplyNewEncodeFix()
{
	SetCompleteHook(0xE9, MAIN_FIX_QUEST_MU_LIST_1_HOOK, &FixQuestMUList1);
	SetCompleteHook(0xE9, MAIN_FIX_QUEST_MU_LIST_2_HOOK, &FixQuestMUList2);

	SetCompleteHook(0xE9, MAIN_FIX_ITEM_GET_HOOK, &FixItemGet);
	SetCompleteHook(0xE9, MAIN_FIX_ITEM_MOVE_HOOK, &FixItemMove);
	SetCompleteHook(0xE9, MAIN_FIX_ITEM_GET_MUUN_HOOK, &FixItemGetMuun);
	SetCompleteHook(0xE9, MAIN_FIX_ITEM_GET_EVENT_HOOK, &FixItemGetEvent);

	SetCompleteHook(0xE9, MAIN_FIX_ITEM_MODIFY_HOOK, &FixItemModify);
	SetCompleteHook(0xE9, MAIN_FIX_ITEM_MODIFY_MUUN_HOOK, &FixItemModifyMuun);
	SetCompleteHook(0xE9, MAIN_FIX_ITEM_MODIFY_EVENT_HOOK, &FixItemModifyEvent);
	SetCompleteHook(0xE9, MAIN_FIX_ITEM_CHANGE_EVENT_HOOK, &FixItemChangeEvent);

	SetCompleteHook(0xE9, MAIN_FIX_LOGIN_HOOK, &FixLogin);

	SetCompleteHook(0xE8, MAIN_OFFSET_BIND_ITEM_USE_HOOK, &ItemUseBind);
}

void SetPacket(BYTE* Packet, WORD size)
{
	memset(NewEncPacket, 0, 8192);

	if(size > 8192)
	{
		size = 8192;
	}

	memcpy(NewEncPacket, Packet, size);
	PacketSize = size;
}

void CapturePacket(BYTE headcode, BYTE * Packet, WORD size)
{
	//SetPacket(Packet, size);

	switch(headcode)
	{
	case 0x22:
	case 0x23:
	case 0x24:
		{
			SetPacket(Packet, size);
		} break;

	case 0x4E:
		{
			switch(((Packet[0]==0xC1)?Packet[3]:Packet[4]))
			{
			case 0x00:
			case 0x05:
				{
					SetPacket(Packet, size);
				} break;
			}
		} break;

	case 0x4D:
		{
			switch(((Packet[0]==0xC1)?Packet[3]:Packet[4]))
			{
			case 0x00:
			case 0x05:
			case 0x06:
				{
					SetPacket(Packet, size);
				} break;
			}
		} break;

	case 0xF3:
		{
			switch(((Packet[0]==0xC1)?Packet[3]:Packet[4]))
			{
			case 0x14:
				{
					SetPacket(Packet, size);
				} break;
			}
		} break;

	case 0xF1:
		{
			switch(((Packet[0]==0xC1)?Packet[3]:Packet[4]))
			{
			case 0x00:
				{
					SetPacket(Packet, size);
				} break;
			}
		} break;

	case 0xF6:
		{
			switch(((Packet[0]==0xC1)?Packet[3]:Packet[4]))
			{
			case 0x70:
			case 0x71:
				{
					SetPacket(Packet, size);
				} break;
			}
		} break;
	}
}