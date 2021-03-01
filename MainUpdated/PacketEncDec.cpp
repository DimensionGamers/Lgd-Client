EncodeDecode g_EncodeDecode;

int LastKey1 = -1;
int LastKey2 = -1;

bool EncodeDecode::Encode(const BYTE * source, BYTE * encoded, DWORD & size)
{
	if ( !source || !encoded || size < 3 )
	{
		return false;
	}

	int rand_1 = -1;
	int rand_2 = -1;

	do
	{
		rand_1 = rand()%MAX_KEY_1;
		rand_2 = rand()%MAX_KEY_2;
	}
	while(LastKey1 == rand_1 || LastKey2 == rand_2);

	LastKey1 = rand_1;
	LastKey2 = rand_2;

	encoded[ENCODE_DECODE_KEY_1] = key_1[rand_1];
	encoded[ENCODE_DECODE_KEY_2] = key_2[rand_2];
	encoded[ENCODE_DECODE_SERIAL] = SerialSEND++;
	encoded[ENCODE_DECODE_SERIAL] -= key_final[rand_1][rand_2];

	for ( WORD i = 0; i < size; ++i )
	{
		encoded[i + ENCODE_DECODE_SIZE] = source[i] - key_final[rand_1][rand_2];
	}

	size += ENCODE_DECODE_SIZE;

	return true;
}
	
bool EncodeDecode::Decode(BYTE * source, BYTE * decoded, DWORD & size)
{
	size = 0;

	if ( !source || !decoded )
		return false;

	BYTE tmp_key_1 = source[ENCODE_DECODE_KEY_1];
	BYTE tmp_key_2 = source[ENCODE_DECODE_KEY_2];
	BYTE position_1 = 0;
	BYTE position_2 = 0;

	if ( !this->GetKey1(tmp_key_1, position_1) || !this->GetKey2(tmp_key_2, position_2) )
	{
		return false;
	}

	BYTE header = decoded[0] = (source[ENCODE_DECODE_SIZE] + key_final[position_1][position_2]);
	size = 0;

	if ( header == 0xC1 || header == 0xC3 )
	{
		size = decoded[1] = (source[ENCODE_DECODE_SIZE + 1] + key_final[position_1][position_2]);

		for ( WORD i = 2; i < size; ++i )
		{
			decoded[i] = source[ENCODE_DECODE_SIZE + i] + key_final[position_1][position_2];
		}
	}
	else if ( header == 0xC2 || header == 0xC4 )
	{
		decoded[1] = (source[ENCODE_DECODE_SIZE + 1] + key_final[position_1][position_2]);
		decoded[2] = (source[ENCODE_DECODE_SIZE + 2] + key_final[position_1][position_2]);

		size = decoded[1] * 256 + decoded[2];

		for ( WORD i = 3; i < size; ++i )
		{
			decoded[i] = source[ENCODE_DECODE_SIZE + i] + key_final[position_1][position_2];
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool EncodeDecode::DecodePC(BYTE * source, BYTE * decoded, DWORD & size)
{
	if ( !source || !decoded )
	{
		return false;
	}

	BYTE header = decoded[0] = source[0];
	size = 0;
	int add = 0;

	if ( header == 0xC1 || header == 0xC3 )
	{
		add = 2;

		BYTE tmp_key_1 = source[ENCODE_DECODE_KEY_1 + add];
		BYTE tmp_key_2 = source[ENCODE_DECODE_KEY_2 + add];
		BYTE position_1 = 0;
		BYTE position_2 = 0;

		if ( !this->GetKey1(tmp_key_1, position_1) || !this->GetKey2(tmp_key_2, position_2) )
		{
			return false;
		}

		size = decoded[1] = source[1];

		for ( WORD i = 2; i < size; ++i )
		{
			decoded[i] = source[ENCODE_DECODE_SIZE + i + add] + key_final[position_1][position_2];
		}
	}
	else if ( header == 0xC2 || header == 0xC4 )
	{
		add = 3;

		BYTE tmp_key_1 = source[ENCODE_DECODE_KEY_1 + add];
		BYTE tmp_key_2 = source[ENCODE_DECODE_KEY_2 + add];
		BYTE position_1 = 0;
		BYTE position_2 = 0;

		if ( !this->GetKey1(tmp_key_1, position_1) || !this->GetKey2(tmp_key_2, position_2) )
		{
			return false;
		}

		decoded[1] = source[1];
		decoded[2] = source[2];

		size = decoded[1] * 256 + decoded[2];

		for ( WORD i = 3; i < size; ++i )
		{
			decoded[i] = source[ENCODE_DECODE_SIZE + i + add] + key_final[position_1][position_2];
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool EncodeDecode::GetKey1(BYTE key, BYTE & position)
{
	for ( BYTE i = 0; i < MAX_KEY_1; ++i )
	{
		if ( key_1[i] == key )
		{
			position = i;
			return true;
		}
	}
	
	return false;
}

bool EncodeDecode::GetKey2(BYTE key, BYTE & position)
{
	for ( BYTE i = 0; i < MAX_KEY_2; ++i )
	{
		if ( key_2[i] == key )
		{
			position = i;
			return true;
		}
	}
	
	return false;
}

// ===============================================================================================
// ===============================================================================================
// ===============================================================================================
// ===============================================================================================

const unsigned char xor_tab_C1C2[32] = {
		0xAB, 0x11, 0xCD, 0xFE, 0x18, 0x23, 0xC5, 0xA3,
		0xCA, 0x33, 0xC1, 0xCC, 0x66, 0x67, 0x21, 0xF3,
		0x32, 0x12, 0x15, 0x35, 0x29, 0xFF, 0xFE, 0x1D,
		0x44, 0xEF, 0xCD, 0x41,	0x26, 0x3C, 0x4E, 0x4D
};

inline unsigned short MuPacketEncSpace( muPacket* pkt)
{
	return((( pkt->contentSize() /8) +(((pkt->contentSize() %8) >0) ? 1 : 0)) *11) +pkt->hdrSize();
}

inline unsigned short MuPacketDecSpace( muPacket* pkt) 
{
	return(( pkt->contentSize() /11) *8) +pkt->hdrSize() -1;
}
// (if C1, offset = 2), (if C2, offset = 3)
void MU_ForceEncodeC1C2( unsigned char* buf, unsigned short len, unsigned short offset =2)
{
	for( unsigned short p =1; p < len; ++p)
	{
		buf[p] ^= buf[p-1] ^ xor_tab_C1C2[(p+offset) %32];
	}
	
}
// (if C1, offset = 2), (if C2, offset = 3)
void MU_ForceDecodeC1C2( unsigned char* buf, unsigned short len, unsigned short offset =2) 
{
	--len;
	for( unsigned short p =len; p > 0; --p)
		buf[p] ^= buf[p-1] ^ xor_tab_C1C2[(p+offset) %32];
}
// encode c1/c2 packet
inline void MU_EncodeC1C2( muPacket* packet) 
{
	MU_ForceEncodeC1C2( packet->contents(), packet->contentSize(), packet->hdrSize());
}
// decode c1/c2 packet
inline void MU_DecodeC1C2( muPacket* packet) 
{
	MU_ForceDecodeC1C2( packet->contents(), packet->contentSize(), packet->hdrSize());
}