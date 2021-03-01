#ifndef ITEM_H
#define ITEM_H

#pragma once

#define MAX_ITEM_TYPE 512

#define ITEM_BASE_MODEL		1583
#define ITEM_X				93
#define ITEM_Y				94
#define ITEM_EXPIRE_STATUS	134
#define ITEM_EXPIRED		135

#pragma pack(1)
struct ItemData
{
	DWORD item_info_ptr; //0
	WORD data4;//4
	WORD data6;//6
	WORD data8;//8
	WORD data10;//10
	WORD data12; //12
	WORD required_level; //14
	DWORD item; //16
	DWORD attributes; //20
	BYTE data24; //24
	BYTE data25; //25
	BYTE data26; //26
	BYTE data27; //27
	WORD damage_min; //28
	WORD damage_max; //30
	BYTE defense_success_rate; //32
	BYTE data33; //33
	WORD defense; //34
	WORD defense_magic; //36
	BYTE unk38[2]; //38
	DWORD power; //40
	BYTE data44; //44
	BYTE data45; //45
	WORD data46; //46
	BYTE durability; //48
	BYTE durability_max; //49
	BYTE raw_excellent; //50
	BYTE ancient; //51
	BYTE excellent; //52
	BYTE option_count; //53
	WORD option_id[8]; //54
	WORD option_value[8]; //70
	WORD skill; //86
	DWORD data88; //88
	BYTE data92; //92
	BYTE x; //93
	BYTE y; //94
	BYTE data95; //95
	WORD harmony_id; //96
	WORD harmony_level; //98
	BYTE option_pvp; //100
	BYTE raw_socket[5]; //101
	BYTE mountable_slots; //106
	BYTE socket_id[5]; //107
	BYTE socket_level[5]; //112
	BYTE socket_bonus; //117
	BYTE unk118[2]; //118
	DWORD elemental_attribute; //120
	DWORD errtel_rank; //124
	BYTE unk124[5]; //128
	BYTE data133; //133
	BYTE expire_status; //134
	BYTE expired; //135
	time_t expire_date; //136
	BYTE data140; //140
	BYTE mastery_excellent[9]; //141
	BYTE data150; //150
	BYTE data151; //151
	DWORD data152; //152
	BYTE unk156[20]; //156
	DWORD data176; //176
	BYTE unk180[20]; //180
	DWORD data200; //200
	BYTE unk204[20]; //204
	DWORD data224; //224
	BYTE unk228[24]; //228
	DWORD data252; //252
};
#pragma pack()
#define GET_ITEM(x,y) (((x)*MAX_ITEM_TYPE)+(y))
#define GET_ITEM_MODEL(x,y) ((((x)*MAX_ITEM_TYPE)+(y))+ITEM_BASE_MODEL)

void InitItem();

extern DWORD ShopPrice[120];
extern BYTE ShopType;
void SetShopPrice(BYTE * Packet);

char* GetItemName(uint8 type, uint16 index);
char* GetItemNameSingle(uint16 item);

#endif