#ifndef CASH_SHOP_H
#define CASH_SHOP_H

#pragma once

#pragma pack(1)
struct CASH_SHOP_DATE : C1_HEADER_SUB
{
	uint16 id;
	uint16 year;
	uint16 month;
};
#pragma pack()

enum CashShopCoin
{
	CASH_SHOP_COIN_C,
	CASH_SHOP_COIN_P,
	CASH_SHOP_COIN_GOBLIN,
	CASH_SHOP_COIN_ZEN,
	CASH_SHOP_COIN_RUUD,
	CASH_SHOP_COIN_BLESS,
	CASH_SHOP_COIN_SOUL,
	CASH_SHOP_COIN_CHAOS,
	CASH_SHOP_COIN_GUARDIAN,
	CASH_SHOP_COIN_MAX
};

class CashShop
{
	public:
		CashShop();
		~CashShop();

		void HandleData(uint8* Packet);
		void HandleItemData(uint8* Packet);
		void HandleCategory(uint8* Packet);
		void HandlePackage(uint8* Packet);
		void HandleProduct(uint8* Packet);
	private:
		DECLARE_ENUM(uint16, ItemID);
		DECLARE_ENUM(uint16, ItemYear);
		DECLARE_ENUM(uint16, ItemMonth);
		std::string Folder;
};

extern CashShop g_CashShop;

#endif