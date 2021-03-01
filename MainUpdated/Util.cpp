void SetByte(DWORD offset,BYTE value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,1,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(BYTE*)(offset) = value;

	VirtualProtect((void*)offset,1,OldProtect,&OldProtect);
}

void SetByteUnsafe(DWORD offset,BYTE value) // OK
{
	*(BYTE*)(offset) = value;
}

void SetWord(DWORD offset,WORD value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,2,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(WORD*)(offset) = value;

	VirtualProtect((void*)offset,2,OldProtect,&OldProtect);
}

void SetDword(DWORD offset,DWORD value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,4,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(DWORD*)(offset) = value;

	VirtualProtect((void*)offset,4,OldProtect,&OldProtect);
}

void SetFloat(DWORD offset,float value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,4,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(float*)(offset) = value;

	VirtualProtect((void*)offset,4,OldProtect,&OldProtect);
}

void SetDouble(DWORD offset,double value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,8,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(double*)(offset) = value;

	VirtualProtect((void*)offset,8,OldProtect,&OldProtect);
}

void SetCompleteHook(BYTE head,DWORD offset,...) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,5,PAGE_EXECUTE_READWRITE,&OldProtect);

	if(head != 0xFF)
	{
		*(BYTE*)(offset) = head;
	}

	DWORD* function = &offset+1;

	*(DWORD*)(offset+1) = (*function)-(offset+5);

	VirtualProtect((void*)offset,5,OldProtect,&OldProtect);
}

void SetCompleteHookUnsafe(BYTE head,DWORD offset,...) // OK
{
	if(head != 0xFF)
	{
		*(BYTE*)(offset) = head;
	}

	DWORD* function = &offset+1;

	*(DWORD*)(offset+1) = (*function)-(offset+5);
}

void MemoryCpy(DWORD offset,void* value,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	memcpy((void*)offset,value,size);

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void MemorySet(DWORD offset,DWORD value,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	memset((void*)offset,value,size);

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

LPVOID HookFunction(const LPVOID offset, LPVOID function, DWORD size)
{
	LPVOID newf = malloc(size + 6);

	DWORD OldProtect;

	VirtualProtect(offset, size, PAGE_EXECUTE_READWRITE, &OldProtect);

	memcpy(newf, offset, size);

	PBYTE j = (PBYTE)((DWORD)newf + size);

	j[0] = 0x68;

	*(DWORD*)&j[1] = (DWORD)((DWORD)offset + size);

	j[5] = 0xC3;

	j = (PBYTE)offset;

	j[0] = 0x68;

	*(DWORD*)&j[1] = (DWORD)(DWORD)function;

	j[5] = 0xC3;

	VirtualProtect(offset, size, OldProtect, &OldProtect);

	return newf;
}

void PacketArgumentEncrypt(char* out_buff,char* in_buff,int size) // OK
{
	BYTE XorTable[3] = {0xFC,0xCF,0xAB};

	for(int n=0;n < size;n++)
	{
		out_buff[n] = in_buff[n]^XorTable[n%3];
	}
}

void Xor::BMD(uint8 * info, int32 Size)
{
	static const uint8 Key_1[KEY_SIZE_1]				= { 0xFC, 0xCF, 0xAB };

	for ( int32 i = 0; i < Size; ++i )
	{
		info[i] ^= Key_1[i % KEY_SIZE_1];
	}
}

void Xor::Byte3(char * info, int32 Size)
{
	static const uint8 Key_1[KEY_SIZE_1]				= { 0xFC, 0xCF, 0xAB };

	for ( int32 i = 0; i < Size; ++i )
	{
		info[i] ^= Key_1[i % KEY_SIZE_1];
	}
}

void Xor::LangXor(char * info, int32 Size, uint16 key)
{
	static const uint8 Key_1[KEY_SIZE_1] = { 0xFC, 0xCF, 0xAB };

	for (int32 i = 0; i < Size; ++i)
	{
		info[i] ^= Key_1[i % KEY_SIZE_1];
		info[i] ^= key;
	}
}

int32 Xor::Byte16(char * Source, char * Dest, int32 size)
{
	static const uint8 Key_2[KEY_SIZE_2]				= { 0xD1, 0x73, 0x52, 0xF6, 0xD2, 0x9A, 0xCB, 0x27, 0x3E, 0xAF, 0x59, 0x31, 0x37, 0xB3, 0xE7, 0xA2 };
	static const uint32 KEY_1							= 94;

	int32 key = KEY_1;

	for ( int32 i = 0; i < size; ++i )
	{
		Dest[i] = (Key_2[i % KEY_SIZE_2] ^ Source[i]) - key;
		key = Source[i] + 61;
	}

	return size;
}

void Xor::Byte20(char * src, char * dst, int32 size)
{
	static const uint8 Key_3[KEY_SIZE_3]				= { 0xD1, 0x73, 0x52, 0xF6, 0xD2, 0x9A, 0xCB, 0x27, 0x3E, 0xAF, 0x59, 0x31, 0x37, 0xB3, 0xE7, 0xA2 };

	for ( int32 i = 0; i < size; ++i )
	{
		dst[i] = (Key_3[i % KEY_SIZE_3] ^ src[i]);
	}
}

void Xor::ByteCustom(char * data, size_t size)
{
	static const uint8 Key_Custom[KEY_SIZE_CUSTOM]		= { 0xF1, 0x10, 0x23, 0x66, 0xAB };

	for ( size_t i = 0; i < size; ++i )
	{
		data[i] ^= Key_Custom[i % KEY_SIZE_CUSTOM];
	}
}

int32 Xor::Byte16New(char * Source, char * Dest, int32 size)
{
	static const uint8 Key_2[KEY_SIZE_2]				= { 0xD1, 0x73, 0x52, 0xF6, 0xD2, 0x9A, 0xCB, 0x27, 0x3E, 0xAF, 0x59, 0x31, 0x37, 0xB3, 0xE7, 0xA2 };
	static const uint32 KEY_1							= 94;

	int32 key = KEY_1;

	for ( int32 i = 0; i < size; ++i )
	{
		Dest[i] = (Key_2[i % KEY_SIZE_2] ^ Source[i]) - key;
		key = Source[i] + 61;
	}

	return size;
}

void ReplaceString(std::string &src, std::string const& search, std::string const& replace)
{
	size_t pos = -1;

	while ( true )
	{
		pos = FindString(src, search);

		if ( pos == size_t(-1) )
			break;

		src.replace(pos, search.length(), replace);
	}
}