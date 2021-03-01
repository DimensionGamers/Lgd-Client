CastleSiege g_CastleSiege;

CastleSiege::CastleSiege()
{
	this->SwitchState = CASTLE_SIEGE_SWITCH_STATE_NONE;
	this->CrownState = CASTLE_SIEGE_CROWN_STATE_NONE;
	this->CrownMasterState = CASTLE_SIEGE_CROWN_MASTER_STATE_NONE;
}

CastleSiege::~CastleSiege()
{

}

void CastleSiege::SetSwitchData(BYTE state, WORD index, WORD monster)
{
	this->SwitchState = state;

	this->SwitchTime.Start(3000);

	char buff[256];
	switch(this->SwitchState)
	{
	case CASTLE_SIEGE_SWITCH_STATE_ON:
		{
			sprintf(buff, "%s", GetTextBMD(1485));
		} break;

	case CASTLE_SIEGE_SWITCH_STATE_OFF:
		{
			sprintf(buff, "%s", GetTextBMD(1484));
		} break;

	case CASTLE_SIEGE_SWITCH_STATE_BUSY:
		{
			sprintf(buff, "Switch is already in use.");
		} break;
	}

	this->SwitchString = buff;
}

void CastleSiege::PrintSwitch()
{
	if (!IsCastleSiege())
	{
		return;
	}

	if(this->SwitchState == CASTLE_SIEGE_SWITCH_STATE_NONE)
	{
		return;
	}

	if(this->SwitchTime.Elapsed())
	{
		this->SwitchState = CASTLE_SIEGE_SWITCH_STATE_NONE;
		return;
	}

	float StartX = (MAX_WIN_WIDTH/2.0f)-(160.0f/2.0f);

	float StartY = 115.0f;

	float progress = (this->SwitchTime.GetRemain() * 150.0f)/(float)this->SwitchTime.Time;

	progress = ((progress>150)?150:progress);

	DrawInterface(0x7B14,StartX - 25.0f,StartY - 40.0f, 209.0f, 80.0f);

	DrawInterface(0x7A65,StartX,StartY,160.0f,18.0f);

	DrawInterface(0x7A66,(StartX+5.0f),(StartY+5.0f),progress,8.0f);

	char buff[256];
	sprintf(buff, "%s", this->SwitchString.c_str());

	DrawInterfaceText(buff,(int)StartX,(int)(StartY-15.0f),0xFFFFFFFF,0,3,160.0f,0);
}

void CastleSiege::SetCrownData(BYTE state)
{
	this->CrownState = state;

	this->CrownTime.Start(3000);

	char buff[256];
	switch(this->CrownState)
	{
	case CASTLE_SIEGE_CROWN_STATE_ON:
		{
			sprintf(buff, "%s", GetTextBMD(1494));
		} break;

	case CASTLE_SIEGE_CROWN_STATE_OFF:
		{
			sprintf(buff, "%s", GetTextBMD(1493));
		} break;
	}

	this->CrownString = buff;
}

void CastleSiege::PrintCrown()
{
	if (!IsCastleSiege())
	{
		return;
	}

	if(this->CrownState == CASTLE_SIEGE_CROWN_STATE_NONE)
	{
		return;
	}

	if(this->CrownTime.Elapsed())
	{
		this->CrownState = CASTLE_SIEGE_CROWN_STATE_NONE;
		return;
	}

	float StartX = (MAX_WIN_WIDTH/2.0f)-(160.0f/2.0f);

	float StartY = 115.0f;

	float progress = (this->CrownTime.GetRemain() * 150.0f)/(float)this->CrownTime.Time;

	progress = ((progress>150)?150:progress);

	DrawInterface(0x7B14,StartX - 25.0f,StartY - 40.0f, 209.0f, 80.0f);

	DrawInterface(0x7A65,StartX,StartY,160.0f,18.0f);

	DrawInterface(0x7A66,(StartX+5.0f),(StartY+5.0f),progress,8.0f);

	char buff[256];
	sprintf(buff, "%s", this->CrownString.c_str());

	DrawInterfaceText(buff,(int)StartX,(int)(StartY-15.0f),0xFFFFFFFF,0,3,160.0f,0);
}

void CastleSiege::SetCrownMasterData(BYTE state, DWORD time)
{
	this->CrownMasterState = state;

	this->CrownMasterTime.Start(3000);

	char buff1[256];
	char buff2[256];
	this->CrownMasterString2.clear();
	this->CrownMasterString1.clear();
	switch(this->CrownMasterState)
	{
	case CASTLE_SIEGE_CROWN_MASTER_STATE_ATTEMPT:
		{
			sprintf(buff1, "%s", GetTextBMD(1489));
			sprintf(buff2, "(Accumulated time: %d seconds)", time / 1000);

			this->CrownMasterTime.Start(61000);
			this->CrownMasterTime.Time -= time;

			this->CrownMasterString2 = buff2;
		} break;

	case CASTLE_SIEGE_CROWN_MASTER_STATE_SUCCESS:
		{
			sprintf(buff1, "%s", GetTextBMD(1490));
		} break;

	case CASTLE_SIEGE_CROWN_MASTER_STATE_FAIL:
		{
			sprintf(buff1, "%s", GetTextBMD(1491));
			sprintf(buff2, "(Accumulated time: %d seconds)", time / 1000);

			this->CrownMasterString2 = buff2;
		} break;

	case CASTLE_SIEGE_CROWN_MASTER_STATE_TAKEN:
		{
			//sprintf(buff1, "%s", GetTextBMD(1492));
		} break;

	case CASTLE_SIEGE_CROWN_MASTER_STATE_WRONG_SWITCH:
		{
			//sprintf(buff1, "%s", GetTextBMD(1982));
		} break;
	}

	this->CrownMasterString1 = buff1;
}
	
void CastleSiege::PrintMasterCrown()
{
	if (!IsCastleSiege())
	{
		return;
	}

	if( this->CrownMasterState == CASTLE_SIEGE_CROWN_MASTER_STATE_NONE ||
		this->CrownMasterState == CASTLE_SIEGE_CROWN_MASTER_STATE_TAKEN ||
		this->CrownMasterState == CASTLE_SIEGE_CROWN_MASTER_STATE_WRONG_SWITCH)
	{
		return;
	}

	if(this->CrownMasterTime.Elapsed())
	{
		this->CrownMasterState = CASTLE_SIEGE_CROWN_MASTER_STATE_NONE;
		return;
	}

	float StartX = (MAX_WIN_WIDTH/2.0f)-(160.0f/2.0f);

	float StartY = 115.0f;

	float progress = (float(this->CrownMasterTime.GetRemain()) * 150.0f)/(float)this->CrownMasterTime.Time;

	progress = ((progress>150)?150:progress);

	DrawInterface(0x7B14,StartX - 25.0f,StartY - 40.0f, 209.0f, 80.0f);

	DrawInterface(0x7A65,StartX,StartY,160.0f,18.0f);

	DrawInterface(0x7A66,(StartX+5.0f),(StartY+5.0f),progress,8.0f);

	char buff1[256];
	sprintf(buff1, "%s", this->CrownMasterString1.c_str());

	DrawInterfaceText(buff1,(int)StartX,(int)(StartY-20.0f),0xFFFFFFFF,0,3,160.0f,0);

	if(!this->CrownMasterString2.empty())
	{
		char buff2[256];
		sprintf(buff2, "%s", this->CrownMasterString2.c_str());

		DrawInterfaceText(buff2,(int)StartX,(int)(StartY-10.0f),0xFFFFFFFF,0,3,160.0f,0);
	}
}