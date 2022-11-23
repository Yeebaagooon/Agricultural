rule PaintTerrain
highFrequency
inactive
{
	//if (trTime() > cActivationTime + 1) {
	xsDisableSelf();
	for(x=1 ; <= MapSize/6){
		for(z=1 ; <= MapSize/6){
			paintShopSquare(x*3-2,z*3-2, "black");
			trQuestVarSet("FarmX"+x+"Z"+z+"", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Cinematic Block", x*6-4, z*6-4, 0);
			xAddDatabaseBlock(dFlags, true);
			xSetInt(dFlags, xUnitID, 0);
			xSetInt(dFlags, xFlagX, x);
			xSetInt(dFlags, xFlagZ, z);
			xSetInt(dFlags, xFlagOwner, 0);
		}
	}
	for(x=1 ; <= MapSize/6){
		for(z=1 ; <= MapSize/6){
			trUnitSelectClear();
			trUnitSelectByQV("FarmX"+x+"Z"+z+"");
			trUnitChangeProtoUnit("Farm");
		}
	}
	XMax = MapSize/6;
	ZMax = MapSize/6;
	trVectorQuestVarSet("dir", xsVectorSet(MapSize*-0.3, 0, MapSize*-0.3));
	trVectorQuestVarSet("CentreMap", xsVectorSet(MapSize*0.5-1, 0, MapSize*0.5-1));
	float baseCos = xsCos(6.283185 / cNumberNonGaiaPlayers);
	float baseSin = xsSin(6.283185 / cNumberNonGaiaPlayers);
	int heading = 45+(360/cNumberNonGaiaPlayers);
	for(p=1; <= cNumberNonGaiaPlayers) {
		trVectorQuestVarSet("base", trVectorQuestVarGet("CentreMap") + trVectorQuestVarGet("dir"));
		trQuestVarSet("P"+p+"Farmer", trGetNextUnitScenarioNameNumber());
		heading = heading-(360/cNumberNonGaiaPlayers);
		if(heading > 360){
			heading = heading-360;
		}
		if(heading < 0){
			heading = heading+360;
		}
		UnitCreate(0, "Cinematic Block", trVectorQuestVarGetX("base"), trVectorQuestVarGetZ("base"), heading);
		trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
		trUnitSelectClear();
		trUnitSelectByQV("P"+p+"Farmer");
		xSetPointer(dPlayerData, p);
		xSetInt(dPlayerData, xUnitID, 1*trQuestVarGet("P"+p+"Farmer"));
		switch(1*trQuestVarGet("P"+p+"Skin"))
		{
			case 0:
			{
				trUnitChangeProtoUnit("Villager Atlantean");
			}
			case 1:
			{
				trUnitChangeProtoUnit("Villager Greek");
			}
			case 2:
			{
				trUnitChangeProtoUnit("Villager Egyptian");
			}
			case 3:
			{
				trUnitChangeProtoUnit("Villager Norse");
			}
			case 4:
			{
				trUnitChangeProtoUnit("Villager Chinese");
			}
		}
		trUnitSelectByQV("P"+p+"Farmer");
		trSetSelectedScale(2,2,2);
	}
	trCameraCut(vector(-63.781834,123.743729,-63.781834), vector(0.500000,-0.707107,0.500000), vector(0.500000,0.707107,0.500000), vector(0.707107,0.000000,-0.707107));
	int a = trCurrentPlayer();
	trUnitSelectClear();
	trUnitSelectByQV("P"+a+"Farmer");
	trUnitHighlight(3, true);
	uiLookAtUnit(kbGetBlockID(""+1*trQuestVarGet("P"+a+"Farmer")));
	trQuestVarSet("Round", 1*trQuestVarGet("Round")+1);
	trOverlayText("Round " + 1*trQuestVarGet("Round") , 5.0, 608, 300, 1000);
	xsEnableRule("RoundStart");
}

rule PaintSkinArea
highFrequency
inactive
{
	xsDisableSelf();
	trPaintTerrain(0,0,MapSize,MapSize,2,1);
	trPaintTerrainCircle(MapSize/4-1, MapSize/4-1, 9, 0, 95);
	trPaintTerrain(0,0,0,0,2,1, true);
	trVectorQuestVarSet("dir", xsVectorSet(14, 0, 0));
	trVectorQuestVarSet("CentreMap", xsVectorSet(MapSize*0.5-1, 0, MapSize*0.5-1));
	//Cceate Skins
	float baseCos = xsCos(6.283185 / 4);
	float baseSin = xsSin(6.283185 / 4);
	int heading = 390;
	for(n=1; <= 4) {
		trVectorQuestVarSet("base", trVectorQuestVarGet("CentreMap") + trVectorQuestVarGet("dir"));
		trQuestVarSet("Skin"+n+"", trGetNextUnitScenarioNameNumber());
		heading = heading-90;
		UnitCreate(0, "Cinematic Block", trVectorQuestVarGetX("base"), trVectorQuestVarGetZ("base"), heading);
		trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
		trUnitSelectClear();
		trUnitSelectByQV("Skin"+n+"");
		switch(n)
		{
			case 1:
			{
				trUnitChangeProtoUnit("Villager Greek");
			}
			case 2:
			{
				trUnitChangeProtoUnit("Villager Egyptian");
			}
			case 3:
			{
				trUnitChangeProtoUnit("Villager Norse");
			}
			case 4:
			{
				trUnitChangeProtoUnit("Villager Chinese");
			}
		}
		trUnitSelectClear();
		trUnitSelectByQV("Skin"+n+"");
		trSetSelectedScale(2,2,2);
		trUnitSelectByQV("Skin"+n+"");
		trUnitOverrideAnimation(9,0,true,true,-1,0);
		xsEnableRule("SkinChooserDeploy");
		trCameraCut(vector(-63.781834,123.743729,-63.781834), vector(0.500000,-0.707107,0.500000), vector(0.500000,0.707107,0.500000), vector(0.707107,0.000000,-0.707107));
	}
}

rule SkinChooserDeploy
inactive
highFrequency
{
	xsDisableSelf();
	//Create choosers
	trVectorQuestVarSet("dir", xsVectorSet(4,0,0));
	trVectorQuestVarSet("CentreMap", xsVectorSet(MapSize*0.5-1, 0, MapSize*0.5-1));
	float baseCos = xsCos(6.283185 / cNumberNonGaiaPlayers);
	float baseSin = xsSin(6.283185 / cNumberNonGaiaPlayers);
	int heading = 270+(360/cNumberNonGaiaPlayers);
	for(p=1; <= cNumberNonGaiaPlayers) {
		heading = heading-(360/cNumberNonGaiaPlayers);
		trVectorQuestVarSet("base", trVectorQuestVarGet("CentreMap") + trVectorQuestVarGet("dir"));
		trQuestVarSet("P"+p+"SkinChooser", trGetNextUnitScenarioNameNumber());
		UnitCreate(p, "Cinematic Block", trVectorQuestVarGetX("base"), trVectorQuestVarGetZ("base"), heading);
		trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
		trUnitSelectClear();
		trUnitSelectByQV("P"+p+"SkinChooser");
		trUnitChangeProtoUnit("Villager Atlantean Hero");
		if(p == trCurrentPlayer()){
			trUnitSelectClear();
			trUnitSelectByQV("P"+p+"SkinChooser");
			trUnitHighlight(30, true);
		}
	}
	trMessageSetText("Move to a villager to choose your skin (cosmetic only). If all players delete the counter ends.", 8000);
	trCounterAddTime("CDSkin", 15-(14*QuickStart), 0, "<color={PlayerColor(1)}>Time remaining", 14);
	xsEnableRule("SkinChange");
	xsEnableRule("SkinEarlyEnd");
}

rule SkinChange
inactive
minInterval 1
{
	for(p=1; <= cNumberNonGaiaPlayers) {
		trUnitSelectClear();
		trUnitSelectByQV("P"+p+"SkinChooser");
		for(n=1; <= 4) {
			if(trUnitDistanceToUnit(""+1*trQuestVarGet("Skin"+n+"")) < 3){
				if(1*trQuestVarGet("P"+p+"Skin") != n){
					trQuestVarSet("P"+p+"Skin", n);
					switch(n)
					{
						case 1:
						{
							trUnitChangeProtoUnit("Villager Greek");
						}
						case 2:
						{
							trUnitChangeProtoUnit("Villager Egyptian");
						}
						case 3:
						{
							trUnitChangeProtoUnit("Villager Norse");
						}
						
						case 4:
						{
							trUnitChangeProtoUnit("Villager Chinese");
						}
					}
					if(p == trCurrentPlayer()){
						trUnitSelectClear();
						trUnitSelectByQV("P"+p+"SkinChooser");
						trUnitHighlight(1, true);
					}
				}
			}
		}
	}
}

void SkinTimeEnd (int p = 0){
	xsDisableSelf();
	xsEnableRule("SkinCommonEnd");
}

rule SkinEarlyEnd
inactive
highFrequency
{
	int CallsToEnd = 0;
	for(p=1; <= cNumberNonGaiaPlayers) {
		if(trPlayerGetPopulation(p) == 0){
			CallsToEnd = CallsToEnd+1;
		}
	}
	if(CallsToEnd == cNumberNonGaiaPlayers){
		xsDisableSelf();
		xsEnableRule("SkinCommonEnd");
		trCounterAbort("CDSkin");
		trMessageSetText("Move to a villager to choose your skin (cosmetic only). If all players delete the counter ends.", 1);
	}
}

rule SkinCommonEnd
inactive
highFrequency
{
	xsDisableSelf();
	trCounterAbort("CDSkin");
	xsDisableRule("SkinChange");
	xsDisableRule("SkinEarlyEnd");
	for(p=1; <= cNumberNonGaiaPlayers) {
		trUnitSelectClear();
		trUnitSelectByQV("P"+p+"SkinChooser");
		trUnitChangeProtoUnit("Hero Death");
		modifyProtounitAbsolute("Villager Greek", p, 1, 6);
		modifyProtounitAbsolute("Villager Egyptian", p, 1, 6);
		modifyProtounitAbsolute("Villager Norse", p, 1, 6);
		modifyProtounitAbsolute("Villager Chinese", p, 1, 6);
		modifyProtounitAbsolute("Villager Atlantean Hero", p, 1, 6);
		modifyProtounitAbsolute("Villager Atlantean", p, 1, 6);
	}
	for(n=1; <= 4) {
		trUnitSelectClear();
		trUnitSelectByQV("Skin"+n+"");
		trUnitChangeProtoUnit("Heavenlight");
	}
	playSound("ageadvance.wav");
	trUIFadeToColor(0,0,0,800,199,true);
	xsEnableRule("CineChoice");
}
