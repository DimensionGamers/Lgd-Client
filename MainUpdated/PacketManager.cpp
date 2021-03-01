// PacketManager.cpp: implementation of the CPacketManager class.
//
//////////////////////////////////////////////////////////////////////

CPacketManager gPacketManager;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPacketManager::CPacketManager() // OK
{
	this->Init();
}

CPacketManager::~CPacketManager() // OK
{

}

void CPacketManager::Init() // OK
{
	memset(this->m_buff,0,sizeof(this->m_buff));

	this->m_size = 0;

	this->m_XorFilter[0] = 0xAB;
	this->m_XorFilter[1] = 0x11;
	this->m_XorFilter[2] = 0xCD;
	this->m_XorFilter[3] = 0xFE;
	this->m_XorFilter[4] = 0x18;
	this->m_XorFilter[5] = 0x23;
	this->m_XorFilter[6] = 0xC5;
	this->m_XorFilter[7] = 0xA3;
	this->m_XorFilter[8] = 0xCA;
	this->m_XorFilter[9] = 0x33;
	this->m_XorFilter[10] = 0xC1;
	this->m_XorFilter[11] = 0xCC;
	this->m_XorFilter[12] = 0x66;
	this->m_XorFilter[13] = 0x67;
	this->m_XorFilter[14] = 0x21;
	this->m_XorFilter[15] = 0xF3;
	this->m_XorFilter[16] = 0x32;
	this->m_XorFilter[17] = 0x12;
	this->m_XorFilter[18] = 0x15;
	this->m_XorFilter[19] = 0x35;
	this->m_XorFilter[20] = 0x29;
	this->m_XorFilter[21] = 0xFF;
	this->m_XorFilter[22] = 0xFE;
	this->m_XorFilter[23] = 0x1D;
	this->m_XorFilter[24] = 0x44;
	this->m_XorFilter[25] = 0xEF;
	this->m_XorFilter[26] = 0xCD;
	this->m_XorFilter[27] = 0x41;
	this->m_XorFilter[28] = 0x26;
	this->m_XorFilter[29] = 0x3C;
	this->m_XorFilter[30] = 0x4E;
	this->m_XorFilter[31] = 0x4D;
}

bool CPacketManager::AddData(BYTE* lpBuff,int size) // OK
{
	if(size <= 0 || size >= 2048)
	{
		return 0;
	}

	memcpy(this->m_buff,lpBuff,size);
	this->m_size = size;
	return 1;
}

bool CPacketManager::ExtractPacket(BYTE* lpBuff) // OK
{
	int size,end;

	switch(this->m_buff[0])
	{
		case 0xC1:
		case 0xC3:
			size = this->m_buff[1];
			end = 2;
			break;
		case 0xC2:
		case 0xC4:
			size = MAKEWORD(this->m_buff[2],this->m_buff[1]);
			end = 3;
			break;
		default:
			return 0;
	}

	if(this->m_size < ((DWORD)size))
	{
		return 0;
	}

	this->XorData((end+1),size);

	memcpy(lpBuff,this->m_buff,size);

	return 1;
}

void CPacketManager::XorData(int start,int end) // OK
{
	if(start > end)
	{
		return;
	}

	for(int n=start;n < end;n++)
	{
		this->m_buff[n] ^= this->m_buff[n-1]^this->m_XorFilter[n%32];
	}
}

bool CPacketManager::Process(BYTE* buffer, DWORD size, BYTE * buffer_final)
{
	this->m_size = 0;
	memset(this->m_buff, 0, 8192);

	if ( !this->AddData(buffer, size) )
	{
		return false;
	}

	if ( this->ExtractData(buffer_final) != 0 )
	{
		return false;
	}

	return true;
}

BOOL CPacketManager::ExtractData(void* pTar)
{
	DWORD wSize;
	BYTE byTemp[2048];

	switch ( this->m_buff[0] )
	{
		case 0xC1:
			wSize = this->m_buff[1];
			break;

		case 0xC2:
			wSize = this->m_buff[1] * 256 + this->m_buff[2];
			break;

		default:
			return 1;
			break;
	}

	if ( this->m_size < wSize )
	{
		return 2;
	}

	this->XorData(wSize-1, (this->m_buff[0] == 0xC1 ? 2 : 3), -1);
	memcpy(pTar, this->m_buff, wSize);
	this->m_size-=wSize;
	memcpy(byTemp, &this->m_buff[wSize], this->m_size);
	memcpy(this->m_buff, byTemp, this->m_size);
	return 0;
}

void CPacketManager::XorData(int iStart, int iEnd, int iDir)
{
	if ( iStart < iEnd  )
	{
		return;
	}

	for ( int i = iStart ; i != iEnd ; i+=iDir )
	{
		this->m_buff[i] ^= this->m_buff[i-1] ^ this->m_XorFilter[ i%32 ];
	}
}