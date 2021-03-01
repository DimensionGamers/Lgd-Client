#ifndef PACKET_MANAGER_H
#define PACKET_MANAGER_H

#pragma once

class CPacketManager
{
public:
	CPacketManager();
	virtual ~CPacketManager();
	void Init();
	bool AddData(BYTE* lpBuff,int size);
	bool ExtractPacket(BYTE* lpBuff);
	void XorData(int start,int end);

	bool Process(BYTE* buffer, DWORD size, BYTE * buffer_final);
	BOOL ExtractData(void* pTar);
	void XorData(int iStart, int iEnd, int iDir);
private:
	BYTE m_buff[2048];
	DWORD m_size;
	BYTE m_XorFilter[32];
};

extern CPacketManager gPacketManager;

#endif