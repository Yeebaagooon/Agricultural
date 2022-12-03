void CreateDot(int x = 0, int z = 0, bool highlight = false){
	trQuestVarSet("temp", trGetNextUnitScenarioNameNumber());
	UnitCreate(0, "Dwarf", x, z, 0);
	trUnitSelectByQV("temp");
	trUnitChangeProtoUnit("Rock Granite Small");
	trUnitSetVariation(1*trQuestVarGet("temp"), 1);
	if(highlight == true){
		trUnitSelectByQV("temp");
		trUnitHighlight(10000, false);
		trQuestVarSet("temp", trGetNextUnitScenarioNameNumber());
		UnitCreate(0, "Dwarf", x, z, 0);
		trUnitSelectByQV("temp");
		trUnitChangeProtoUnit("Acid Pool");
		trUnitSelectByQV("temp");
		trUnitSetAnimationPath("0,1,1,0,0,0,0");
	}
}

rule StartSP
highFrequency
inactive
{
	xsDisableSelf();
	trPaintTerrain(0,0,MapSize,MapSize,5,4);
	//PaintAtlantisArea(0,0,23,23,5,4);
	trQuestVarSetFromRand("Music", 1, 11);
	switch(1*trQuestVarGet("Music"))
	{
		case 1:
		{
			playSound("music\quiet\(fine layers of) slaysenflite (mellow mix).mp3");
		}
		case 2:
		{
			playSound("music\quiet\adult swim (mellow mix).mp3");
		}
		case 3:
		{
			playSound("music\quiet\behold the great science fi (mellow mix).mp3");
		}
		case 4:
		{
			playSound("music\quiet\chocolate outline (mellow mix).mp3");
		}
		case 5:
		{
			playSound("music\quiet\eat your potatoes (mellow mix).mp3");
		}
		case 6:
		{
			playSound("music\quiet\flavor cats (in the comfort zone) (mellow mix).mp3");
		}
		case 7:
		{
			playSound("music\quiet\hoping for real betterness (mellow mix).mp3");
		}
		case 8:
		{
			playSound("music\quiet\in a pile of its own good (mellow mix).mp3");
		}
		case 9:
		{
			playSound("music\quiet\never mind the slacks and bashers (mellow mix).mp3");
		}
		case 10:
		{
			playSound("music\quiet\suture self (mellow mix).mp3");
		}
		case 11:
		{
			playSound("music\quiet\the ballad of ace lebaron (mellow mix).mp3");
		}
	}
	xSetPointer(dPlayerData, 1);
	if(cNumberNonGaiaPlayers == 1){
		xsEnableRule("PaintSP");
		if(xGetInt(dPlayerData, xSeenSP) == 0){
			startNPCDialog(3);
			//TUTORIAL
		}
		else{
			//start
			trCameraCut(vector(23.398306,123.743713,-101.420784), vector(0.004524,-0.707107,0.707092), vector(0.004524,0.707107,0.707093), vector(0.999980,0.000000,-0.006398));
		}
	}
	else{
		startNPCDialog(1);
	}
}

rule PaintSP
highFrequency
inactive
{
	trBlockAllSounds(true);
	trBlockAllAmbientSounds();
	PaintAtlantisArea(0,0,101,5,5,4);
	xSetPointer(dPlayerData, 1);
	xSetPointer(dSkin, 1*trQuestVarGet("WinSkin"));
	for(n = 1; <= 50){
		if(n < xGetInt(dPlayerData, xWins)){
			CreateDot(n*4, 4, true);
		}
		else if(n == xGetInt(dPlayerData, xWins)){
			
			trQuestVarSet("temp", trGetNextUnitScenarioNameNumber());
			UnitCreate(1, "Dwarf", n*4, 4, 90);
			trUnitSelectByQV("temp");
			trUnitChangeProtoUnit("Spy Eye");
			trUnitSelectByQV("temp");
			trMutateSelected(kbGetProtoUnitID("Flag"));
			trUnitSelectByQV("temp");
			trUnitSetAnimationPath("0,1,0,0,0,0");
			CreateDot(n*4, 4, true);
		}
		else if(n > xGetInt(dPlayerData, xWins)){
			CreateDot(n*4, 4, false);
		}
		if(xGetInt(dSkin, xSkinRequirement) == n){
			//create skin unit
			trQuestVarSet("temp", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf", n*4, 6, 180);
			xSetInt(dSkin, xUnitID, 1*trQuestVarGet("temp"));
			trUnitSelectByQV("temp");
			trUnitChangeProtoUnit(""+xGetString(dSkin, xSkinName));
			//UNLOCK
			if(n <= xGetInt(dPlayerData, xWins)){
				//debugLog("Unlocked skin " + (xGetPointer(dSkin)-1));
				xSetInt(dSkin, xSkinUnlocked, 1);
			}
			if(xGetString(dSkin, xSkinName) == "Snowman"){
				trUnitSelectByQV("temp");
				trUnitChangeProtoUnit("Old Man");
				trUnitSelectByQV("temp");
				trSetSelectedScale(1,0.6,1);
				trQuestVarSet("temp", trGetNextUnitScenarioNameNumber());
				UnitCreate(0, "Dwarf", n*4, 6, 180);
				trUnitSelectByQV("temp");
				trUnitChangeProtoUnit("Snowman");
				
			}
			xDatabaseNext(dSkin);
		}
		
	}
	trChangeTerrainHeight(0,7,102,50,8,false);
	//Paint point skins
	PaintAtlantisArea(0,9,101,13,5,4);
	xSetPointer(dSkin, 1*trQuestVarGet("PointSkin"));
	for(n = 1; <= 100){
		if(n < xGetInt(dPlayerData, xMaxBank)){
			CreateDot(n*2, 22, true);
		}
		else if(n == xGetInt(dPlayerData, xMaxBank)){
			
			trQuestVarSet("temp", trGetNextUnitScenarioNameNumber());
			UnitCreate(1, "Dwarf", n*2, 22, 90);
			trUnitSelectByQV("temp");
			trUnitChangeProtoUnit("Spy Eye");
			trUnitSelectByQV("temp");
			trMutateSelected(kbGetProtoUnitID("Flag"));
			trUnitSelectByQV("temp");
			trUnitSetAnimationPath("0,1,0,0,0,0");
			CreateDot(n*2, 22, true);
		}
		else if(n > xGetInt(dPlayerData, xMaxBank)){
			CreateDot(n*2, 22, false);
		}
		
		if(xGetInt(dSkin, xSkinRequirement) == n){
			//create skin unit
			trQuestVarSet("temp", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf", n*2, 24, 180);
			xSetInt(dSkin, xUnitID, 1*trQuestVarGet("temp"));
			trUnitSelectByQV("temp");
			trUnitChangeProtoUnit(""+xGetString(dSkin, xSkinName));
			if(n <= xGetInt(dPlayerData, xMaxBank)){
				////debugLog("Unlocked skin " + (xGetPointer(dSkin)-1));
				xSetInt(dSkin, xSkinUnlocked, 1);
			}
			if(xGetString(dSkin, xSkinName) == "Chicken"){
				trUnitSelectByQV("temp");
				trSetSelectedScale(2,2,2);
			}
			xDatabaseNext(dSkin);
		}
	}
	//unitTransform("Titan Gate Dead", "Heavenlight");
	trChangeTerrainHeight(0,16,102,50,11,false);
	//Paint PB skins
	//n *10 = each dot worth 10 points
	PaintAtlantisArea(0,18,101,22,5,4);
	xSetPointer(dSkin, 1*trQuestVarGet("PBSkin"));
	for(n = 1; <= 100){
		if(n*10 <= xGetInt(dPlayerData, xPersonalBest)){
			CreateDot(n*2, 40, true);
		}
		else if(n*10 > xGetInt(dPlayerData, xPersonalBest)){
			CreateDot(n*2, 40, false);
		}
		
		if(xGetInt(dSkin, xSkinRequirement) == n*10){
			//create skin unit
			trQuestVarSet("temp", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Dwarf", n*2, 42, 180);
			xSetInt(dSkin, xUnitID, 1*trQuestVarGet("temp"));
			trUnitSelectByQV("temp");
			trUnitChangeProtoUnit(""+xGetString(dSkin, xSkinName));
			//trMutateSelected(kbGetProtoUnitID(""+xGetString(dSkin, xSkinName)));
			//UNLOCK
			if(n*10 <= xGetInt(dPlayerData, xPersonalBest)){
				////	debugLog("Unlocked skin " + (xGetPointer(dSkin)-1));
				xSetInt(dSkin, xSkinUnlocked, 1);
			}
			xDatabaseNext(dSkin);
		}
	}
	//Dynamic flag since PB might not always be modulo10
	trQuestVarSet("temp", trGetNextUnitScenarioNameNumber());
	UnitCreate(1, "Dwarf", xGetInt(dPlayerData, xPersonalBest)/5, 40, 90);
	trUnitSelectByQV("temp");
	trUnitChangeProtoUnit("Spy Eye");
	trUnitSelectByQV("temp");
	trMutateSelected(kbGetProtoUnitID("Flag"));
	trUnitSelectByQV("temp");
	trUnitSetAnimationPath("0,1,0,0,0,0");
	xsDisableSelf();
	
	trChangeTerrainHeight(0,24,102,50,14,false);
	//Paint PB skins
	//n *10 = each dot worth 10 points
	PaintAtlantisArea(0,27,101,31,5,4);
	
	xSetPointer(dSkin, 1*trQuestVarGet("ExtraSkin"));
	for(n = 1; <= 6){
		//No dot as no progression here
		//create skin unit
		trQuestVarSet("temp", trGetNextUnitScenarioNameNumber());
		UnitCreate(0, "Dwarf", n*8, 58, 180);
		xSetInt(dSkin, xUnitID, 1*trQuestVarGet("temp"));
		trUnitSelectByQV("temp");
		trUnitChangeProtoUnit(""+xGetString(dSkin, xSkinName));
		//trMutateSelected(kbGetProtoUnitID(""+xGetString(dSkin, xSkinName)));
		if(n == 1){
			if(false){
				xSetInt(dSkin, xSkinUnlocked, 1);
				trUnitSelectByQV("temp");
				trUnitHighlight(10000, false);
			}
		}
		if(n == 2){
			if(trGetScenarioUserData(15, "motherload") > 0){
				xSetInt(dSkin, xSkinUnlocked, 1);
				trUnitSelectByQV("temp");
				trUnitHighlight(10000, false);
			}
		}
		if(n == 3){
			if(trGetScenarioUserData(0, "motherload") == 10){
				xSetInt(dSkin, xSkinUnlocked, 1);
				trUnitSelectByQV("temp");
				trUnitHighlight(10000, false);
			}
		}
		if(n == 4){
			if(xGetInt(dPlayerData, xSDWins) > 0){
				xSetInt(dSkin, xSkinUnlocked, 1);
				trUnitSelectByQV("temp");
				trUnitHighlight(10000, false);
			}
		}
		if(n == 5){
			if(trGetScenarioUserData(10, "motherload") == 884731){
				xSetInt(dSkin, xSkinUnlocked, 1);
				trUnitSelectByQV("temp");
				trUnitHighlight(10000, false);
			}
		}
		if(n == 6){
			if(trGetScenarioUserData(8, "Ascension MMORPG") >= 70392960){
				xSetInt(dSkin, xSkinUnlocked, 1);
				trUnitSelectByQV("temp");
				trUnitHighlight(10000, false);
			}
		}
		xDatabaseNext(dSkin);
	}
	if(xGetInt(dPlayerData, xSkin) > 1*trQuestVarGet("WinSkin")){
		for (x=xGetDatabaseCount(dSkin); > 0) {
			xDatabaseNext(dSkin);
			if(xGetPointer(dSkin) == xGetInt(dPlayerData, xSkin)){
				xUnitSelect(dSkin, xUnitID);
				trUnitChangeProtoUnit("Titan Atlantean");
				xUnitSelect(dSkin, xUnitID);
				trUnitChangeProtoUnit(""+xGetString(dSkin, xSkinName));
				xUnitSelect(dSkin, xUnitID);
				trUnitHighlight(10000, true);
				characterDialog("Current skin - " + xGetString(dSkin, xSkinName), " ", "");
				continue;
			}
		}
	}
	trDelayedRuleActivation("SkinConvertGaia");
	xsEnableRule("SelectSkinsSP");
}

rule SkinConvertGaia
inactive
highFrequency
{
	for (x=xGetDatabaseCount(dSkin); > 0) {
		xDatabaseNext(dSkin);
		xUnitSelect(dSkin, xUnitID);
		trUnitConvert(0);
	}
	unitTransform("Titan Gate Dead", "Gaia Forest effect");
	xsDisableSelf();
	trUnblockAllSounds();
	trUnBlockAllAmbientSounds();
}

void GoToMainMenu(int p = 0){
	modeEnter("Campaign");
	modeEnter("Pregame");
	xsDisableSelf();
}

void SPHelp(int p = 0){
	startNPCDialog(2);
	xsDisableSelf();
}

void ChooseASkin(int p = 0){
	xsSetContextPlayer(0);
	p = p-20;
	xSetPointer(dPlayerData, 1);
	xSetInt(dPlayerData, xSkin, p);
	saveAllData();
	if(xGetInt(dPlayerData, xWins) < 3){
		uiMessageBox("Skin choice saved!");
	}
	playSound("arkantosleave.wav");
	trEndGame();
	trModeEnter("Pregame");
}

rule SelectSkinsSP
inactive
highFrequency
{
	xDatabaseNext(dSkin);
	xUnitSelect(dSkin,xUnitID);
	int req = 0;
	int cur = 0;
	xSetPointer(dPlayerData, 1);
	if (trUnitIsSelected()) {
		uiClearSelection();
		if(xGetInt(dSkin, xSkinUnlocked) == 0){
			if((xGetPointer(dSkin) >= trQuestVarGet("WinSkin")) && (xGetPointer(dSkin) < trQuestVarGet("PointSkin"))){
				req = xGetInt(dSkin, xSkinRequirement);
				cur = xGetInt(dPlayerData, xWins);
				uiMessageBox("This skin is locked! You need " + req + " wins to unlock. (Current = " + cur + ")");
			}
			else if((xGetPointer(dSkin) >= trQuestVarGet("PointSkin")) && (xGetPointer(dSkin) < trQuestVarGet("PBSkin"))){
				req = xGetInt(dSkin, xSkinRequirement);
				cur = xGetInt(dPlayerData, xMaxBank);
				uiMessageBox("This skin is locked! You need to bank " + req + " points in one go to unlock. (Current = " + cur + ")");
			}
			else if((xGetPointer(dSkin) >= trQuestVarGet("PBSkin")) && (xGetPointer(dSkin) < trQuestVarGet("ExtraSkin"))){
				req = xGetInt(dSkin, xSkinRequirement);
				cur = xGetInt(dPlayerData, xPersonalBest);
				uiMessageBox("This skin is locked! You need a personal best of " + req + " points to unlock. (Current = " + cur + ")");
			}
			//SPECIALS
			else if(xGetPointer(dSkin) >= trQuestVarGet("ExtraSkin")){
				startNPCDialog(xGetPointer(dSkin)-40);
			}
		}
		else{
			trShowChoiceDialog("Select this skin?", "Yes", (20+(xGetPointer(dSkin))), "No", -1);
		}
		//	debugLog(""+(xGetPointer(dSkin)));
	}
}
