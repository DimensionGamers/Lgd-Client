#define HACK_CHECK_LOOP_VALUE					40
#define FIX_SLEEP_FPS							40

OffsetDataMap offset_data_map;
OffsetFPSMap offset_fps_map;
OffsetAntiHackMap offset_antihack_map;

DWORD getMSTimeMain()
{
	static const boost::chrono::system_clock::time_point ApplicationStartTime = boost::chrono::system_clock::now();

    return DWORD(boost::chrono::duration_cast<boost::chrono::milliseconds>(boost::chrono::system_clock::now() - ApplicationStartTime).count());
}

DWORD getMSTimeDiff(DWORD oldMSTime, DWORD newMSTime)
{
    if (oldMSTime > newMSTime)
        return (0xFFFFFFFF - oldMSTime) + newMSTime;
    else
        return newMSTime - oldMSTime;
}

DWORD GetMSTimeDiffToNow(DWORD oldMSTime)
{
    return getMSTimeDiff(oldMSTime, getMSTimeMain());
}

void CGHackCheckByteModified(DWORD offset, BYTE move, BYTE value)
{
	HACK_CHECK_MODIFIED_BYTE_OFFSET pMsg;
	pMsg.offset = offset;
	pMsg.move = move;
	pMsg.value = value;

	DataSend((BYTE*)&pMsg, pMsg.h.size);
}

void CGHackCheckDoubleModified(DWORD offset, double value)
{
	HACK_CHECK_MODIFIED_DOUBLE_OFFSET pMsg;
	pMsg.offset = offset;
	pMsg.value = value;

	DataSend((BYTE*)&pMsg, pMsg.h.size);
}

void CGHackCheckHookedFunction(BYTE id, BYTE data)
{
	HACK_CHECK_HOOKED_FUNCTION pMsg;
	pMsg.id = id;
	pMsg.data = data;

	DataSend((BYTE*)&pMsg, pMsg.h.size);
}

// ======================================================================================================
//								MAINLOOP
// ======================================================================================================
DWORD MainLoopPingTime = getMSTimeMain();

void MainLoopInit()
{
	if ( GetMainState() == MAIN_STATE_PLAYING )
	{
		if ( GetMSTimeDiffToNow(MainLoopPingTime) >= 1000 )
		{		
			MainLoopPingTime = getMSTimeMain();

			CheckNotPatched("kernel32.dll", "QueryPerformanceCounter", 0, 0);
			CheckNotPatched("kernel32.dll", "QueryPerformanceFrequency", 0, 1);
			CheckNotPatched("kernel32.dll", "GetTickCount", 0, 2);
		}
	}
}
// ======================================================================================================
//								SLEEP
// ======================================================================================================
void ApplyAntiCheat()
{

}

void CheckNotPatched(const char* szDll, const char* szFunc,int mode,BYTE id)
{
    HMODULE hMod = GetModuleHandleA(szDll);

    if(!hMod)
    {
        return;
    }

    BYTE* pFunc = (BYTE*)GetProcAddress(hMod, szFunc);

    if (!pFunc)
    {
        return;
    }

	if(pFunc[0] == 0xE9 || pFunc[0] == 0x90)
	{
		CGHackCheckHookedFunction(id, pFunc[0]);
	}
}

void CGMainFramePing()
{
	if (GetMainState() == MAIN_STATE_PLAYING)
	{
		for ( OffsetDataMap::const_iterator it = offset_data_map.begin(); it != offset_data_map.end(); ++it )
		{
			if ( !it->second.offset )
			{
				continue;
			}

			if ( *(BYTE*)(it->second.offset) != it->second.data )
			{
				CGHackCheckByteModified(it->second.offset, 0, *(BYTE*)(it->second.offset));

				if ( it->second.fix )
				{
					*(BYTE*)(it->second.offset) = it->second.data;
				}
			}
		}

		for ( OffsetAntiHackMap::const_iterator itr = offset_antihack_map.begin(); itr != offset_antihack_map.end(); ++itr )
		{
			if ( *(BYTE*)(itr->first) != itr->second )
			{
				CGHackCheckByteModified(itr->first, 0, *(BYTE*)(itr->first));
			}
		}
	}
}

void AddOffsetData(BYTE * Packet)
{
	HACK_CHECK_ADD_OFFSET_HEAD * head = (HACK_CHECK_ADD_OFFSET_HEAD*)Packet;
	HACK_CHECK_ADD_OFFSET_BODY * body = (HACK_CHECK_ADD_OFFSET_BODY*)&Packet[sizeof(HACK_CHECK_ADD_OFFSET_HEAD)];

	for ( OffsetDataMap::iterator it = offset_data_map.begin(); it != offset_data_map.end(); ++it )
	{
		it->second.offset = 0;
	}

	for ( int i = 0; i < head->count; ++i )
	{
		body[i].offset = 0xFFFFFFFF - body[i].offset;
		body[i].data = 0xFF - body[i].data;

		OffsetData & data = offset_data_map[body[i].offset];
		data.data = body[i].data;
		data.fix = body[i].fix;
		data.offset = body[i].offset;
	}
}