DWORD ShopPrice[120];
BYTE ShopType = 0;

void SetShopPrice(BYTE * Packet)
{
	for ( int i = 0; i < 120; ++i )
	{
		ShopPrice[i] = 0;
	}

	SHOP_MISC_HEAD * head = (SHOP_MISC_HEAD*)Packet;
	SHOP_MISC_BODY * body = (SHOP_MISC_BODY*)&Packet[sizeof(SHOP_MISC_HEAD)];
	ShopType = head->type;

	for ( int i = 0; i < head->count; ++i )
	{
		ShopPrice[body[i].slot] = body[i].price;
	}
}

__declspec(naked) void ItemUseHook()
{
	static DWORD ItemUseHookAddressOK = MAIN_OFFSET_ITEM_USE_OK;
	static DWORD ItemUseHookAddressNEXT = MAIN_OFFSET_ITEM_USE_NEXT;
	static DWORD ItemID = 0;
	static DWORD ItemLevel = 0;

	_asm
	{
		Mov Eax, Dword Ptr Ss:[Ebp - 0x04]
		Mov Edx, Dword Ptr Ds:[Eax + 0x10]
		Mov ItemID, Edx

		Mov Eax, Dword Ptr Ss:[Ebp - 0x10]
		Mov Edx, Dword Ptr Ds:[Eax + 0x14]
		Mov ItemLevel, Edx
	}

	ItemLevel = (ItemLevel >> 3) & 0xF;

	if ( ItemID == GET_ITEM(13, 54) ||
		 ItemID == GET_ITEM(13, 55) ||
		 ItemID == GET_ITEM(13, 56) ||
		 ItemID == GET_ITEM(13, 57) ||
		 ItemID == GET_ITEM(13, 58) ||
		 ItemID == GET_ITEM(13, 60) ||
		 ItemID == GET_ITEM(14, 120) ||
		 ItemID == GET_ITEM(14, 133) )
	{
		_asm
		{
			Mov Al, 1
			Jmp [ItemUseHookAddressOK]
		}
	}
	else
	{
		_asm
		{
			Jmp [ItemUseHookAddressNEXT]
		}
	}
}

__declspec(naked) void FixLethalWizardRingAttributes()
{
	static DWORD JMP_SKIP = MAIN_OFFSET_LETHAL_WIZARD_RING_SKIP;
	static DWORD JMP_CONTINUE = MAIN_OFFSET_LETHAL_WIZARD_RING_CONTINUE;
	static DWORD ItemPtr = 0;
	static DWORD ItemID = 0;

	_asm
	{
		Mov Eax, Dword Ptr Ss:[Ebp - 0x28]
		Mov Edx, Dword Ptr Ds:[Eax + 0x10]
		Mov ItemID, Edx

		Mov Eax, Dword Ptr Ss:[Ebp - 0x28]
		Mov ItemPtr, Eax
	}

	if (ItemID == GET_ITEM(13, 107))
	{
		WzAddItemOption(ItemPtr, 7, 15);
		WzAddItemOption(ItemPtr, 8, 15);
		WzAddItemOption(ItemPtr, 9, 10);

		_asm
		{
			Jmp [JMP_SKIP]
		}
	}
	else if (ItemID == GET_ITEM(13, 20))
	{
		_asm
		{
			Jmp [JMP_CONTINUE]
		}
	}
	else
	{
		_asm
		{
			Jmp [JMP_SKIP]
		}
	}
}

__declspec(naked) void FixLethalWizardRingApplyAttributes1()
{
	static const DWORD JMP_OFFSET = MAIN_OFFSET_LWR_APPLY_JMP_1;
	static const DWORD ItemID = 0;
	static const DWORD CharStruct = 0;

	_asm
	{
		Mov Edx, Dword Ptr Ds:[Eax + 0x10]
		Mov ItemID, Edx
	}

	if(ItemID == GET_ITEM(13, 107))
	{

	}

	_asm
	{
		Jmp [JMP_OFFSET]
	}
}

__declspec(naked) void FixLethalWizardRingApplyAttributes2()
{
	static const DWORD JMP_OFFSET = MAIN_OFFSET_LWR_APPLY_JMP_2;
	static const DWORD Item = 0;
	static const DWORD Struct = 0;

	_asm
	{
		Jmp [JMP_OFFSET]
	}
}

DWORD * WzItemTextColorArray = (DWORD*)MAIN_OFFSET_ITEM_TEXT_COLOR;
DWORD * WzItemTextUnkArray = (DWORD*)MAIN_OFFSET_ITEM_TEXT_UNK;
DWORD WzItemTextArray = MAIN_OFFSET_ITEM_TEXT;

void CopyItemText(DWORD & current_line, DWORD color, const char * text, ...)
{
	ARG(buffer, text);
	sprintf((char*)(WzItemTextArray + 100 * current_line), "%s", buffer);
	WzItemTextColorArray[current_line] = color;

	++current_line;
}

__declspec(naked) void ItemShopTextHook()
{
	static DWORD ItemShopTextJMP = MAIN_OFFSET_SHOP_ITEM_TEXT_JMP;

	static DWORD ItemData = 0;
	static DWORD ItemPrice = 0;
	static DWORD CurrentLine = 0;
	static DWORD CurrentEmptyLine = 0;
	static BYTE ItemSlot = 0;
	static char ItemPriceTextTax[100];
	static char ItemPriceText[100];
	
	memset(ItemPriceTextTax, 0, 100);
	memset(ItemPriceText, 0, 100);

	_asm
	{
		Mov Edx, Dword Ptr Ss:[Ebp + 0x10]
		Mov ItemData, Edx

		Mov Eax, Dword Ptr Ss:[Ebp - MAIN_OFFSET_ITEM_TEXT_VAR_2]
		Mov CurrentLine, Eax

		Mov Eax, Dword Ptr Ss:[Ebp - MAIN_OFFSET_ITEM_TEXT_VAR_3]
		Mov CurrentEmptyLine, Eax
	}

	if ( ItemData )
	{
		ItemPrice = WzGetItemPrice(ItemData, 0);
		ItemSlot = *(BYTE*)(ItemData + ITEM_Y) * 8 + *(BYTE*)(ItemData + ITEM_X);

		if ( ItemSlot < 120 )
		{
			if ( ShopPrice[ItemSlot] > 0 )
			{
				ItemPrice = ShopPrice[ItemSlot];
			}
		}

		_asm
		{
			Mov Eax, ItemPrice
			Mov Dword Ptr Ss:[Ebp - MAIN_OFFSET_ITEM_TEXT_VAR_4], Eax
		}

		WzConvertItemPriceTax(ItemPrice, ItemPriceTextTax, 0);
		WzConvertItemPrice(ItemPrice, ItemPriceText);

		switch ( ShopType )
		{
		case 0:
			{
				CopyItemText(CurrentLine, 0, GetTextBMD(1620), ItemPriceText, ItemPriceTextTax);
			} break;

		case 1:
		case 4:
			{
				CopyItemText(CurrentLine, 0, "Purchasing Ruud price: %s(%s)", ItemPriceText, ItemPriceTextTax);
			} break;

		case 2:
			{
				CopyItemText(CurrentLine, 0, "Purchasing WCoin price: %s(%s)", ItemPriceText, ItemPriceTextTax);
			} break;

		case 3:
			{
				CopyItemText(CurrentLine, 0, "Purchasing GP price: %s(%s)", ItemPriceText, ItemPriceTextTax);
			} break;

		case 5:
			{
				CopyItemText(CurrentLine, 0, "Purchasing Rare Ticket price: %s(%s)", ItemPriceText, ItemPriceTextTax);
			} break;

		case 6:
			{
				CopyItemText(CurrentLine, 0, "Purchasing Jewel of Bless price: %s(%s)", ItemPriceText, ItemPriceTextTax);
			} break;

		case 7:
			{
				CopyItemText(CurrentLine, 0, "Purchasing Jewel of Soul price: %s(%s)", ItemPriceText, ItemPriceTextTax);
			} break;

		case 8:
			{
				CopyItemText(CurrentLine, 0, "Purchasing Jewel of Chaos price: %s(%s)", ItemPriceText, ItemPriceTextTax);
			} break;
		}
	}

	_asm
	{
		Jmp [ItemShopTextJMP]
	}
}

void InitItem()
{
	SetCompleteHook(0xE9, MAIN_OFFSET_ITEM_USE_HOOK, &ItemUseHook);
	SetCompleteHook(0xE9, MAIN_OFFSET_LETHAL_WIZARD_RING_HOOK, &FixLethalWizardRingAttributes);

	SetCompleteHook(0xE9, MAIN_OFFSET_SHOP_ITEM_TEXT_HOOK, &ItemShopTextHook);
}