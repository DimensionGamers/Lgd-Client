#ifndef DEFINES_H
#define DEFINES_H

#pragma once

#define MAX_WIN_WIDTH 640
#define MAX_WIN_HEIGHT 480
#define MAX_MAIN_VIEWPORT 400

typedef __int64 int64;
typedef int int32;
typedef short int16;
typedef char int8;
typedef unsigned __int64 uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

#define SET_NUMBERH(x) ( (BYTE)((WORD)(x)>>(WORD)8) )
#define SET_NUMBERL(x) ( (BYTE)((WORD)(x) & 0xFF) )
#define SET_NUMBERHB(x) ((BYTE)((DWORD)(x)>>(DWORD)8))
#define SET_NUMBERLB(x) ((BYTE)((DWORD)(x)&0xFF))
#define SET_NUMBERHW(x) ((WORD)((DWORD)(x)>>(DWORD)16))
#define SET_NUMBERLW(x) ((WORD)((DWORD)(x)&0xFFFF))
#define SET_NUMBERHDW(x) ((DWORD)((uint64)(x)>>(QWORD)32))
#define SET_NUMBERLDW(x) ((DWORD)((uint64)(x)&0xFFFFFFFF))

#define MAKE_NUMBERW(x,y) ((WORD)(((BYTE)((y)&0xFF))|((BYTE)((x)&0xFF)<<8)))
#define MAKE_NUMBERDW(x,y) ((DWORD)(((WORD)((y)&0xFFFF))|((WORD)((x)&0xFFFF)<<16)))
#define MAKE_NUMBERQW(x,y) ((uint64)(((DWORD)((y)&0xFFFFFFFF))|((DWORD)((x)&0xFFFFFFFF)<<32)))
#define MAKE_NUMBERQW2(x,y) ((__int64)(((long)((y)&0xFFFFFFFF))|((long)((x)&0xFFFFFFFF)<<32)))

#define GET_HEADCODE(Packet) (Packet[0] == 0xC1 || Packet[0] == 0xC3) ? Packet[2] : (Packet[0] == 0xC2 || Packet[0] == 0xC4) ? Packet[3]: 0xFF;
#define GET_SUBCODE(Packet) (Packet[0] == 0xC1 || Packet[0] == 0xC3) ? Packet[3] : (Packet[0] == 0xC2 || Packet[0] == 0xC4) ? Packet[4]: 0xFF;

enum TimeConstants
{
    MINUTE = 60,
    HOUR   = MINUTE * 60,
    DAY    = HOUR * 24,
    WEEK   = DAY * 7,
    MONTH  = DAY * 30,
    YEAR   = MONTH * 12,
    IN_MILLISECONDS = 1000
};

#define ARG(DEST, SOURCE) \
	char DEST[2048]; \
	::memset(DEST, 0, sizeof(DEST)); \
	va_list pArguments; \
	va_start(pArguments, SOURCE); \
	vsprintf_s(DEST, SOURCE, pArguments); \
	va_end(pArguments);

#define SAFE_DELETE_2008(p) if(p != NULL){delete p; p = NULL;}
#define SAFE_DELETE_ARRAY_2008(p) if((p)!=NULL){delete[] (p);(p)=NULL;}

#define DECLARE_BOOL(name)	\
	protected: \
		bool m_propb##name; \
	public: \
		bool Is##name() const { return this->m_propb##name; } \
		void Set##name(bool value) { this->m_propb##name = value; }

#define DECLARE_ENUM(type, name)	\
	protected: \
		##type m_prop##name; \
	public: \
		##type Get##name() const { return this->m_prop##name; } \
		void Set##name(##type value) { this->m_prop##name = value; }

#define DECLARE_PTR(type, name)	\
	protected: \
		##type* m_prop##name; \
	public: \
		##type* Get##name() { return this->m_prop##name; } \
		##type* Get##name() const { return this->m_prop##name; } \
		void Set##name(##type* value) { this->m_prop##name = value; } \
		void Erase##name() { SAFE_DELETE_2008(this->m_prop##name); }

#define DECLARE_ARRAY_STRUCT(type, name, size)	\
	protected: \
		##type m_prop##name[size]; \
	public: \
		##type* Get##name(unsigned int dwPosition) { return &this->m_prop##name[dwPosition]; } \
		##type const* Get##name(unsigned int dwPosition) const { return &this->m_prop##name[dwPosition]; } \
		##type* Get##name##Ptr() { return &this->m_prop##name[0]; } \
		##type const* Get##name##Ptr() const { return &this->m_prop##name[0]; } \
		void Set##name(unsigned int dwPosition, type const& value) { this->m_prop##name[dwPosition] = value; }

#define LIST_CLEAR(list_it, list) \
	for ( list_it clear_list = list.begin(); clear_list != list.end(); ++clear_list ) {\
		SAFE_DELETE_2008(*clear_list); }\
	list.clear();	

#define MAP_CLEAR(list_it, list) \
	for ( list_it clear_list = list.begin(); clear_list != list.end(); ++clear_list ) { \
		SAFE_DELETE_2008(clear_list->second); }\
	list.clear();

#endif