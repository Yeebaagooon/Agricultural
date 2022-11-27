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
	xSetPointer(dPlayerData, 1);
	if(cNumberNonGaiaPlayers == 1){
		xsEnableRule("PaintSP");
		if(xGetInt(dPlayerData, xSeenSP) == 0){
			startNPCDialog(3);
			//TUTORIAL
		}
		else{
			//start
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
				debugLog("Unlocked skin " + (xGetPointer(dSkin)-1));
				xSetInt(dSkin, xSkinUnlocked, 1);
				trUnitSelectByQV("temp");
				trUnitChangeProtoUnit("Villager Egyptian");
				trUnitSelectByQV("temp");
				trUnitConvert(1);
				spyEffect(1*trQuestVarGet("temp"), kbGetProtoUnitID("Hero Birth"), vector(0,0,0), vector(1,1,1));
				trUnitSelectByQV("temp");
				trUnitChangeProtoUnit(""+xGetString(dSkin, xSkinName));
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
			//trMutateSelected(kbGetProtoUnitID(""+xGetString(dSkin, xSkinName)));
			//UNLOCK
			if(n <= xGetInt(dPlayerData, xMaxBank)){
				debugLog("Unlocked skin " + (xGetPointer(dSkin)-1));
				xSetInt(dSkin, xSkinUnlocked, 1);
				trUnitSelectByQV("temp");
				trUnitChangeProtoUnit("Villager Egyptian");
				trUnitSelectByQV("temp");
				trUnitConvert(1);
				spyEffect(1*trQuestVarGet("temp"), kbGetProtoUnitID("Hero Birth"), vector(0,0,0), vector(1,1,1));
				trUnitSelectByQV("temp");
				trUnitChangeProtoUnit(""+xGetString(dSkin, xSkinName));
			}
			xDatabaseNext(dSkin);
		}
	}
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
				debugLog("Unlocked skin " + (xGetPointer(dSkin)-1));
				xSetInt(dSkin, xSkinUnlocked, 1);
				trUnitSelectByQV("temp");
				trUnitChangeProtoUnit("Villager Egyptian");
				trUnitSelectByQV("temp");
				trUnitConvert(1);
				spyEffect(1*trQuestVarGet("temp"), kbGetProtoUnitID("Hero Birth"), vector(0,0,0), vector(1,1,1));
				trUnitSelectByQV("temp");
				trUnitChangeProtoUnit(""+xGetString(dSkin, xSkinName));
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
		xDatabaseNext(dSkin);
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
	playSound("arrkantosleave.wav");
	trEndGame();
	trModeEnter("Pregame");
}

rule SelectSkinsSP
inactive
highFrequency
{
	xDatabaseNext(dSkin);
	xUnitSelect(dSkin,xUnitID);
	if (trUnitIsSelected()) {
		uiClearSelection();
		if(xGetInt(dSkin, xSkinUnlocked) == 0){
			uiMessageBox("This skin is locked!");
		}
		else{
			trShowChoiceDialog("Select this skin?", "Yes", (20+(xGetPointer(dSkin))), "No", -1);
			debugLog(""+(xGetPointer(dSkin)-1));
		}
	}
}
