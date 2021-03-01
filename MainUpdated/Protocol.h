#ifndef PROTOCOL_H
#define PROTOCOL_H

#pragma once

enum
{
	HEADCODE_CASH_SHOP = 0xD2,
		SUBCODE_CASH_SHOP_COIN = 0x01,
		SUBCODE_CASH_SHOP_OPEN = 0x02,
		SUBCODE_CASH_SHOP_ITEM_BUY = 0x03,
		SUBCODE_CASH_SHOP_ITEM_GIFT = 0x04,
		SUBCODE_CASH_SHOP_ITEM_LIST = 0x05,
		SUBCODE_CASH_SHOP_ITEM_LIST_PAGE = 0x06,
		SUBCODE_CASH_SHOP_ITEM_USE = 0x0B,
		SUBCODE_CASH_SHOP_DATE_ITEM = 0x0C,
		SUBCODE_CASH_SHOP_ITEM_LIST_DATA_2 = 0x0D,
		SUBCODE_CASH_SHOP_ITEM_LIST_DATA_1 = 0x0E,
		SUBCODE_CASH_SHOP_ITEM_USE_NEW = 0x0F,
		SUBCODE_CASH_SHOP_ITEM_EXPIRE = 0x11,
		SUBCODE_CASH_SHOP_ITEM_EXPIRE_DATA = 0x12,
		SUBCODE_CASH_SHOP_DATE_BANNER = 0x15,
		SUBCODE_CASH_SHOP_CATEGORY = 0x16,
		SUBCODE_CASH_SHOP_PACKAGE = 0x17,
		SUBCODE_CASH_SHOP_PRODUCT = 0x18,
};

#pragma pack(1)
struct TerrainAttribute
{
	BYTE head;
	BYTE x;
	BYTE y;
	BYTE attribute[65536];
};
#pragma pack()
//**********************************************//
//************ Packet Base *********************//
//**********************************************//

struct ObjectViewport;



//**********************************************//
//************ GameServer -> Client ************//
//**********************************************//
#define CLIENT_CONNECT_CUSTOM_HEADER			0xFA

#pragma pack(1)
struct CLIENT_CONNECT_CUSTOM : C1_HEADER
{
	uint32 time;
};

struct CLIENT_CONNECT_CUSTOM_RESULT : C1_HEADER
{
	CLIENT_CONNECT_CUSTOM_RESULT()
	{
		this->Set(CLIENT_CONNECT_CUSTOM_HEADER, sizeof(CLIENT_CONNECT_CUSTOM_RESULT));
		this->result = 0;
		this->time = 0;
	}

	uint8 result;
	uint32 time;
};
#pragma pack()

#pragma pack(1)
struct CHARACTER_SELECT_REQUEST
{
	PSBMSG_HEAD h;
	char character_name[10];
	BYTE index;
};
#pragma pack()

struct HELPER_OPEN_RESULT
{
	PSBMSG_HEAD h;
	WORD spent_time; // 4
	DWORD zen; // 8
	BYTE result; // 12
};

struct PMSG_NOTICE
{
	PMSG_NOTICE()
	{
		this->h.set(0x0D, sizeof(PMSG_NOTICE) - sizeof(this->Notice));
		memset(this->Notice, 0, 200);
		this->type = 0;
		this->btCount = 0;
		this->btTest = 0;
		this->wDelay = 0;
		this->dwColor = 0;
		this->btSpeed = 0;
	}
	PBMSG_HEAD h;
	BYTE type; //3
	BYTE btCount;
	BYTE btTest;
	WORD wDelay;	
	int dwColor;
	BYTE btSpeed;
	char Notice[200];
};

#pragma pack(1)
struct PMSG_VIEWPORT_DESTROY_HEAD
{
	PBMSG_HEAD header; // C1:14
	BYTE count;
};

struct PMSG_VIEWPORT_DESTROY_BODY
{
	BYTE index[2];
};
#pragma pack()
struct PMSG_USER_DIE_RECV
{
	PBMSG_HEAD header; // C1:17
	BYTE index[2];
	BYTE skill[2];
	BYTE killer[2];
};

struct PMSG_MAP_SERVER_MOVE_RECV
{
	PSBMSG_HEAD header; // C1:B1:00
	char IpAddress[16];
	WORD ServerPort;
	WORD ServerCode;
	DWORD AuthCode1;
	DWORD AuthCode2;
	DWORD AuthCode3;
	DWORD AuthCode4;
};
#pragma pack(1)
struct SERVER_CHANGE_AUTH
{
	PSBMSG_HEAD h;
	char account[12];
	char name[12];
	DWORD auth[4];
	DWORD tick_count;
	BYTE version[5];
	BYTE serial[16];
};
#pragma pack()
struct PMSG_MAP_SERVER_MOVE_AUTH_RECV
{
	PSBMSG_HEAD header; // C1:B1:01
	BYTE result;
};

struct PMSG_CHARACTER_ATTACK_SPEED_RECV
{
	PSBMSG_HEAD header; // C1:EC:30
	DWORD PhysiSpeed;
	DWORD MagicSpeed;
};

#pragma pack(1)
struct PMSG_CONNECT_CLIENT_RECV
{
	PSBMSG_HEAD header; // C1:F1:00
	BYTE result;
	BYTE junk1;
	BYTE indexH;
	BYTE junk2[4];
	BYTE indexL;
	BYTE version[5];
	DWORD Key;
};
#pragma pack()

struct PMSG_CONNECT_ACCOUNT_RECV
{
	PSBMSG_HEAD header; // C1:F1:01
	BYTE result;
};

struct PMSG_CLOSE_CLIENT_RECV
{
	PSBMSG_HEAD header; // C1:F1:02
	BYTE result;
};

struct PMSG_NEW_MESSAGE_RECV
{
	PSBMSG_HEAD header; // C1:F3:E4
	char message[128];
};

//**********************************************//
//************ Client -> GameServer ************//
//**********************************************//

struct PMSG_HELPER_START_SEND
{
	PSBMSG_HEAD header; // C1:BF:51
	BYTE type;
};

struct PMSG_CHARACTER_LIST_SEND
{
	PSBMSG_HEAD header; // C1:F3:00
};

struct CUSTOM_MESSAGE
{
	PSBMSG_HEAD h;
	BYTE type;
	char message[100];
};
#pragma pack(1)
struct LOGIN_REQUEST
{
	PSBMSG_HEAD h;
	char account[10];
	char password[20];
	DWORD TickCount;
	BYTE client_version[5];
	BYTE client_serial[16];
	BYTE language_code;
	char mac[18];
	DWORD disk_serial;
};

struct CASH_SHOP_DATA_UPDATE
{
	PSBMSG_HEAD h;
	char item_ip[16];
	char item_dir[32];
	char item_dir_test[32];

	char banner_ip[16];
	char banner_dir[32];
	char banner_dir_test[32];
};
#pragma pack()


struct PARTY_USER_DELETE
{
	PARTY_USER_DELETE()
	{
		this->h.set(0x43, sizeof(PARTY_USER_DELETE));
	}

	PBMSG_HEAD h;
};

struct CASTLE_SIEGE_SWITCH_INFO
{
	PSBMSG_HEAD h;
	WORD switch_index;
	BYTE id;
	BYTE state;
	BYTE join_side;
	char guild[9];
	char user[11];
};

struct SERVER_INFO_RESULT
{
	PSBMSG_HEAD h;
	char ip[16];
	WORD port;
};

struct SEND_EFFECT
{
	PBMSG_HEAD h;
	BYTE index[2];
	BYTE effect;
};

struct HACK_REPORT
{
	HACK_REPORT(BYTE type)
	{
		this->h.set(0xF3, 187, sizeof(HACK_REPORT));
		this->type = type;
		this->headcode = 0;
	}

	PSBMSG_HEAD h;
	BYTE type;
	BYTE headcode;
};

struct VIEWPORT_CREATE_MONSTER
{
	PWMSG_HEAD h;
	BYTE count;
	BYTE IndexH;
	BYTE IndexL;
	BYTE ClassH;
	BYTE ClassL;
	BYTE x;
	BYTE y;
	BYTE tx;
	BYTE ty;
	BYTE path;
	BYTE elemental_attribute;
	BYTE Level[2];
	BYTE hp_max[4];
	BYTE hp[4];
	BYTE effect_count;
};

struct VIEWPORT_DESTROY_COMPLETE
{
	PBMSG_HEAD h;
	BYTE count;
	BYTE IndexH;
	BYTE IndexL;
};
#pragma pack(1)
struct MESSAGE_BOX_SEND
{
	PSBMSG_HEAD h;
	BYTE type;
	char caption[100];
	char message[150];
};

struct VIEWPORT_MONSTER_CUSTOM_EQUIPMENT
{
	WORD item;
	BYTE level;
	BYTE excellent_ancient;
};

struct VIEWPORT_MONSTER_CUSTOM_DATA
{
	PSBMSG_HEAD h;
	WORD index;
	BYTE type;
	char name[32];
	float size;
	BYTE race;
	VIEWPORT_MONSTER_CUSTOM_EQUIPMENT equipment[12];
};

struct ATTACK_SPEED_DATA
{
	ATTACK_SPEED_DATA(DWORD att_speed, DWORD mc_speed)
	{
		this->h.set(0xF3, 190, sizeof(ATTACK_SPEED_DATA));
		memset(this->attack_speed, 0, 4);
		memset(this->magic_speed, 0, 4);

		this->attack_speed[0] = HIBYTE(HIWORD(att_speed));
		this->attack_speed[1] = LOBYTE(HIWORD(att_speed));
		this->attack_speed[2] = HIBYTE(LOWORD(att_speed));
		this->attack_speed[3] = LOBYTE(LOWORD(att_speed));

		this->magic_speed[0] = HIBYTE(HIWORD(mc_speed));
		this->magic_speed[1] = LOBYTE(HIWORD(mc_speed));
		this->magic_speed[2] = HIBYTE(LOWORD(mc_speed));
		this->magic_speed[3] = LOBYTE(LOWORD(mc_speed));

		this->attack_speed[0] += 0x30;
		this->attack_speed[1] += 0x31;
		this->attack_speed[2] += 0x32;
		this->attack_speed[3] += 0x33;

		this->magic_speed[0] += 0x34;
		this->magic_speed[1] += 0x35;
		this->magic_speed[2] += 0x36;
		this->magic_speed[3] += 0x37;
	}

	PSBMSG_HEAD h;
	BYTE attack_speed[4];
	BYTE magic_speed[4];
};

struct HACK_CHECK_PING
{
	HACK_CHECK_PING()
	{
		this->h.set(0xF3, 191, sizeof(HACK_CHECK_PING));
		this->id = 0;
	}

	PSBMSG_HEAD h;
	BYTE id;
};

struct HACK_CHECK_MODIFIED_BYTE_OFFSET
{
	HACK_CHECK_MODIFIED_BYTE_OFFSET()
	{
		this->h.set(0xF3, 192, sizeof(HACK_CHECK_MODIFIED_BYTE_OFFSET));
		this->offset = 0;
		this->move = 0;
		this->value = 0;
	}

	PSBMSG_HEAD h;
	DWORD offset;
	BYTE move;
	BYTE value;
};

struct HACK_CHECK_MODIFIED_DOUBLE_OFFSET
{
	HACK_CHECK_MODIFIED_DOUBLE_OFFSET()
	{
		this->h.set(0xF3, 193, sizeof(HACK_CHECK_MODIFIED_DOUBLE_OFFSET));
		this->offset = 0;
		this->value = 0.0f;
	}

	PSBMSG_HEAD h;
	DWORD offset;
	double value;
};

struct HACK_CHECK_HOOKED_FUNCTION
{
	HACK_CHECK_HOOKED_FUNCTION()
	{
		this->h.set(0xF3, 194, sizeof(HACK_CHECK_HOOKED_FUNCTION));
		this->id = 0;
		this->data = 0;
	}

	PSBMSG_HEAD h;
	BYTE id;
	BYTE data;
};

struct HACK_CHECK_FRAME_COUNT
{
	HACK_CHECK_FRAME_COUNT()
	{
		this->h.set(0xF3, 195, sizeof(HACK_CHECK_FRAME_COUNT));
		this->count = 0;
	}

	PSBMSG_HEAD h;
	int count;
};

struct HACK_CHECK_ADD_OFFSET_BODY
{
	DWORD offset;
	BYTE data;
	BYTE fix;
};

struct HACK_CHECK_ADD_OFFSET_HEAD
{
	PSWMSG_HEAD h;
	BYTE count;
};

struct SHOP_MISC_BODY
{
	BYTE slot;
	DWORD price;
};

struct SHOP_MISC_HEAD
{
	PSWMSG_HEAD h;
	BYTE type;
	BYTE count;
};

struct CLIENT_MINIMIZE
{
	CLIENT_MINIMIZE(BYTE minimize)
	{
		this->h.set(0xF3, 203, sizeof(CLIENT_MINIMIZE));
		this->minimize = minimize;
	}
	PSBMSG_HEAD h;
	BYTE minimize;
};
#pragma pack()
struct CASTLE_SIEGE_SWITCH_STATE
{
	PSBMSG_HEAD h;
	BYTE switchH;
	BYTE switchL;
	BYTE playerH;
	BYTE playerL;
	BYTE state;
};

struct CROWN_STATE
{
    PSBMSG_HEAD h;
    BYTE state;
};

struct CROWN_ACCESS_STATE 
{
	PSBMSG_HEAD h;
	BYTE state;
	BYTE unk1;
	BYTE unk2;
	BYTE unk3;
	DWORD accumulated_time;
};

#pragma pack(1)
struct NORMAL_MAGIC_ATTACK
{
	PBMSG_HEAD h;
	BYTE TargetH;
	BYTE MagicH;
	BYTE TargetL;
	BYTE MagicL;
	__int64 Time;
};

struct DURATION_MAGIC_ATTACK
{
	PBMSG_HEAD h;
	BYTE x;
	BYTE SkillH;
	BYTE y;
	BYTE SkillL;
	BYTE Dir;
	BYTE TargetH;
	BYTE Dis;
	BYTE TargetL;
	BYTE target_pos;
	BYTE MagicKey;
	__int64 Time;
};
#pragma pack()
struct ATTACK_REQUEST
{
	PBMSG_HEAD h;
	BYTE target[2];
	BYTE action;
	BYTE dir_dis;
	__int64 Time;
};

#pragma pack(1)
struct PLAYER_RESPAWN 
{
	PSBMSG_HEAD h;
	uint8 x; //4
	uint8 y; //5
	uint16 world; //6
	uint8 direction; //8
	uint8 labyrinth_id; //9
	uint16 power[4]; //10
	uint8 experience[8]; //18
	uint8 unk2; //26
	uint8 unk3; //27
	uint32 zen; //28

	///- Custom
	uint32 ViewHP;
	uint32 ViewMP;
	uint32 ViewAG;
	uint32 ViewSD;
};

struct NORMAL_LEVELUP_SEND
{
	PSBMSG_HEAD h;
	uint16 level;
	uint16 points;
	uint16 power_max[4];
	uint16 add_point;
	uint16 add_point_max;
	uint16 minus_point;
	uint16 minus_point_max;

	///- CUSTOM
	uint32 ViewMaxHP;
	uint32 ViewMaxMP;
	uint32 ViewMaxAG;
	uint32 ViewMaxSD;
};

struct ELEMENTAL_DAMAGE_SEND
{
	PBMSG_HEAD h;
	uint8 index[2];
	uint8 elemental_attribute;
	uint8 unk2[2];
	uint32 damage;
	uint8 data;

	///- CUSTOM
	uint32 ViewHP;
	uint32 ViewSD;
};

struct DAMAGE_SEND
{
	PBMSG_HEAD h;
	
	uint8 index[2];
	uint8 junk[3]; //5
	uint32 damage; //8
	uint8 typeH; //12
	uint8 typeL; //13
	uint8 shieldH; //14
	uint8 shieldL; //15
	uint8 attribute; //16

	///- CUSTOM
	uint32 ViewHP;
	uint32 ViewSD;
};

struct MASTER_LEVELUP_SEND
{
	PSBMSG_HEAD h;
	uint16 level;
	uint16 minuspoint;
	uint16 points;
	uint16 maxminuspoint;
	uint16 power_max[4];

	///- CUSTOM
	uint32 ViewMaxHP;
	uint32 ViewMaxMP;
	uint32 ViewMaxAG;
	uint32 ViewMaxSD;
};

struct MASTER_STATUS_SEND
{
	PSBMSG_HEAD h;
	uint16 level;
	uint8 experience[8];
	uint8 next_experience[8];
	uint16 points;
	uint16 power_max[4];

	///- CUSTOM
	uint32 ViewMaxHP;
	uint32 ViewMaxMP;
	uint32 ViewMaxAG;
	uint32 ViewMaxSD;
};

struct CHARACTER_JOIN_RESULT
{
	PSBMSG_HEAD h;
	uint8 x; //4
	uint8 y; //5
	uint16 world; //6
	uint8 direction; //8
	uint8 experience[8]; //9
	uint8 next_experience[8]; //17
	uint8 unk1; //25
	uint16 normal_points; //26
	uint16 strength; //28
	uint16 agility; //30
	uint16 vitality; //32
	uint16 energy; //34
	uint16 life; //36
	uint16 life_max; //38
	uint16 mana; //40
	uint16 mana_max; //42
	uint16 shield; //44
	uint16 shield_max; //46
	uint16 stamina; //48
	uint16 stamina_max; //50
	uint32 zen;  // 52
	uint8 PkLevel; // 56
	uint8 authority; // 57
	uint16 add_point; // 58
	uint16 add_point_max; // 60
	uint16 leadership; // 62
	uint16 minus_point;  // 64
	uint16 minus_point_max;  // 66
	uint8 ExpandedInventory;  // 68
	uint8 unk2[3]; // 69
	uint32 r_money; // 72

	///- CUSTOM
	uint32 ViewHP;
	uint32 ViewMaxHP;
	uint32 ViewMP;
	uint32 ViewMaxMP;
	uint32 ViewAG;
	uint32 ViewMaxAG;
	uint32 ViewSD;
	uint32 ViewMaxSD;
};

struct LIFE_SEND : C1_HEADER
{
	uint8 type;
	uint8 life[2];
	uint8 flag;
	uint8 shield[2];
	//EXTRA
	uint32 ViewHP;
	uint32 ViewSD;
};

struct MANA_SEND : C1_HEADER
{
	uint8 type;
	uint8 mana[2];
	uint8 bp[2];
	//EXTRA
	uint32 ViewMP;
	uint32 ViewAG;
};
#pragma pack()
//**********************************************//
//**********************************************//
//**********************************************//

BOOL ProtocolCoreEx(BYTE head,BYTE* lpMsg,DWORD size,int key);
void GCUserDieRecv(PMSG_USER_DIE_RECV* lpMsg);
void GCMapServerMoveRecv(PMSG_MAP_SERVER_MOVE_RECV* lpMsg);
void GCMapServerMoveAuthRecv(PMSG_MAP_SERVER_MOVE_AUTH_RECV* lpMsg);
void GCConnectClientRecv(PMSG_CONNECT_CLIENT_RECV* lpMsg);
void GCConnectAccountRecv(PMSG_CONNECT_ACCOUNT_RECV* lpMsg);
bool GCCloseClientRecv(PMSG_CLOSE_CLIENT_RECV* lpMsg);
void GCCharacterListRecv();
void GCCharacterInfoRecv(BYTE* Packet);
void GCNewMessageRecv(BYTE * Packet);
void GCNewMessageRecv(BYTE type, const char * message, ...);
void DataSend(BYTE* lpMsg,DWORD size);
void GCSetCrownSwitchData(BYTE * Packet);
void GCSetAttackSpeed(BYTE * Packet);
void CGAttackSpeed();
void GCMessageBox(BYTE * Packet);
void GCMessageBox(BYTE type, const char * caption, const char * message, ...);

void NormalMessage(BYTE type, const char * msg, ...);

void GCOffsetFPS(BYTE * Packet);
void ApplyFPSOffset(bool value);

void TestPacketRecv(BYTE* Packet);

void CustomConnect(BYTE* Packet);

void HandleRespawn(BYTE* Packet);
void HandleLevelUp(BYTE* Packet);
void HandleElementalDamage(BYTE* Packet);
void HandleDamage(BYTE* Packet);
void HandleMasterStatus(BYTE* Packet);
void HandleMasterLevelUp(BYTE* Packet);
void HandleHP(BYTE* Packet);
void HandleMP(BYTE* Packet);

#endif