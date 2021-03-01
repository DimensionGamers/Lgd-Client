#ifndef CASTLE_SIEGE_H
#define CASTLE_SIEGE_H

enum CastleSiegeSwitchState
{
	CASTLE_SIEGE_SWITCH_STATE_NONE = -1,
	CASTLE_SIEGE_SWITCH_STATE_OFF = 0,
	CASTLE_SIEGE_SWITCH_STATE_ON = 1,
	CASTLE_SIEGE_SWITCH_STATE_BUSY = 2,
};

enum CastleSiegeCrownState
{
	CASTLE_SIEGE_CROWN_STATE_NONE = -1,
	CASTLE_SIEGE_CROWN_STATE_OFF = 0,
	CASTLE_SIEGE_CROWN_STATE_ON = 1,
};

enum CastleSiegeCrownMasterState
{
	CASTLE_SIEGE_CROWN_MASTER_STATE_NONE = -1,
	CASTLE_SIEGE_CROWN_MASTER_STATE_ATTEMPT = 0,
	CASTLE_SIEGE_CROWN_MASTER_STATE_SUCCESS = 1,
	CASTLE_SIEGE_CROWN_MASTER_STATE_FAIL = 2,
	CASTLE_SIEGE_CROWN_MASTER_STATE_TAKEN = 3,
	CASTLE_SIEGE_CROWN_MASTER_STATE_WRONG_SWITCH = 4,
};

class CastleSiege
{
	public:
		CastleSiege();
		virtual ~CastleSiege();

		void SetSwitchData(BYTE state, WORD index, WORD monster);
		void PrintSwitch();

		void SetCrownData(BYTE state);
		void PrintCrown();

		void SetCrownMasterData(BYTE state, DWORD time);
		void PrintMasterCrown();

		BYTE SwitchState;
		TimeStruct SwitchTime;
		std::string SwitchString;

		BYTE CrownState;
		TimeStruct CrownTime;
		std::string CrownString;

		BYTE CrownMasterState;
		TimeStruct CrownMasterTime;
		std::string CrownMasterString1;
		std::string CrownMasterString2;
};

extern CastleSiege g_CastleSiege;

#endif