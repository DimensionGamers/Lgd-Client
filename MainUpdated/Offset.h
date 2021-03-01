#ifndef OFFSET_H
#define OFFSET_H

#pragma once

struct ObjectItem;
struct ObjectViewport;

static const WORD LoginServerPORT = 44405;

///- SERVER TEST
static const char ClientVersion[8] = "1.07.17";
static const char ClientSerial[17] = "jw45af7xf4wxj198";
static const char IpAddress[14] = "127.0.0.1";

static const char* ScreenShotPath = "ScreenShots\\Screen(%02d_%02d-%02d-%02d)-%04d.jpg";

enum MainState
{
	MAIN_STATE_NONE				= 0,
	MAIN_STATE_1				= 1,
	MAIN_STATE_2				= 2,
	MAIN_STATE_3				= 3,
	MAIN_STATE_4				= 4,
	MAIN_STATE_5				= 5,
	MAIN_STATE_PLAYING			= 6,

	MAIN_STATE_DESTROY			= 9,
};

#define MAIN_OFFSET_EP								0x012441FD
#define MAIN_OFFSET_EP_SIZE							12
static const BYTE MainOffsetEP[MAIN_OFFSET_EP_SIZE] = { 0x6A, 0x58, 0x68, 0xE0, 0xF0, 0x7D, 0x01, 0xE8, 0x8F, 0xAB, 0x00, 0x00 };

#define MAIN_OFFSET_PROTOCOL_CORE					0x00D5758D
#define MAIN_OFFSET_PROTOCOL_CORE_HOOK				0x00D5DD56

#define MAIN_OFFSET_LOAD_INTERFACE					0x008366CA
#define MAIN_OFFSET_FREE_INTERFACE					0x00836856
#define MAIN_OFFSET_DRAW_INTERFACE					0x0083F98C
#define MAIN_OFFSET_DRAW_INTERFACE_TEXT				0x0089627A

#define MAIN_CONNECTION_STATUS						0x0A6A16E8
#define MAIN_SCREEN_STATE							0x0046BD30
#define MAIN_SCREEN_STATE_POINTER					0x0A6A5908

#define MAIN_CHARACTER_MAP							0x0181DF04
#define MAIN_CHARACTER_STRUCT						0x0A6A5A34

#define MAIN_OFFSET_DATASEND_POINTER				0x01826E54
#define MAIN_OFFSET_DATASEND						0x00CEB64F
#define MAIN_OFFSET_DATASEND_HOOK_1					0x00CEB249
#define MAIN_OFFSET_DATASEND_HOOK_2					0x00CEB37C
#define MAIN_OFFSET_DATASEND_HOOK_3					0x00CEB415

#define MAIN_OFFSET_PRINT_PLAYER_VIEW_HP_HOOK		0x00C56C0B
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_HP			0x00C56C14
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_HP_HOOK	0x00C56C25
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_HP		0x00C56C2E
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_MP_HOOK		0x00C56C3F
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_MP			0x00C56C48
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_MP_HOOK	0x00C56C59
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_MP		0x00C56C62
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_SD_HOOK		0x00C56C73
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_SD			0x00C56C7C
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_SD_HOOK	0x00C56C8D
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_SD		0x00C56C96
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_BP_HOOK		0x00C56CA7
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_BP			0x00C56CB0
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_BP_HOOK	0x00C56CC1
#define MAIN_OFFSET_PRINT_PLAYER_VIEW_MAX_BP		0x00C56CCA

#define MAIN_OFFSET_CASHSHOP_IP_1					0x01602178
#define MAIN_OFFSET_CASHSHOP_DIR_1					0x0160218C
#define MAIN_OFFSET_CASHSHOP_IP_2					0x016021A8
#define MAIN_OFFSET_CASHSHOP_DIR_2					0x016021C4

#define MAIN_OFFSET_CASHSHOP_BANNER_IP_1			0x01602204
#define MAIN_OFFSET_CASHSHOP_BANNER_DIR_1			0x01602218
#define MAIN_OFFSET_CASHSHOP_BANNER_IP_2			0x01602234
#define MAIN_OFFSET_CASHSHOP_BANNER_DIR_2			0x01602250

#define MAIN_OFFSET_CLOSE_SOCKET_POINTER			0x0A6A1768
#define MAIN_OFFSET_CLOSE_SOCKET_CALL				0x00CEBAC3
#define MAIN_OFFSET_SOCKET_CHECK_CALL				0x00CEBC01

#define MAIN_OFFSET_ITEM_USE_HOOK					0x00AA6713
#define MAIN_OFFSET_ITEM_USE_NEXT					0x00AA6726
#define MAIN_OFFSET_ITEM_USE_OK						0x00AA6818

#define MAIN_OFFSET_LETHAL_WIZARD_RING_HOOK			0x00AA5477
#define MAIN_OFFSET_LETHAL_WIZARD_RING_SKIP			0x00AA54F0
#define MAIN_OFFSET_LETHAL_WIZARD_RING_CONTINUE		0x00AA5483
#define MAIN_OFFSET_ADD_ITEM_OPTION_CALL			0x00AA5611
#define MAIN_OFFSET_APPLY_ITEM_OPTION_CALL			0x00AA6A3F

#define MAIN_OFFSET_LWR_APPLY_HOOK_1				0x00CD4413
#define MAIN_OFFSET_LWR_APPLY_JMP_1					0x00CD450D
#define MAIN_OFFSET_LWR_APPLY_HOOK_2				0x00CD4523
#define MAIN_OFFSET_LWR_APPLY_JMP_2					0x00CD4628

#define MAIN_OFFSET_ITEM_TEXT_COLOR					0x08575490
#define MAIN_OFFSET_ITEM_TEXT_UNK					0x085753F0
#define MAIN_OFFSET_ITEM_TEXT						0x08575530

#define MAIN_OFFSET_PS_PETS_ITEM_TEXT_HOOK			0x0057710B
#define MAIN_OFFSET_PS_PETS_ITEM_TEXT_NEXT			0x00577136
#define MAIN_OFFSET_PS_PETS_ITEM_TEXT_OK			0x00577195
#define MAIN_OFFSET_PS_PETS_ITEM_TEXT_VAR_1			0x1B0
#define MAIN_OFFSET_PS_PETS_ITEM_TEXT_VAR_2			0x04

#define MAIN_OFFSET_ITEM_TEXT_VAR_2					0xE4
#define MAIN_OFFSET_ITEM_TEXT_VAR_3					0xD4
#define MAIN_OFFSET_ITEM_TEXT_VAR_4					0x1D8

#define MAIN_OFFSET_SHOP_ITEM_TEXT_HOOK				0x00870072
#define MAIN_OFFSET_SHOP_ITEM_TEXT_JMP				0x00870103

#define MAIN_OFFSET_INIT_WINDOW_HOOK				0x00502116
#define MAIN_OFFSET_INIT_WINDOW_REAL				0x00500B1C

#define MAIN_OFFSET_PLAY_RENDER						0x0050EEDA

#define MAIN_OFFSET_PARTY_PK_HOOK					0x005DA853
#define MAIN_OFFSET_PARTY_PK_JMP					0x005DA8F1

#define MAIN_OFFSET_GET_TEXT_BMD_1					0x00457DE4
#define MAIN_OFFSET_GET_TEXT_BMD_2					0x0A6A5BCC

#define MAIN_OFFSET_FONT_OFFSET						0x01855CCC
#define MAIN_OFFSET_INTERFACE_OFFSET				0x00473A0F
#define MAIN_OFFSET_SET_FONT_OFFSET					0x00473C7E
#define MAIN_OFFSET_SET_TEXT_COLOR_OFFSET			0x00473BCC
#define MAIN_OFFSET_TEXT_OUT						0x00473CA6
#define MAIN_OFFSET_INTERFACE_UNK_OFFSET			0x00473C56
#define MAIN_OFFSET_BIND_TEXTURE					0x0066D1CA

#define MAIN_OFFSET_OBJECT_STRUCT_PTR				0x00458077
#define MAIN_OFFSET_OBJECT_GET_BY_POS				0x00AB7659
#define MAIN_OFFSET_OBJECT_IS_LOADED				0x00457DD6
#define OBJECT_LOADED_DATA							0x40C
#define MAIN_OFFSET_OBJECT_GET_NAME_1				0x004F7FDE
#define MAIN_OFFSET_OBJECT_GET_NAME_2				0x004073E0
#define MAIN_OFFSET_OBJECT_SET_NAME_1				0x004F7FC2
#define MAIN_OFFSET_OBJECT_SET_NAME_2				0x00406FC0

#define MAIN_OFFSET_RENDER_MONSTERS					0x00605C75

#define MAIN_OFFSET_MESSAGE_BUILD					0x00406FC0
#define MAIN_OFFSET_MESSAGE_FREE					0x00407B10
#define MAIN_OFFSET_MESSAGE_PREPARE_PTR				0x0A5D0CC4
#define MAIN_OFFSET_MESSAGE_SEND					0x00C3EED8

#define MAIN_OFFSET_RECONNECT_CHECK_CONNECTION_HOOK		0x0050F060 
#define MAIN_OFFSET_RECONNECT_CHECK_CONNECTION_1		0x0050F108
#define MAIN_OFFSET_RECONNECT_CHECK_CONNECTION_2		0x0050F073

#define MAIN_OFFSET_RECONNECT_CLOSE_SOCKET_HOOK			0x00CEBAD5
#define MAIN_OFFSET_RECONNECT_CLOSE_SOCKET				0x00CEBADC
#define MAIN_OFFSET_RECONNECT_CLOSE_SOCKET_JUMP2		0x00CEBBB5

#define MAIN_OFFSET_RECONNECT_CREATE_CONNECTION			0x00CEDEB4
static const DWORD MainOffsetReconnectCreateConnection[] = {0x0045FFAD, 0x0050BE97, 0x0052FF76, 0x00BCAF32, 0x00D17139, 0 };

#define MAIN_OFFSET_RECONNECT_DRAW_INTERFACE_HOOK		0x0088A8DE
#define MAIN_OFFSET_RECONNECT_DRAW_INTERFACE			0x005C8F8A

#define MAIN_OFFSET_RECONNECT_MAIN_PROC_CHECK			0x0052FF91

#define MAIN_OFFSET_CLIENT_VERSION						0x01826E38

#define MAIN_OFFSET_MAIN_LOOP_VALUE						0x0185619C
#define MAIN_OFFSET_MAIN_LOOP_INIT_HOOK					0x0050E7AE
#define MAIN_OFFSET_MAIN_LOOP_INIT_CALL					0x005BAA41

#define MAIN_OFFSET_GET_ITEM_PRICE						0x005C4B45
#define MAIN_OFFSET_CONVERT_ITEM_PRICE					0x005E9CC4
#define MAIN_OFFSET_CONVERT_ITEM_PRICE_TAX				0x005EC983

#define MAIN_OFFSET_MESSAGE_BOX							0x00B4E445
#define MAIN_OFFSET_MESSAGE_BOX_PTR_1					0x00ACEDC0
#define MAIN_OFFSET_MESSAGE_BOX_PTR_2					0x004698C4

#define MAIN_OFFSET_WELCOME_TO_WORLD_HOOK_1				0x00D26704
#define MAIN_OFFSET_WELCOME_TO_WORLD_JUMP_1				0x00D26716
#define MAIN_OFFSET_WELCOME_TO_WORLD_HOOK_2				0x00D28F34
#define MAIN_OFFSET_WELCOME_TO_WORLD_JUMP_2				0x00D28F46

#define MAIN_OFFSET_WELCOME_TO_WORLD_DATA_1_2			0x2B7C
#define MAIN_OFFSET_WELCOME_TO_WORLD_DATA_2_2			0x29FC

#define MAIN_OFFSET_GET_WORLD_NAME						0x005F3788

#define MAIN_OFFSET_SIEGE_SWITCH_HOOK					0x005D2503
static const DWORD MainOffsetSiegeSwitchClear[] = { 0x00CF65CF, 0x00CF7818, 0x00D3D08B, 0x00D3D09B, 0x00D4AE43, 0x00D4AE53, 0 };
static const DWORD MainOffsetCheckIntegrity[] = { 0x00508676, 0x00D2654B, 0x00E098E8, 0x00E09A21, 0 };

#define WORLD_ATTRIBUTE									0x086CE3F0
#define WORLD_HEIGHTMAP									0x0880E3F0
#define WORLD_MAP_D1									0x087FE3F0
#define WORLD_MAP_D2									0x087EE3F0
#define WORLD_MAP_ALPHA									0x087AE3F0

#define NEW_ENCRYPT_OFFSET								0x006023BB
#define NEW_DECRYPT_OFFSET								0x0060256C

#define MAIN_OFFSET_DECRYPT01							0x005C4487
#define MAIN_OFFSET_XOR3BYTES							0x0045EB99

#define MAIN_OFFSET_BIND_ITEM_USE_HOOK					0x00C75E16
#define MAIN_OFFSET_SEND_ITEM_USE						0x008493C7

///- New Encode Fix
#define MAIN_FIX_ITEM_GET_HOOK							0x00D2B5F8
#define MAIN_FIX_ITEM_GET_JMP							0x00D2B6C5
#define MAIN_FIX_ITEM_GET_VALUE							0x2018	

#define MAIN_FIX_ITEM_MOVE_HOOK							0x00D4FDE4
#define MAIN_FIX_ITEM_MOVE_JMP							0x00D4FEB1
#define MAIN_FIX_ITEM_MOVE_VALUE						0x2018

#define MAIN_FIX_ITEM_GET_MUUN_HOOK						0x00D30E2F
#define MAIN_FIX_ITEM_GET_MUUN_JMP						0x00D30EFC
#define MAIN_FIX_ITEM_GET_MUUN_VALUE					0x2018

#define MAIN_FIX_ITEM_GET_EVENT_HOOK					0x00D31D96
#define MAIN_FIX_ITEM_GET_EVENT_JMP						0x00D31E63
#define MAIN_FIX_ITEM_GET_EVENT_VALUE					0x2018

#define MAIN_FIX_ITEM_MODIFY_HOOK						0x00D51946
#define MAIN_FIX_ITEM_MODIFY_JMP						0x00D51A13
#define MAIN_FIX_ITEM_MODIFY_VALUE						0x2024

#define MAIN_FIX_ITEM_MODIFY_MUUN_HOOK					0x00CFA001
#define MAIN_FIX_ITEM_MODIFY_MUUN_JMP					0x00CFA0CB
#define MAIN_FIX_ITEM_MODIFY_MUUN_VALUE					4

#define MAIN_FIX_ITEM_MODIFY_EVENT_HOOK					0x00CF9088
#define MAIN_FIX_ITEM_MODIFY_EVENT_JMP					0x00CF9155
#define MAIN_FIX_ITEM_MODIFY_EVENT_VALUE				0x2010

#define MAIN_FIX_ITEM_CHANGE_EVENT_HOOK					0x00CF8A4B
#define MAIN_FIX_ITEM_CHANGE_EVENT_JMP					0x00CF8B18
#define MAIN_FIX_ITEM_CHANGE_EVENT_VALUE				0x2010

#define MAIN_FIX_LOGIN_HOOK								0x00D3865B
#define MAIN_FIX_LOGIN_JMP								0x00D38728
#define MAIN_FIX_LOGIN_VALUE							0x2010

#define MAIN_FIX_QUEST_MU_LIST_1_HOOK					0x00D10F38
#define MAIN_FIX_QUEST_MU_LIST_1_JMP					0x00D11009
#define MAIN_FIX_QUEST_MU_LIST_1_VALUE					0x08

#define MAIN_FIX_QUEST_MU_LIST_2_HOOK					0x00D37B64
#define MAIN_FIX_QUEST_MU_LIST_2_JMP					0x00D37C35
#define MAIN_FIX_QUEST_MU_LIST_2_VALUE					0x10

#define IP_ADDRESS_OFFSET								0x0181D3D0

#define MAIN_OFFSET_ZOOM								0x015F1858

static const struct MainOffsetByteFix
{
	DWORD offset;
	BYTE value;
} g_MainOffsetByteFix[] =
{
	///- Config.ini
	{ 0x00501EA3, 0xEB },

	///- GameGuard
	{ 0x00501F57, 0xEB },
	{ 0x00501F9A + 0x00, 0xE9 },
	{ 0x00501F9A + 0x01, 0x88 },
	{ 0x00501F9A + 0x02, 0x00 },
	{ 0x00501F9A + 0x03, 0x00 },
	{ 0x00501F9A + 0x04, 0x00 },
	{ 0x00501F9A + 0x05, 0x00 },

	///- Floating Point
	{ 0x01258117 + 0x00, 0xB8 },
	{ 0x01258117 + 0x01, 0x01 },
	{ 0x01258117 + 0x02, 0x00 },
	{ 0x01258117 + 0x03, 0x00 },
	{ 0x01258117 + 0x04, 0x00 },
	{ 0x01258117 + 0x05, 0x90 },
	{ 0x01258117 + 0x06, 0x90 },
	{ 0x01258117 + 0x07, 0x90 },
	{ 0x01258117 + 0x08, 0x90 },
	{ 0x01258117 + 0x09, 0x90 },
	{ 0x01258117 + 0x0A, 0x90 },

	///- ResourceGuard ERROR
	{ 0x005086A5, 0xEB },
	{ 0x00D2657A + 0x00, 0xE9 },
	{ 0x00D2657A + 0x01, 0x95 },
	{ 0x00D2657A + 0x02, 0x00 },
	{ 0x00D2657A + 0x03, 0x00 },
	{ 0x00D2657A + 0x04, 0x00 },
	{ 0x00E09913, 0xEB },
	{ 0x00E09A4C, 0xEB },

	///- TCA & TOL
	{ 0x00B81CF8, 0xEB },
	{ 0x00B81D09, 0xEB },
	{ 0x00C30978, 0xEB },

	///- ChatBox Text Length
	{ 0x00C3E345 + 0x03, 60 },

	///- Packet Encode
	{ 0x00CEB23A, 0x10 },
	{ 0x00CEB23B, 0x74 },

	///- Version
	{ MAIN_OFFSET_CLIENT_VERSION, (ClientVersion[0] + 1) },
	{ MAIN_OFFSET_CLIENT_VERSION + 1, (ClientVersion[2] + 2) },
	{ MAIN_OFFSET_CLIENT_VERSION + 2, (ClientVersion[3] + 3) },
	{ MAIN_OFFSET_CLIENT_VERSION + 3, (ClientVersion[5] + 4) },
	{ MAIN_OFFSET_CLIENT_VERSION + 4, (ClientVersion[6] + 5) },

	///- HP, MP, SD, AG
	{ 0x00C56BBE, 0xEB },

	///- Gun Crusher Creation
	{ 0x00BC8BBE + 0x01, 0x00 },

	///- Trap Crash Fix
	{ 0x0050D071, 0xEB },
	{ 0x0050D545, 0xEB },
	{ 0x0050D929, 0xEB },
	{ 0x0050EBF5, 0xEB },
	{ 0x005107EE, 0xEB },
	{ 0x005BABB9, 0xEB },
	{ 0x005DF234, 0xEB },
	{ 0x005E7A22, 0xEB },
	{ 0x005E82C7, 0xEB },
	{ 0x0060E5F8, 0xEB },
	{ 0x0086FC0C, 0xEB },
	{ 0x008729D5, 0xEB },
	{ 0x009CD835, 0xEB },
	{ 0x00A6AB0B, 0xEB },
	{ 0x00AC065F, 0xEB },
	{ 0x00B01061, 0xEB },
	{ 0x00D2FC5C, 0xEB },

	{ 0, 0 }
};

static const struct MainOffsetDwordFix
{
	DWORD offset;
	DWORD value;
} g_MainOffsetDwordFix[] =
{
	{ 0x0050EA4E, (DWORD)ScreenShotPath },

	{ 0, 0 }
};

static const struct MainOffsetMemorySet
{
	DWORD offset;
	DWORD value;
	DWORD count;
} g_MainOffsetMemorySet[] =
{
	///- Packet Twist
	{ 0x00DBBDE5, 0x90, 2 },
	{ 0x00DBBE3F, 0x90, 2 },

	///- Warp Menu
	{ 0x00B66C8D, 0x90, 5 },

	///- Map Name
	{ 0x00B62679, 0x90 , 5 },

	///- IP
	{ IP_ADDRESS_OFFSET, 0x00, 23 },

	///- CS MiniMap
	{ 0x008ADA4B, 0x90, 10 },

	{ 0, 0, 0 }
};

static const struct MainOffsetMemoryCpy
{
	DWORD offset;
	void* value;
	DWORD size;
} g_MainOffsetMemoryCpy[] =
{
	///- IP
	{ IP_ADDRESS_OFFSET, (void*)IpAddress, sizeof(IpAddress) },
	{ 0, 0, 0 }
};

static const struct MainOffsetPerformanceFix
{
	DWORD offset;
	BYTE value;
	BYTE original;
} g_MainOffsetPerformanceFix[] =
{
	{ 0x00678F47, 0xC3, 0x55 },
	{ 0x00646D6D, 0xC3, 0x55 },
	{ 0x00643AC7, 0xC3, 0x55 },
	{ 0x00606582, 0xC3, 0x55 },
	{ 0x00602BE2, 0xC3, 0x55 },
	{ 0x00602C59, 0xC3, 0x55 },
	{ 0x00602CD0, 0xC3, 0x55 },
	{ 0x00602D47, 0xC3, 0x55 },
	{ 0x005FDDD0, 0xC3, 0x55 },
	{ 0x005FC752, 0xC3, 0x55 },
	{ 0x00756083, 0xC3, 0x55 },

	{ 0, 0, 0 }
};

static const struct MainOffsetAC
{
	DWORD offset1;
	DWORD offset2;
} g_MainOffsetAC[] =
{
	{ 0x00A961CF, 0x00A9621C }, ///- Remove animation frames
	{ 0x00A94EEA, 0x00A94F54 }, ///- Wall Attack & Attack Range

	{ 0, 0 }
};

#define ProtocolCore ((BOOL(*)(DWORD,BYTE*,DWORD,DWORD)) MAIN_OFFSET_PROTOCOL_CORE)
#define DrawInterface ((void(*)(DWORD,float,float,float,float))MAIN_OFFSET_DRAW_INTERFACE)
#define DrawInterfaceText ((void(*)(char*,int,int,int,int,int,float,int))MAIN_OFFSET_DRAW_INTERFACE_TEXT)
#define INIT_WINDOW_REAL ((HWND(*)(HINSTANCE hInstance)) MAIN_OFFSET_INIT_WINDOW_REAL)

#define WzNewDecrypt				((DWORD(*)(char * dest, char * source, int size)) NEW_DECRYPT_OFFSET)
#define WzNewEncrypt				((DWORD(*)(char * dest, char * source, int size)) NEW_ENCRYPT_OFFSET)

#define WzDecrypt01				((DWORD(*)(char * dest, char * source, int size)) MAIN_OFFSET_DECRYPT01)
#define WzXor3Bytes				((DWORD(*)(char* buffer, size_t size)) MAIN_OFFSET_XOR3BYTES)

#define WzGetItemPrice			((DWORD(_cdecl*)(DWORD, BYTE)) MAIN_OFFSET_GET_ITEM_PRICE)
#define WzConvertItemPriceTax	((DWORD(_cdecl*)(double, char*, BYTE)) MAIN_OFFSET_CONVERT_ITEM_PRICE_TAX)
#define WzConvertItemPrice		((DWORD(_cdecl*)(DWORD, char*)) MAIN_OFFSET_CONVERT_ITEM_PRICE)

#define WzGetWorldName			((char*(_cdecl*)(DWORD)) MAIN_OFFSET_GET_WORLD_NAME)

inline const char * GetTextBMD(int id)
{
	return ((const char*(__thiscall*)(int, int))MAIN_OFFSET_GET_TEXT_BMD_1)(MAIN_OFFSET_GET_TEXT_BMD_2, id);
}

inline int SocketCheck()
{
	return ((int(__thiscall*)(DWORD))MAIN_OFFSET_SOCKET_CHECK_CALL)(MAIN_OFFSET_CLOSE_SOCKET_POINTER);
}

#define WzSendItemUse			((DWORD(*)(BYTE, char)) MAIN_OFFSET_SEND_ITEM_USE)

inline ObjectViewport* WzGetObjectStructByPos(DWORD pos)
{
	static const DWORD CALL_1 = MAIN_OFFSET_OBJECT_STRUCT_PTR;
	static const DWORD CALL_2 = MAIN_OFFSET_OBJECT_GET_BY_POS;

	DWORD result = 0;

	_asm
	{
		Mov Edx, pos
		Push Edx
		Call [CALL_1]
		Mov Ecx, Eax
		Call [CALL_2]
		Mov result, Eax
	}

	if (result == 0)
	{
		return NULL;
	}

	return (ObjectViewport*)result;
}

inline bool WzIsObjectLoaded(DWORD data)
{
	static const DWORD CALL_1 = MAIN_OFFSET_OBJECT_IS_LOADED;

	DWORD result = 0;

	_asm
	{
		Mov Edx, data
		Mov Ecx, Dword Ptr Ds : [Edx]
		Add Ecx, OBJECT_LOADED_DATA
		Call [CALL_1]
		Movzx Edx, Al
		Mov result, Edx
	}

	return result != 0;
}

inline const char* WzGetObjectName(ObjectViewport* pObject)
{
	static const DWORD WzGetObjectName1 = MAIN_OFFSET_OBJECT_GET_NAME_1;
	static const DWORD WzGetObjectName2 = MAIN_OFFSET_OBJECT_GET_NAME_2;

	char* pData = "";
	
	_asm
	{
		Mov Ecx, pObject
		Call [WzGetObjectName1]
		Mov Ecx, Eax
		Call [WzGetObjectName2]
		Mov pData, Eax
	}

	return pData;
}

struct ObjectNameData
{
	BYTE data1[4];
	char data2[16];
	DWORD data3;
	DWORD data4;
};

inline void WzSetObjectName(ObjectViewport* pObject, const char* name)
{
	static const DWORD WzSetObjectNameCALL = MAIN_OFFSET_OBJECT_SET_NAME_1;
	static const DWORD WzSetObjectNameCALL2 = MAIN_OFFSET_OBJECT_SET_NAME_2;
	BYTE data[100];
	ObjectNameData* pText = (ObjectNameData*)data;

	_asm
	{
		Push [name]
		Lea Ecx, pText
		Call [WzSetObjectNameCALL2]
		
		Lea Eax, pText
		Push Eax
		Mov Ecx, pObject
		Call [WzSetObjectNameCALL]
	}
}

inline void WzMessageBox(const char * caption, const char* message, int type)
{
	static const DWORD WzMessageBoxPTR1 = MAIN_OFFSET_MESSAGE_BOX_PTR_1;
	static const DWORD WzMessageBoxPTR2 = MAIN_OFFSET_MESSAGE_BOX_PTR_2;
	static const DWORD WzMessageBoxCALL = MAIN_OFFSET_MESSAGE_BOX;

	_asm
	{
		Push 0
		Push 0
		Push 0
		Mov Edx, caption
		Push Edx
		Mov Edx, message
		Push Edx
		Push 0
		Push 0
		Call [WzMessageBoxPTR1]
		Mov Ecx, Eax
		Call [WzMessageBoxPTR2]
		Mov Ecx, Eax
		Call [WzMessageBoxCALL]
	}
}

#define WzLoadInterface			((void(*)(char*, DWORD, DWORD, DWORD, BYTE, BYTE)) MAIN_OFFSET_LOAD_INTERFACE)
#define WzFreeInterface			((void(*)(DWORD, BYTE)) MAIN_OFFSET_FREE_INTERFACE)

inline bool CC_MAP_RANGE()
{
	return *(DWORD*)MAIN_CHARACTER_MAP == 18 ||
		   *(DWORD*)MAIN_CHARACTER_MAP == 19 ||
		   *(DWORD*)MAIN_CHARACTER_MAP == 20 ||
		   *(DWORD*)MAIN_CHARACTER_MAP == 21 ||
		   *(DWORD*)MAIN_CHARACTER_MAP == 22 ||
		   *(DWORD*)MAIN_CHARACTER_MAP == 23 ||
		   *(DWORD*)MAIN_CHARACTER_MAP == 53 ||
		   *(DWORD*)MAIN_CHARACTER_MAP == 97;
}

inline bool IsCastleSiege()
{
	return *(DWORD*)MAIN_CHARACTER_MAP == 30;
}

inline DWORD GetMainState()
{
	return ((DWORD(__thiscall*)(DWORD))MAIN_SCREEN_STATE)(MAIN_SCREEN_STATE_POINTER);
}

inline void WzMessageSend(BYTE type, const char * message, const char * name)
{
	char memory_1[616];
	char memory_2[616];

	((void(__thiscall*)(void*, void*))MAIN_OFFSET_MESSAGE_BUILD)(memory_1, (void*)message);
	((void(__thiscall*)(void*, void*))MAIN_OFFSET_MESSAGE_BUILD)(memory_2, "");

	((void(__thiscall*)(void*, int, void*, void*))MAIN_OFFSET_MESSAGE_SEND)((void*)(*(DWORD*)MAIN_OFFSET_MESSAGE_PREPARE_PTR), type, memory_2, memory_1);

	((void(__thiscall*)(void*))MAIN_OFFSET_MESSAGE_FREE)(memory_1);
	((void(__thiscall*)(void*))MAIN_OFFSET_MESSAGE_FREE)(memory_2);
}

inline void WzAddItemOption(DWORD item, DWORD option, DWORD value)
{
	static const DWORD CALL_OFFSET = MAIN_OFFSET_ADD_ITEM_OPTION_CALL;

	_asm
	{
		Mov Eax, value
		Push Eax
		Mov Edx, option
		Push Edx
		Mov Ecx, item
		Call [CALL_OFFSET]
	}
}

inline void WzApplyItemOption(DWORD item, int a2, int* a3, int a4, float a5)
{
	((DWORD(__thiscall*)(DWORD, int, int*, int, float))MAIN_OFFSET_APPLY_ITEM_OPTION_CALL)(item, a2, a3, a4, a5);
}

#endif