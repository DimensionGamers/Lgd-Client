#ifndef COMMON_H
#define COMMON_H

#pragma once

void UpdateThread();
void InitCommon();

void PartyPK();
void WelcomeToWorld1();
void WelcomeToWorld2();

void GetMac(char* mac);
DWORD GetMachineID();
BOOL DataSendHOOK(BYTE * Packet, DWORD Size);
void DataSendASM(BYTE * Packet, DWORD Len);
bool CheckSocketPort(SOCKET s);
void CloseSocket();

HWND InitWindow(HINSTANCE hInstance);
extern HWND gHWND;
extern HINSTANCE gInstance;

struct TimeStruct
{
	TimeStruct()
	{
		this->Init();
	}

	void Init()
	{
		this->Tick = GetTickCount();
		this->Time = 0;
	}

	void Start(DWORD Time)
	{
		this->Tick = GetTickCount();
		this->Time = Time;
	}

	void Start()
	{
		this->Tick = GetTickCount();
	}

	bool Elapsed()
	{
		if(GetTickCount() > (this->Tick + this->Time))
		{
			return true;
		}

		return false;
	}

	DWORD GetRemain()
	{
		return GetTickCount() - this->Tick;
	}

	DWORD Tick;
	DWORD Time;
};

extern uint32 UpdateThreadTime;

struct CrownSwitchData
{
	WORD index;
	BYTE state;
	BYTE join_side;
	char guild[9];
	char name[11];

	CrownSwitchData()
	{
		this->Reset();
	}

	void Reset()
	{
		this->index = -1;
		this->state = 0;
		this->join_side = 0;
		memset(this->guild, 0, 9);
		memset(this->name, 0, 11);
	}
};

extern CrownSwitchData g_CrownSwitchData[2];
extern bool CastleSiegeMiniMap;

void PrintCrownSwitchData();
void ResetCrownSwitchData();
void ClearCrownSwitchData(void* ptr);
int CheckIntegrity();

struct PlayerCustomData
{
	PlayerCustomData()
	{
		this->Reset();
	}

	void Reset()
	{
		memset(this->attack_speed, 0, 4);
		memset(this->magic_speed, 0, 4);
	}

	BYTE attack_speed[4];
	BYTE magic_speed[4];

	DWORD GetAttackSpeed() const;
	DWORD GetMagicSpeed() const;

	bool FixSpeed();
};

extern PlayerCustomData g_PlayerCustomData;

#endif