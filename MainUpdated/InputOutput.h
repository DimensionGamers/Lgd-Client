#ifndef _INPUT_OUTPUT_H_
#define _INPUT_OUTPUT_H_

#pragma once

class InputOutput
{
	public:
		InputOutput(): KeyboardHook(NULL), ThreadHandle(NULL), UpdateThreadHandle(NULL)
		{
			this->render_fix_1 = false;
			this->render_fix_2 = false;
			this->render_fix_3 = false;
		}

		virtual ~InputOutput() { }

		bool Init(HINSTANCE hInst);
		BOOL KeyboardSetHook(bool set_or_clear);
		void FreeMemory();

		void CreateUpdateThread();

		bool render_fix_1;
		bool render_fix_2;
		bool render_fix_3;
	private:
		HHOOK KeyboardHook;
		HANDLE ThreadHandle;
		HANDLE UpdateThreadHandle;

		static LRESULT CALLBACK KeyboardProc(int, WPARAM, LPARAM);

	public:
		static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};

extern InputOutput sInputOutput;

#endif