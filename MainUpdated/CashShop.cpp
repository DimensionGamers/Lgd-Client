CashShop g_CashShop;

CashShop::CashShop()
{
	this->SetItemID(0);
	this->SetItemYear(0);
	this->SetItemMonth(0);
}

CashShop::~CashShop()
{

}

void CashShop::HandleData(uint8* Packet)
{
	CASH_SHOP_DATA_UPDATE * lpMsg = (CASH_SHOP_DATA_UPDATE*)Packet;

	MemoryCpy(MAIN_OFFSET_CASHSHOP_IP_1, lpMsg->item_ip, 16);
	MemoryCpy(MAIN_OFFSET_CASHSHOP_DIR_1, lpMsg->item_dir, 32);
	MemoryCpy(MAIN_OFFSET_CASHSHOP_IP_2, lpMsg->item_ip, 16);
	MemoryCpy(MAIN_OFFSET_CASHSHOP_DIR_2, lpMsg->item_dir, 32);

	MemoryCpy(MAIN_OFFSET_CASHSHOP_BANNER_IP_1, lpMsg->banner_ip, 16);
	MemoryCpy(MAIN_OFFSET_CASHSHOP_BANNER_DIR_1, lpMsg->banner_dir, 32);
	MemoryCpy(MAIN_OFFSET_CASHSHOP_BANNER_IP_2, lpMsg->banner_ip, 16);
	MemoryCpy(MAIN_OFFSET_CASHSHOP_BANNER_DIR_2, lpMsg->banner_dir, 32);
}

void CashShop::HandleItemData(uint8* Packet)
{
	CASH_SHOP_DATE * lpMsg = (CASH_SHOP_DATE*)Packet;

	this->SetItemID(lpMsg->id);
	this->SetItemYear(lpMsg->year);
	this->SetItemMonth(lpMsg->month);

	char id_buffer[255];
	char year_buffer[255];
	char month_buffer[255];

	if(lpMsg->id < 10)
	{
		sprintf(id_buffer, "00%u", lpMsg->id);
	}
	else if(lpMsg->id < 100)
	{
		sprintf(id_buffer, "0%u", lpMsg->id);
	}
	else
	{
		sprintf(id_buffer, "%u", lpMsg->id);
	}

	if(lpMsg->year < 10)
	{
		sprintf(year_buffer, "00%u", lpMsg->year);
	}
	else if(lpMsg->year < 100)
	{
		sprintf(year_buffer, "0%u", lpMsg->year);
	}
	else
	{
		sprintf(year_buffer, "%u", lpMsg->year);
	}

	if(lpMsg->month < 10)
	{
		sprintf(month_buffer, "00%u", lpMsg->month);
	}
	else if(lpMsg->month < 100)
	{
		sprintf(month_buffer, "0%u", lpMsg->month);
	}
	else
	{
		sprintf(month_buffer, "%u", lpMsg->month);
	}

	char buffer[1024];
	sprintf(buffer, "Data/InGameShopScript/%s.%s.%s/", id_buffer, year_buffer, month_buffer);

	this->Folder = buffer;
}

void CashShop::HandleCategory(uint8* Packet)
{
	GamePacket incoming(Packet);

	std::string filename = this->Folder + "IBSCategory.txt";
	FILE* fp = fopen(filename.c_str(), "w");

	while(!incoming.is_all_read())
	{
		uint16 id = incoming.read<uint16>();
		std::string const& name = incoming.read<std::string>();
		uint8 data_1 = 200;
		uint8 data_2 = 201;
		uint8 parent = incoming.read<uint8>();
		uint8 main = incoming.read<uint8>();

		std::ostringstream stream;
		stream << (uint32)id << "@";
		stream << name << "@";
		stream << (uint32)data_1 << "@";
		stream << (uint32)data_2 << "@";
		stream << (uint32)parent << "@";
		stream << (uint32)parent << "@";
		stream << (uint32)main;

		if(!incoming.is_all_read())
		{
			fprintf(fp, "%s\n", stream.str().c_str());
		}
		else
		{
			fprintf(fp, "%s", stream.str().c_str());
		}
	}

	fflush(fp);
	fclose(fp);
}

void CashShop::HandlePackage(uint8* Packet)
{
	GamePacket incoming(Packet);

	std::string filename = this->Folder + "IBSPackage.txt";
	FILE* fp = fopen(filename.c_str(), "w");

	while(!incoming.is_all_read())
	{
		uint16 category = incoming.read<uint16>();
		uint8 position = incoming.read<uint8>();
		uint16 id = incoming.read<uint16>();
		std::string const& name = incoming.read<std::string>();
		uint32 price = incoming.read<uint32>();
		std::string const& description = incoming.read<std::string>();
		uint8 price_type = incoming.read<uint8>();
		uint8 product_count = incoming.read<uint8>();

		std::ostringstream stream;
		stream << (uint32)category << "@";
		stream << (uint32)position << "@";
		stream << (uint32)id << "@";
		stream << name << "@";
		stream << (uint32)170 << "@";
		stream << (uint32)price << "@";
		stream << description << "@";
		stream << "@";
		stream << (uint32)182 << "@";
		stream << (uint32)184 << "@";
		stream << (uint32)20100526194000 << "@";
		stream << (uint32)20190531124000 << "@";
		stream << (uint32)177 << "@";
		stream << (uint32)product_count << "@";

		std::string price_name = "Credits";

		switch(price_type)
		{
		case CASH_SHOP_COIN_P:
			{
				price_name = "Event Points";
			} break;

		case CASH_SHOP_COIN_GOBLIN:
			{
				price_name = "Goblin Points";
			} break;

		case CASH_SHOP_COIN_ZEN:
			{
				price_name = "Zen";
			} break;

		case CASH_SHOP_COIN_RUUD:
			{
				price_name = "Ruud";
			} break;

		case CASH_SHOP_COIN_BLESS:
			{
				price_name = "Jewel of Bless";
			} break;

		case CASH_SHOP_COIN_SOUL:
			{
				price_name = "Jewel of Soul";
			} break;

		case CASH_SHOP_COIN_CHAOS:
			{
				price_name = "Jewel of Chaos";
			} break;

		case CASH_SHOP_COIN_GUARDIAN:
			{
				price_name = "Jewel of Guardian";
			} break;
		}

		stream << price_name << "@";
		stream << price_name << "@";
		stream << (uint32)181 << "@";
		stream << (uint32)200 << "@";
		stream << (uint32)0 << "@";

		for(int i = 0; i < product_count; ++i)
		{
			uint16 product_id = incoming.read<uint16>();
			stream << (uint32)product_id << "|";
		}
		stream << "@";

		uint16 display_item = incoming.read<uint16>();
		stream << (uint32)display_item << "@";
		stream << (uint32)2 << "@";

		uint8 option_count = incoming.read<uint8>();
		stream << (uint32)option_count << "@";
		for(int i = 0; i < option_count; ++i)
		{
			uint8 option = incoming.read<uint8>();
			stream << (uint32)option << "|";
		}

		stream << "@";
		stream << (uint32)1;

		if(!incoming.is_all_read())
		{
			fprintf(fp, "%s\n", stream.str().c_str());
		}
		else
		{
			fprintf(fp, "%s", stream.str().c_str());
		}
	}

	fflush(fp);
	fclose(fp);
}

void CashShop::HandleProduct(uint8* Packet)
{
	GamePacket incoming(Packet);

	std::string filename = this->Folder + "IBSProduct.txt";
	FILE* fp = fopen(filename.c_str(), "w");

	while(!incoming.is_all_read())
	{
		uint16 id = incoming.read<uint16>();
		std::string const& name = incoming.read<std::string>();
		uint8 type = incoming.read<uint8>();
		uint32 value = incoming.read<uint32>();
		uint32 price = incoming.read<uint32>();
		uint8 option = incoming.read<uint8>();
		uint16 item = incoming.read<uint16>();

		std::ostringstream stream;
		stream << (uint32)id << "@";
		stream << name << "@";

		if(type == 0)
		{
			stream << "Duration" << "@";
			stream << value << "@";
			stream << "Sec" << "@";
		}
		else
		{
			stream << "Quantity" << "@";
			stream << value << "@";
			stream << "EA" << "@";
		}

		stream << price << "@";
		stream << (uint32)option << "@";

		stream << (uint32)142 << "@";
		stream << (uint32)145 << "@";
		stream << (uint32)1 << "@";
		stream << (uint32)144 << "@";
		stream << (uint32)673 << "@";
		stream << (uint32)518 << "@";

		stream << (uint32)item << "@";

		if(type == 0)
		{
			stream << (uint32)10 << "@";
			stream << (uint32)140 << "@";
			stream << (uint32)386;
		}
		else
		{
			stream << (uint32)7 << "@";
			stream << (uint32)138 << "@";
			stream << (uint32)680;
		}

		if(!incoming.is_all_read())
		{
			fprintf(fp, "%s\n", stream.str().c_str());
		}
		else
		{
			fprintf(fp, "%s", stream.str().c_str());
		}
	}

	fflush(fp);
	fclose(fp);
}