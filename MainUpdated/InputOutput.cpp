InputOutput sInputOutput;

HINSTANCE g_hInst;

bool InputOutput::Init(HINSTANCE hInst)
{
	g_hInst = hInst;

	if ( !this->KeyboardSetHook(true) )
		return false;

	return true;
}

BOOL InputOutput::KeyboardSetHook(bool set_or_clear)
{
	if ( set_or_clear )
	{
		if( !this->KeyboardHook )
		{
			DWORD PiD = 0;
			this->KeyboardHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, g_hInst, GetCurrentThreadId());

			if( !this->KeyboardHook )
			{
				return FALSE;
			}
		}
	}
	else
	{
		return UnhookWindowsHookEx(this->KeyboardHook);
	}

	return TRUE;
}

void InputOutput::FreeMemory()
{
	this->KeyboardSetHook(false);

	if(this->ThreadHandle != NULL)
	{
		CloseHandle(this->ThreadHandle);
		this->ThreadHandle = NULL;
	}

	if(this->UpdateThreadHandle != NULL)
	{
		CloseHandle(this->UpdateThreadHandle);
		this->UpdateThreadHandle = NULL;
	}
}

LRESULT CALLBACK InputOutput::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{  
    if( ((lParam>>31)&1) && (nCode == HC_ACTION) && (GetForegroundWindow() == gHWND) )
    {
        switch(wParam)
        {
        case VK_F10:
            {
				if(GetMainState() == MAIN_STATE_PLAYING)
				{
					if ( !CC_MAP_RANGE() )
					{
						sInputOutput.render_fix_1 = !sInputOutput.render_fix_1;
						if (sInputOutput.render_fix_1) {
							SetByte(MAIN_OFFSET_RENDER_MONSTERS, 0xC3); // Render Monsters
						}
						else {
							SetByte(MAIN_OFFSET_RENDER_MONSTERS, 0x55); // Render Monsters
						}
					}
				}
            } break;

        case VK_F11:
            {
				//if(GetMainState() == MAIN_STATE_PLAYING)
				//{
					ApplyFPSOffset(!sInputOutput.render_fix_2);
				//}
            } break;

        case VK_F12:
            {
				ShowWindow(gHWND, SW_MINIMIZE);
            } break;
        }

		if (GetMainState() == MAIN_STATE_PLAYING)
		{
			g_AntiCheat.SetKeyPress(false, wParam);
		}
    }

    return CallNextHookEx(sInputOutput.KeyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK InputOutput::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if((GetForegroundWindow() == gHWND))
	{
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) lParam;
		if(nCode < 0 || (p->flags & 0x10)) 
		{
			if (GetMainState() == MAIN_STATE_PLAYING)
			{
				g_AntiCheat.SetKeyPress(true, p->vkCode);
			}
		}
	}
    
    return CallNextHookEx(NULL, nCode, wParam,lParam);
}