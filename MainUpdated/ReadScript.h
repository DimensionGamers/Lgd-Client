#ifndef	_READ_SCRIPT_H_
#define	_READ_SCRIPT_H_

enum SMDToken 
{
	NAME, 
	NUMBER, 
	END, 
	COMMAND = '#',
	LP = '{',
	RP = '}',
	COMMA = ',',
	SEMICOLON = ';',
	SMD_ERROR
};

class ReadScript
{
	public:
		ReadScript(const char* filename, const char* mode)
		{
			this->m_filename = filename;
			this->fp = fopen(filename,mode);
		}
		~ReadScript()
		{
			this->close();
		}

		bool open() const { return this->fp != NULL; }
		void close() { if ( this->fp ) fclose(this->fp); }

		SMDToken GetToken();

		bool IsEnd(const char * end)
		{
			return !strcmp(end,this->TokenString);
		}

		void LogOpenError();

		BYTE GetUInt8() const { return static_cast<BYTE>(this->TokenNumber); }
		WORD GetUInt16() const { return static_cast<WORD>(this->TokenNumber); }
		DWORD GetUInt32() const { return static_cast<DWORD>(this->TokenNumber); }
		bool GetBool() const { return this->GetUInt8() == 1 ? true: false; }

		char GetInt8() const { return static_cast<char>(this->TokenNumber); }
		short GetInt16() const { return static_cast<short>(this->TokenNumber); }
		int GetInt32() const { return static_cast<int>(this->TokenNumber); }
	public:
		FILE* fp;
		float TokenNumber;
		char TokenString[100];
		SMDToken CurrentToken;
		std::string m_filename;
};

#endif