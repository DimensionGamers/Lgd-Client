AntiCheat g_AntiCheat;

AntiCheat::AntiCheat()
{
	this->SetTime(getMSTimeMain());
}

AntiCheat::~AntiCheat()
{

}

void AntiCheat::InitKey()
{
	this->SetAntiMacroEnabled(false);
	this->SetAntiMacroTime(0);

	this->SetAntiMacroComboEnabled(false);
	this->SetAntiMacroComboTime(0);

	for(int i = 0; KeyArray[i] != 0; ++i)
	{
		this->SetKeyPress(true, KeyArray[i]);
		this->SetKeyPress(false, KeyArray[i]);
	}
}

void AntiCheat::LoadOffsetMap()
{
	FILE* fp = fopen("OffsetData.txt", "w");

	for(size_t i = 0; g_MainOffsetAC[i].offset1 != 0; ++i)
	{
		for(DWORD n = g_MainOffsetAC[i].offset1; n < g_MainOffsetAC[i].offset2; ++n)
		{
			this->m_OffsetMap[n] = *(BYTE*)(n);

			fprintf(fp, "%u	%u\n", n, this->m_OffsetMap[n]);
		}
	}

	fclose(fp);
}

void AntiCheat::UpdateOffsetMap()
{
	if(GetMSTimeDiffToNow(this->GetTime()) < 1000)
	{
		return;
	}

	this->SetTime(getMSTimeMain());

	for(ACOffsetMap::const_iterator itr = this->m_OffsetMap.begin(); itr != this->m_OffsetMap.end(); ++itr)
	{
		BYTE value = *(BYTE*)(itr->first);

		if(value != itr->second)
		{
			CGHackCheckByteModified(itr->first, 0, value);
		}
	}
}

void AntiCheat::SetKeyPress(bool vr, int key)
{
	switch(key)
	{
	case 0x51:
	case 0x71:
	case 0x57:
	case 0x77:
	case 0x45:
	case 0x65:
	case 0x52:
	case 0x72:
		{
			key = 0;
		} break;

	case 0x30: // 0
	case 0x31: // 1
	case 0x32: // 2
	case 0x33: // 3
	case 0x34: // 4
	case 0x35: // 5 
	case 0x36: // 6
	case 0x37: // 7
	case 0x38: // 8
	case 0x39: // 9
		{
			key = 4;
		} break;

	default:
		{
			key = -1;
		} break;
	}

	if(key == -1)
	{
		return;
	}

	if(vr)
	{
		this->m_VirtualKeyMap[key] = GetTickCount();
	}
	else
	{
		this->m_NormalKeyMap[key] = GetTickCount();
	}
}

bool AntiCheat::IsKeyAllowed(int key, uint8 type)
{
	if(type == 0)
	{
		if(!this->IsAntiMacroEnabled())
		{
			return true;
		}
	}
	else
	{
		if(!this->IsAntiMacroComboEnabled())
		{
			return true;
		}
	}

	if (GetMainState() != MAIN_STATE_PLAYING)
	{
		return true;
	}

	if(key <= -1)
	{
		return true;
	}

	KeyPressMap::const_iterator itr = this->m_NormalKeyMap.find(key);

	if(itr == this->m_NormalKeyMap.end())
	{
		return true;
	}

	DWORD virtual_time = this->m_VirtualKeyMap[key];
	DWORD current_time = GetTickCount();
	DWORD time = type == 0 ? this->GetAntiMacroTime() : this->GetAntiMacroComboTime();

	if((current_time - virtual_time) < time)
	{
		return false;
	}

	int diff = this->m_NormalKeyMap[key] - virtual_time;

	if(diff < 0)
	{
		return false;
	}

	return true;
}

bool AntiCheat::IsBindKeyAllowed(int key)
{
	if(!this->IsAntiMacroEnabled())
	{
		return true;
	}

	if(this->IsKeyAllowed(key, 0))
	{
		return true;
	}

	this->SendMacroDetect(0);
	return false;
}

bool AntiCheat::IsSkillBindKeyAllowed(int key)
{
	if(!this->IsAntiMacroComboEnabled())
	{
		return true;
	}

	if(this->IsKeyAllowed(key, 1))
	{
		return true;
	}

	this->SendMacroDetect(1);
	return false;
}

void AntiCheat::SetAntiMacroData(BYTE* Packet)
{
	PACKET_ANTI_MACRO * lpMsg = (PACKET_ANTI_MACRO*)Packet;

	this->SetAntiMacroEnabled(lpMsg->enabled == 1 ? true : false);
	this->SetAntiMacroTime(lpMsg->time);

	this->SetAntiMacroComboEnabled(lpMsg->combo_enabled == 1 ? true : false);
	this->SetAntiMacroComboTime(lpMsg->combo_time);
}

void AntiCheat::SendMacroDetect(uint8 type)
{
	PACKET_ANTI_MACRO_DETECT pMsg;
	pMsg.type = type;

	DataSend((BYTE*)&pMsg, pMsg.GetSize());
}