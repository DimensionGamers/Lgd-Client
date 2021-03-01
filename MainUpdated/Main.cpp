void InitEntryProc()
{
	CreateDirectory("Logs", NULL);
	CreateDirectory("ScreenShots", NULL);

	for(int i = 0; i < MAIN_OFFSET_EP_SIZE; ++i)
	{
		SetByte(MAIN_OFFSET_EP + i, MainOffsetEP[i]);
	}

	for ( size_t i = 0; g_MainOffsetByteFix[i].offset != 0; ++i )
	{
		SetByte(g_MainOffsetByteFix[i].offset, g_MainOffsetByteFix[i].value);
	}

	for ( size_t i = 0; g_MainOffsetDwordFix[i].offset != 0; ++i )
	{
		SetDword(g_MainOffsetDwordFix[i].offset, g_MainOffsetDwordFix[i].value);
	}

	for ( size_t i = 0; g_MainOffsetMemorySet[i].offset != 0; ++i )
	{
		MemorySet(g_MainOffsetMemorySet[i].offset, g_MainOffsetMemorySet[i].value, g_MainOffsetMemorySet[i].count);
	}

	for ( size_t i = 0; g_MainOffsetMemoryCpy[i].offset != 0; ++i )
	{
		MemoryCpy(g_MainOffsetMemoryCpy[i].offset, g_MainOffsetMemoryCpy[i].value, g_MainOffsetMemoryCpy[i].size);
	}

	SetCompleteHook(0xFF, MAIN_OFFSET_DATASEND_HOOK_1, &DataSendHOOK);
	SetCompleteHook(0xFF, MAIN_OFFSET_DATASEND_HOOK_2, &DataSendHOOK);
	SetCompleteHook(0xFF, MAIN_OFFSET_DATASEND_HOOK_3, &DataSendHOOK);
	SetCompleteHook(0xFF, MAIN_OFFSET_PROTOCOL_CORE_HOOK, &ProtocolCoreEx);

	InitCommon();

	InitItem();

	InitPrintPlayer();
#if RECONNECT_ENABLED == 1
	InitReconnect();
#endif

	ApplyAntiCheat();

	ApplyNewEncodeFix();

	g_AntiCheat.InitKey();

	ApplyNewEncodeFix();
}

BOOL APIENTRY DllMain(HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			InitEntryProc();
			break;
		case DLL_PROCESS_DETACH:
			CloseSocket();
			sInputOutput.FreeMemory();
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
	}

	return 1;
}