DWORD ViewIndex = 0;
DWORD ViewHP = 0;
DWORD ViewSD = 0;
DWORD ViewMP = 0;
DWORD ViewAG = 0;

DWORD ViewMaxHP = 0;
DWORD ViewMaxSD = 0;
DWORD ViewMaxMP = 0;
DWORD ViewMaxAG = 0;

void InitPrintPlayer()
{
	SetCompleteHook(0xE9,MAIN_OFFSET_PRINT_PLAYER_VIEW_HP_HOOK,&PrintPlayerViewHP);
	SetCompleteHook(0xE9,MAIN_OFFSET_PRINT_PLAYER_VIEW_MP_HOOK,&PrintPlayerViewMP);
	SetCompleteHook(0xE9,MAIN_OFFSET_PRINT_PLAYER_VIEW_BP_HOOK,&PrintPlayerViewBP);
	SetCompleteHook(0xE9,MAIN_OFFSET_PRINT_PLAYER_VIEW_SD_HOOK,&PrintPlayerViewSD);
	
	SetCompleteHook(0xE9,MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_HP_HOOK,&PrintPlayerViewMaxHP);
	SetCompleteHook(0xE9,MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_MP_HOOK,&PrintPlayerViewMaxMP);
	SetCompleteHook(0xE9,MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_BP_HOOK,&PrintPlayerViewMaxBP);
	SetCompleteHook(0xE9,MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_SD_HOOK,&PrintPlayerViewMaxSD);
}

__declspec(naked) void PrintPlayerViewHP()
{
	static DWORD PrintPlayerViewHPAddress1 = MAIN_OFFSET_PRINT_PLAYER_VIEW_HP;
	
	_asm
	{
		Mov Eax,ViewHP
		Push Eax
		Jmp [PrintPlayerViewHPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewMP()
{
	static DWORD PrintPlayerViewMPAddress1 = MAIN_OFFSET_PRINT_PLAYER_VIEW_MP;

	_asm
	{
		Mov Eax,ViewMP
		Push Eax
		Jmp [PrintPlayerViewMPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewBP()
{
	static DWORD PrintPlayerViewBPAddress1 = MAIN_OFFSET_PRINT_PLAYER_VIEW_BP;

	_asm
	{
		Mov Eax,ViewAG
		Push Eax
		Jmp [PrintPlayerViewBPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewSD()
{
	static DWORD PrintPlayerViewSDAddress1 = MAIN_OFFSET_PRINT_PLAYER_VIEW_SD;

	_asm
	{
		Mov Eax,ViewSD
		Push Eax
		Jmp [PrintPlayerViewSDAddress1]
	}
}

__declspec(naked) void PrintPlayerViewMaxHP()
{
	static DWORD PrintPlayerViewHPAddress1 = MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_HP;

	_asm
	{
		Mov Eax,ViewMaxHP
		Push Eax
		Jmp [PrintPlayerViewHPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewMaxMP()
{
	static DWORD PrintPlayerViewMPAddress1 = MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_MP;

	_asm
	{
		Mov Eax,ViewMaxMP
		Push Eax
		Jmp [PrintPlayerViewMPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewMaxBP()
{
	static DWORD PrintPlayerViewBPAddress1 = MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_BP;

	_asm
	{
		Mov Eax,ViewMaxAG
		Push Eax
		Jmp [PrintPlayerViewBPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewMaxSD()
{
	static DWORD PrintPlayerViewSDAddress1 = MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_SD;

	_asm
	{
		Mov Eax,ViewMaxSD
		Push Eax
		Jmp [PrintPlayerViewSDAddress1]
	}
}