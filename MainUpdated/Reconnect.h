#ifndef RECONNECT_H
#define RECONNECT_H

#pragma once

#if RECONNECT_ENABLED == 1

enum eReconnectStatus
{
	RECONNECT_STATUS_NONE = 0,
	RECONNECT_STATUS_RECONNECT = 1,
	RECONNECT_STATUS_DISCONNECT = 2,
};

enum eReconnectProgress
{
	RECONNECT_PROGRESS_NONE = 0,
	RECONNECT_PROGRESS_CONNECTED = 1,
	RECONNECT_PROGRESS_JOINED = 2,
	RECONNECT_PROGRESS_CHAR_LIST = 3,
	RECONNECT_PROGRESS_CHAR_INFO = 4,
};

void InitReconnect();




BOOL ReconnectCreateConnection(char* address,WORD port);
void ReconnectGetAccountInfo();
void ReconnectCheckConnection();
void ReconnectCloseSocket();

class Reconnect
{
	public:
		Reconnect();
		virtual ~Reconnect();

		static void DrawInterfaceHook();

		void Update();
		void OnCloseSocket();
		void SetData(const char * account, const char * password);
		void SetInfo(eReconnectStatus status, eReconnectProgress progress);
		void ViewportDestroy();
		void Draw();
		void GameServerLoad();
		void GameServerAuth();

		void OnMapServerMove(char* address,WORD port);
		void OnMapServerMoveAuth(BYTE result);
		void OnConnectAccount(BYTE result);
		void OnCloseClient(BYTE result);
		void OnCharacterList();
		void OnCharacterInfo();

		void SetConnectionInfo(char* address,WORD port);

		char Account[11];
		char Password[21];

		char CharacterName[11];
		BYTE CharacterIndex;
		bool HelperOn;
		DWORD ServerMoveAuth[4];
		///-
		eReconnectProgress Progress;
		eReconnectStatus Status;
		bool IsConnectServerConnected;
		bool AuthSend;
		///-
		TimeStruct InterfaceTime;
		TimeStruct ProcessTime;
};

extern Reconnect g_Reconnect;

#endif

#endif