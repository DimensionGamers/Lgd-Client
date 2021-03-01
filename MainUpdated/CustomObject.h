#ifndef CUSTOM_OBJECT_H
#define CUSTOM_OBJECT_H

#pragma once

#define MAX_VIEWPORT_OBJECT				400

#pragma pack(1)
struct ObjectCharacter
{
	/*+0*/		BYTE unk11[442];
	/*+0x1BA*/	WORD AttackSpeed;
	/*+444*/	BYTE Unk346[10];
	/*+0x1C6*/	WORD MagicSpeed;
};

struct ObjectViewportItem
{
	WORD id;
	BYTE level;
	BYTE excellent;
	BYTE ancient;
	BYTE unk273;
	BYTE unk274[30];
};

struct ObjectViewport //(1828 -> Season 13 Ep1 KOR)
{
	/*+12*/ BYTE unk[62];
	/*+62*/ WORD index;
	/*+64*/ BYTE unk64[424];

	/*+488*/ ObjectViewportItem helm; //
	/*+524*/ ObjectViewportItem armor; //0x20C
	/*+560*/ ObjectViewportItem pants; //0x230
	/*+596*/ ObjectViewportItem gloves; //
	/*+632*/ ObjectViewportItem boots; //
	/*+668*/ ObjectViewportItem weapon_01; //0x29C
	/*+704*/ ObjectViewportItem weapon_02; //0x2C0
	/*+740*/ ObjectViewportItem wings;
	/*+776*/ ObjectViewportItem pet;
	/*+812*/ ObjectViewportItem item_unk;

	/*+848*/ BYTE unk840[188];
	/*1036*/ DWORD loaded;
	/*+1040*/ BYTE unk980[44];
	/*+1084*/ BYTE type;
	/*+1081*/ BYTE unk1017[75];
	/*+1160*/ float scale;
	/*+1152*/ BYTE unk1096[680];
};

struct CustomObjectViewport
{
	void Reset()
	{
		this->index = -1;
		this->scale = 1.0f;
	}

	WORD index;
	float scale;
};
#pragma pack()

struct VIEWPORT_MONSTER_CUSTOM_EQUIPMENT;

class CustomObjectMgr
{
	public:
		CustomObjectMgr();
		virtual ~CustomObjectMgr();

		void Update();
		void GCRemoveMonsterData(BYTE * Packet);
		void GCSetMonsterData(BYTE * Packet);
		void SetMonsterEquipment(ObjectViewport* pObject, VIEWPORT_MONSTER_CUSTOM_EQUIPMENT const& equipment, BYTE slot);
		
	private:
		CustomObjectViewport ObjectData[MAX_VIEWPORT_OBJECT];
};

extern CustomObjectMgr g_CustomObjectMgr;

#endif