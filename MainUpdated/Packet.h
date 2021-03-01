#ifndef PACKET_H
#define PACKET_H

#pragma once

#pragma pack(1)
struct PBMSG_HEAD
{
	void set(BYTE head,BYTE size) // OK
	{
		this->type = 0xC1;
		this->size = size;
		this->head = head;
	}

	void setE(BYTE head,BYTE size) // OK
	{
		this->type = 0xC3;
		this->size = size;
		this->head = head;
	}

	BYTE type;
	BYTE size;
	BYTE head;
};

struct PSBMSG_HEAD
{
	void set(BYTE head,BYTE subh,BYTE size) // OK
	{
		this->type = 0xC1;
		this->size = size;
		this->head = head;
		this->subh = subh;
	}

	void setE(BYTE head,BYTE subh,BYTE size) // OK
	{
		this->type = 0xC3;
		this->size = size;
		this->head = head;
		this->subh = subh;
	}

	BYTE type;
	BYTE size;
	BYTE head;
	BYTE subh;
};

struct PWMSG_HEAD
{
	void set(BYTE head, WORD size) // OK
	{
		this->type = 0xC2;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
	}

	void setE(BYTE head,WORD size) // OK
	{
		this->type = 0xC4;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
	}

	BYTE type;
	BYTE size[2];
	BYTE head;
};

struct PSWMSG_HEAD
{
	void set(BYTE head,BYTE subh,WORD size) // OK
	{
		this->type = 0xC2;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
		this->subh = subh;
	}

	void setE(BYTE head,BYTE subh,WORD size) // OK
	{
		this->type = 0xC4;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
		this->subh = subh;
	}

	WORD get_size() const { return MAKE_NUMBERW(this->size[0], this->size[1]); }

	BYTE type;
	BYTE size[2];
	BYTE head;
	BYTE subh;
};

struct C1_HEADER
{
public:

	void Set(BYTE head, BYTE size)
	{
		this->pct_id = 0xC1;
		this->pct_size = size;
		this->pct_headcode = head;
	};

	BYTE GetSize() const { return this->pct_size; }

	BYTE pct_id;
	BYTE pct_size;
	BYTE pct_headcode;
};

struct C1_HEADER_SUB : C1_HEADER
{
public:

	void Set(BYTE head, BYTE sub, BYTE size)
	{
		this->C1_HEADER::Set(head, size);
		this->pct_subcode = sub;
	};

	BYTE pct_subcode;
};

struct C2_HEADER
{
public:

	void Set(BYTE head, WORD size)
	{
		this->pct_id = 0xC2;
		this->SetSize(size);
		this->pct_headcode = head;
	};

	void SetSize(WORD size)
	{
		this->pct_size[0] = SET_NUMBERH(size);
		this->pct_size[1] = SET_NUMBERL(size);
	}

	WORD GetSize() const { return MAKE_NUMBERW(this->pct_size[0], this->pct_size[1]); }

	BYTE pct_id;
	BYTE pct_size[2];
	BYTE pct_headcode;
};

struct C2_HEADER_SUB : C2_HEADER
{
public:

	void Set(BYTE head, BYTE sub, WORD size)
	{
		this->C2_HEADER::Set(head, size);
		this->pct_subcode = sub;
	};

	BYTE pct_subcode;
};
#pragma pack()


#pragma pack(1)
struct PACKET_ANTI_MACRO : C1_HEADER_SUB
{
	uint8 enabled;
	uint32 time;
	uint8 combo_enabled;
	uint32 combo_time;
};

struct PACKET_ANTI_MACRO_DETECT : C1_HEADER_SUB
{
	PACKET_ANTI_MACRO_DETECT()
	{
		this->Set(0xF3, 204, sizeof(PACKET_ANTI_MACRO_DETECT));
		this->type = 0;
	}

	uint8 type;
};
#pragma pack()

#endif