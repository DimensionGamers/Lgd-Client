#ifndef HACK_CHECK_H
#define HACK_CHECK_H

#pragma once
struct OffsetData
{
	OffsetData()
	{
		this->offset = 0;
		this->data = 0;
		this->fix = 0;
	}

	DWORD offset;
	BYTE data;
	BYTE fix;
};

typedef std::map<DWORD, OffsetData> OffsetDataMap;

struct OffsetFPS
{
	OffsetFPS()
	{
		this->offset = 0;
		this->mod = 0;
		this->original = 0;
	}

	DWORD offset;
	BYTE mod;
	BYTE original;
};

typedef std::map<DWORD, OffsetFPS> OffsetFPSMap;
extern OffsetFPSMap offset_fps_map;

typedef std::map<DWORD, BYTE> OffsetAntiHackMap;
extern OffsetAntiHackMap offset_antihack_map;

DWORD getMSTimeMain();
DWORD getMSTimeDiff(DWORD oldMSTime, DWORD newMSTime);
DWORD GetMSTimeDiffToNow(DWORD oldMSTime);

void CGHackCheckByteModified(DWORD offset, BYTE move, BYTE value);
void CGHackCheckDoubleModified(DWORD offset, double value);
void AddOffsetData(BYTE * Packet);

void MainLoopInit();
void ApplyAntiCheat();

void CheckNotPatched(const char* szDll, const char* szFunc,int mode,BYTE id);
void FrameCheck();
void CGMainFramePing();

#endif