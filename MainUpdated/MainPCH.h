#ifndef MAIN_PCH_H
#define MAIN_PCH_H

#define RECONNECT_ENABLED			1

#include <windows.h>
#include <ostream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <list>
#include <math.h>
#include <tchar.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <tlhelp32.h>

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib, "version.lib")  // for "VerQueryValue"

#pragma warning(disable: 4996)
#pragma warning(disable: 4244)
#pragma warning(disable: 4826)

#include <boost/chrono/include.hpp>
#include <boost/filesystem.hpp>

#include "Defines.h"
#include "Offset.h"

#include "Main.h"

#include "Packet.h"

#include "ReadScript.h"
#include "Common.h"
#include "CustomObject.h"
#include "HackCheck.h"
#include "Item.h"
#include "PacketEncDec.h"
#include "PacketManager.h"
#include "PrintPlayer.h"
#include "Protocol.h"
#include "Reconnect.h"
#include "Util.h"
#include "InputOutput.h"

#include "GUIMgr.h"

#include "CastleSiege.h"
#include "NewEncode.h"
#include "AntiCheat.h"

#include "ByteBuffer.h"
#include "GamePacket.h"

#include "CashShop.h"

#endif