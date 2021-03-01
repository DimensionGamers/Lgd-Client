#ifndef GUI_MGR_H
#define GUI_MGR_H

#pragma once

typedef LPVOID(__cdecl *pCDC_This)();
extern pCDC_This CDC_This;

typedef int(__thiscall *pCDCTabbedTextOut)(LPVOID This, int x, int y, LPCTSTR lpszString, int nCount, int TabPositions, DWORD lpnTabStopPositions, int nTabOrigin);
extern pCDCTabbedTextOut MU_TabbedTextOut;

typedef DWORD(__thiscall *pCDCSetTextColor)(LPVOID This, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5);
extern pCDCSetTextColor MU_SetTextColor;

typedef DWORD(__thiscall *pCDC00420120)(LPVOID This, HGDIOBJ hFont);
extern pCDC00420120 MU_SetFont;

typedef DWORD(__thiscall *pCDC004200F0)(LPVOID This, int data);
extern pCDC004200F0 MU_4200F0;

typedef void(__cdecl *pMU_BindTexture)(DWORD Id);
extern pMU_BindTexture MU_BindTexture;

#endif