#ifndef PRINT_PLAYER_H
#define PRINT_PLAYER_H

#pragma once

void InitPrintPlayer();

void PrintPlayerViewHP();
void PrintPlayerViewMP();
void PrintPlayerViewBP();
void PrintPlayerViewSD();

void PrintPlayerViewMaxHP();
void PrintPlayerViewMaxMP();
void PrintPlayerViewMaxBP();
void PrintPlayerViewMaxSD();

extern DWORD ViewIndex;
extern DWORD ViewHP;
extern DWORD ViewSD;
extern DWORD ViewMP;
extern DWORD ViewAG;

extern DWORD ViewMaxHP;
extern DWORD ViewMaxSD;
extern DWORD ViewMaxMP;
extern DWORD ViewMaxAG;

#endif