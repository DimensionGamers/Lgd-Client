#ifndef ANTI_CHEAT_H
#define ANTI_CHEAT_H

#pragma once

typedef std::map<int, DWORD> KeyPressMap;

static const int KeyArray[] = {
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x51, 0x52, 0x57, 0x45, 0x71, 0x72, 0x77, 0x65, 0
};

typedef std::map<DWORD, BYTE> ACOffsetMap;

class AntiCheat
{
	public:
		AntiCheat();
		virtual ~AntiCheat();

		void InitKey();

		void LoadOffsetMap();
		void UpdateOffsetMap();

		void SetKeyPress(bool vr, int key);
		bool IsKeyAllowed(int key, uint8 type);
		bool IsBindKeyAllowed(int key);
		bool IsSkillBindKeyAllowed(int key);

		void SetAntiMacroData(BYTE* Packet);

		void SendMacroDetect(uint8 type);
		
		DECLARE_BOOL(AntiMacroEnabled);
		DECLARE_ENUM(DWORD, AntiMacroTime);

		DECLARE_BOOL(AntiMacroComboEnabled);
		DECLARE_ENUM(DWORD, AntiMacroComboTime);

		DECLARE_ENUM(uint32, Time);
	private:
		KeyPressMap m_NormalKeyMap;
		KeyPressMap m_VirtualKeyMap;
		ACOffsetMap m_OffsetMap;
};

extern AntiCheat g_AntiCheat;

#endif