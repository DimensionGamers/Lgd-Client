#ifndef PACKET_ENCDEC_H
#define PACKET_ENCDEC_H

#pragma once

enum
{
	ENCODE_DECODE_KEY_1,
	ENCODE_DECODE_KEY_2,
	ENCODE_DECODE_SERIAL,
	ENCODE_DECODE_SIZE
};

#define MAX_KEY_1					8
#define MAX_KEY_2					8

static const BYTE key_1[MAX_KEY_1] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; ///- COPY SERVER DATA
static const BYTE key_2[MAX_KEY_2] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; ///- COPY SERVER DATA

static const BYTE key_final[MAX_KEY_1][MAX_KEY_2] = 
{
	0x22, 0x8F, 0x3B, 0x0A, 0x8E, 0x6A, 0x51, 0x32,
	0xBA, 0xCC, 0xAA, 0xBF, 0xFB, 0x54, 0x24, 0x47,
	0x00, 0xA1, 0x21, 0x02, 0x02, 0x21, 0xAB, 0x9F,
	0xFE, 0x3A, 0xB0, 0x86, 0xBA, 0xAF, 0x34, 0x55,
	0xCB, 0x63, 0x8D, 0xEA, 0x56, 0xE8, 0x51, 0x29,
	0x7D, 0x2B, 0x5F, 0xC3, 0xB1, 0xE9, 0x8A, 0xFB,
	0xBC, 0x89, 0x9F, 0xB2, 0xE7, 0x23, 0xA8, 0x3A,
	0x6D, 0xFF, 0x5C, 0x58, 0x8B, 0x25, 0xAF, 0x62
};

class EncodeDecode
{
	public:
		EncodeDecode(): SerialSEND(0), SerialRECV(0)
		{

		}

		bool Encode(const BYTE * source, BYTE * encoded, DWORD & size);
		bool Decode(BYTE * source, BYTE * decoded, DWORD & size);
		bool DecodePC(BYTE * source, BYTE * decoded, DWORD & size);
		bool GetKey1(BYTE key, BYTE & position);
		bool GetKey2(BYTE key, BYTE & position);

		BYTE SerialSEND;
		BYTE SerialRECV;
};

extern EncodeDecode g_EncodeDecode;

// ===============================================================================================
// ===============================================================================================
// ===============================================================================================
// ===============================================================================================

#define MU_PACKET( buf_ptr) (muPacket*)buf_ptr
#define MU_REFPKT( pkt_ptr) (*pkt_ptr)

class muPacket
{
	public:
		muPacket()
		{
		}

		~muPacket()
		{
		}

	public:

	inline unsigned char* packet()
	{
		return ((unsigned char*)this);
	}

	inline unsigned char& packet( unsigned short i)
	{
		return ((unsigned char*)this)[i];
	}

	inline void packet( void* out_buf, unsigned short offset, unsigned short bytes) 
	{
		memcpy( out_buf, &this->packet()[offset], bytes);
	}

	inline unsigned char hdr()
	{
		return this->packet()[0];
	}

	unsigned short size() 
	{
		unsigned char* buf =(unsigned char*)this;
		if( buf[0] ==0xC1 || buf[0] ==0xC3)
		return (unsigned short)buf[1];
		else if( buf[0] ==0xC2 || buf[0] ==0xC4)
		return (((unsigned short)buf[1] << 8) | (unsigned short)buf[2]);
		// shouldn't occur
		return 0;
	}

	inline unsigned char *contents() 
	{
		return &(this->packet()[this->hdrSize()]);
	}
	
	inline unsigned char& contents( unsigned short i)
	{
		return this->packet()[this->hdrSize()+i];
	}

	inline void contents( void* out_buf, unsigned short offset, unsigned short bytes)
	{
		memcpy( out_buf, &(this->contents()[offset]), bytes);
	}
	
	inline unsigned short contentSize() 
	{
		return( this->size() -this->hdrSize());
	}
	
	inline unsigned char opc() 
	{
		return( this->operator()( 0));
	}
	
	unsigned char hdrSize() 
	{
		unsigned char* buf =(unsigned char*)this;
		if( buf[0] ==0xC1 || buf[0] ==0xC3)
		return 2;
		else if( buf[0] ==0xC2 || buf[0] ==0xC4)
		return 3;
		// shouldn't occur
		return 0;
	}

	public:
	// iterates whole packet
	inline unsigned char& operator[]( unsigned short i) 
	{
		return this->packet()[i];
	}
	// iterates contents
	inline unsigned char& operator()( unsigned short i) 
	{
		return this->packet()[i +this->hdrSize()];
	}
	// returns pointer to packet
	inline operator unsigned char*() 
	{
		return this->packet();
	}
};

void MuXor3Byte( unsigned char* ptr, unsigned int len);
extern void MU_EncodeC1C2( muPacket* packet);
extern void MU_DecodeC1C2( muPacket* packet);
extern unsigned short MuPacketEncSpace( muPacket* pkt);
extern unsigned short MuPacketDecSpace( muPacket* pkt);

#endif