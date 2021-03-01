CustomObjectMgr g_CustomObjectMgr;

CustomObjectMgr::CustomObjectMgr()
{
	for ( int i = 0; i < MAX_VIEWPORT_OBJECT; ++i )
	{
		this->ObjectData[i].Reset();
	}
}

CustomObjectMgr::~CustomObjectMgr()
{

}

void CustomObjectMgr::Update()
{
	if (GetMainState() != MAIN_STATE_PLAYING)
	{
		for ( int i = 0; i < MAX_VIEWPORT_OBJECT; ++i )
		{
			this->ObjectData[i].Reset();
		}
	}
}

void CustomObjectMgr::GCRemoveMonsterData(BYTE * Packet)
{
	VIEWPORT_DESTROY_COMPLETE * lpMsg = (VIEWPORT_DESTROY_COMPLETE*)Packet;

	WORD index = MAKE_NUMBERW(lpMsg->IndexH, lpMsg->IndexL);

	for ( int i = 0; i < MAX_VIEWPORT_OBJECT; ++i )
	{
		if ( this->ObjectData[i].index == index )
		{
			this->ObjectData[i].Reset();
		}
	}
}

void CustomObjectMgr::GCSetMonsterData(BYTE * Packet)
{
	VIEWPORT_MONSTER_CUSTOM_DATA * lpMsg = (VIEWPORT_MONSTER_CUSTOM_DATA*)Packet;

	if ( lpMsg->index == WORD(-1) )
	{
		return;
	}

	for ( int i = 0; i < MAX_VIEWPORT_OBJECT; ++i )
	{
		ObjectViewport* object = WzGetObjectStructByPos(i);

		if (!object)
		{
			continue;
		}

		if ( WzIsObjectLoaded(*(DWORD*)object) && object->index == lpMsg->index )
		{
			if ( this->ObjectData[i].index != lpMsg->index )
			{
				this->ObjectData[i].index = lpMsg->index;
				this->ObjectData[i].scale = object->scale;
			}

			if ( strlen(lpMsg->name) )
			{
				WzSetObjectName(object, lpMsg->name);
			}

			for ( int n = 0; n < 12; ++n )
			{
				SetMonsterEquipment(object, lpMsg->equipment[n], n);
			}

			object->type = lpMsg->type;
			object->scale = this->ObjectData[i].scale * lpMsg->size;
			break;
		}
	}
}

void CustomObjectMgr::SetMonsterEquipment(ObjectViewport* pObject, VIEWPORT_MONSTER_CUSTOM_EQUIPMENT const& equipment, BYTE slot)
{
	if ( !pObject )
	{
		return;
	}

	if ( equipment.item == WORD(-1) )
	{
		return;
	}

	ObjectViewportItem * pItem = NULL;

	switch ( slot )
	{
	case 0:
		{
			pItem = &pObject->weapon_01;
		} break;

	case 1:
		{
			pItem = &pObject->weapon_02;
		} break;

	case 2:
		{
			pItem = &pObject->helm;
		} break;

	case 3:
		{
			pItem = &pObject->armor;
		} break;

	case 4:
		{
			pItem = &pObject->pants;
		} break;

	case 5:
		{
			pItem = &pObject->gloves;
		} break;

	case 6:
		{
			pItem = &pObject->boots;
		} break;

	case 7:
		{
			pItem = &pObject->wings;
		} break;

	case 8:
		{
			pItem = &pObject->pet;
		} break;
	}
	
	if ( !pItem )
	{
		return;
	}

	pItem->id = equipment.item + ITEM_BASE_MODEL;
	pItem->level = equipment.level;
	pItem->excellent = equipment.excellent_ancient & 1;
	pItem->ancient = equipment.excellent_ancient & 2;
}