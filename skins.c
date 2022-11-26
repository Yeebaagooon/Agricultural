rule Animations
highFrequency
inactive
{
	int anim = 0;
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(xGetInt(dPlayerData, xSkin) <= 4){
			break;
		}
		if(xGetInt(dPlayerData, xSkin) > 4){
			anim = 0;
			anim = kbUnitGetAnimationActionType(kbGetBlockID(""+1*trQuestVarGet("P"+p+"Farmer")+""));
			xSetPointer(dPlayerData, p);
			if((xGetInt(dPlayerData, xOldAnim) == anim) || (xGetInt(dPlayerData, xOldAnim) == -10)){
				break;
				//Stop if no anim change
			}
			if((xGetInt(dPlayerData, xSkin) == 5) || (xGetInt(dPlayerData, xSkin) == 6)){
				xSetInt(dPlayerData, xOldAnim, anim);
				//Walk
				if((anim == 10) || (anim == 11)){
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitOverrideAnimation(15, 0, true, true, -1, 0);
				}
				//Gather
				if((anim == 5)){
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitOverrideAnimation(9, 0, true, true, -1, 0);
				}
				//Idle
				if((anim == 9)){
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitOverrideAnimation(2, 0, true, true, -1, 0);
				}
				//Flail
				if((anim == 29)){
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitOverrideAnimation(24, 0, true, true, -1, 0);
				}
			}
			if(xGetInt(dPlayerData, xSkin) == 46){
				xSetInt(dPlayerData, xOldAnim, anim);
				//Walk
				if((anim == 10) || (anim == 11)){
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitOverrideAnimation(15, 0, true, true, -1, 0);
				}
				//Gather
				if((anim == 5)){
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitOverrideAnimation(26, 0, true, true, -1, 0);
				}
				//Idle
				if((anim == 9)){
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitOverrideAnimation(2, 0, true, true, -1, 0);
				}
				//Flail
				if((anim == 29)){
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitOverrideAnimation(24, 0, true, true, -1, 0);
				}
			}
			if(xGetInt(dPlayerData, xSkin) == 47){
				xSetInt(dPlayerData, xOldAnim, anim);
				//Walk
				if((anim == 10) || (anim == 11)){
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitOverrideAnimation(15, 0, true, true, -1, 0);
				}
				//Gather
				if((anim == 5)){
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitOverrideAnimation(25, 0, true, true, -1, 0);
				}
				//Idle
				if((anim == 9)){
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitOverrideAnimation(2, 0, true, true, -1, 0);
				}
				//Flail
				if((anim == 29)){
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitOverrideAnimation(24, 0, true, true, -1, 0);
				}
			}
		}
	}
}

string SkinProto(int id = 0) {
	string msg = "WTF That's not a skin!";
	switch(id)
	{
		case 5:
		{
			msg = "Brokk";
		}
		case 6:
		{
			msg = "Eitri";
		}
		case 46:
		{
			msg = "Minotaur";
		}
		case 47:
		{
			msg = "Pharaoh of Osiris XP";
		}
	}
	return(msg);
}

rule ConvertSpies
highFrequency
inactive
{
	xsDisableSelf();
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(xGetInt(dPlayerData, xSkin) > 4){
			xUnitSelect(dPlayerData, xSpyID);
			trUnitChangeProtoUnit("Villager Greek");
			xUnitSelect(dPlayerData, xSpyID);
			trUnitConvert(p);
			xUnitSelect(dPlayerData, xSpyID);
			trUnitChangeProtoUnit("Spy Eye");
			xUnitSelect(dPlayerData, xSpyID);
			trMutateSelected(kbGetProtoUnitID(""+SkinProto(xGetInt(dPlayerData, xSkin))));
			xUnitSelect(dPlayerData, xSpyID);
			trSetSelectedScale(2,2,2);
		}
	}
}

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
		UnitCreate(p, "Cinematic Block", trVectorQuestVarGetX("base"), trVectorQuestVarGetZ("base"), heading);
		trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
		trUnitSelectClear();
		trUnitSelectByQV("P"+p+"Farmer");
		xSetPointer(dPlayerData, p);
		xSetInt(dPlayerData, xUnitID, 1*trQuestVarGet("P"+p+"Farmer"));
		switch(xGetInt(dPlayerData, xSkin))
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
		if(xGetInt(dPlayerData, xSkin) > 4){
			trUnitChangeProtoUnit("Villager Egyptian");
		}
		trUnitSelectByQV("P"+p+"Farmer");
		if(xGetInt(dPlayerData, xSkin) > 4){
			trSetSelectedScale(0,2,0);
			spyEffect(1*trQuestVarGet("P"+p+"Farmer"), kbGetProtoUnitID(""+SkinProto(xGetInt(dPlayerData, xSkin))), xsVectorSet(dPlayerData,xSpyID,p), vector(2,2,2));
		}
		else{
			trSetSelectedScale(2,2,2);
			trUnitSelectByQV("P"+p+"Farmer");
			trUnitConvert(0);
		}
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
	xsEnableRule("Animations");
	trDelayedRuleActivation("HideSpies");
}

rule HideSpies
highFrequency
inactive
{
	for(p=1; <= cNumberNonGaiaPlayers) {
		xSetPointer(dPlayerData, p);
		if(xGetInt(dPlayerData, xSkin) > 4){
			trUnitSelectByQV("P"+p+"Farmer");
			trUnitChangeProtoUnit("Cinematic Block");
		}
	}
	xsDisableSelf();
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
		xSetPointer(dPlayerData, 1);
		xSetInt(dPlayerData, xSkin, SkinOverride);
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
		xSetPointer(dPlayerData, p);
		if(xGetInt(dPlayerData, xSkin) <= 4){
			xSetInt(dPlayerData, xSkin, 0);
		}
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
	for(b=1; <= cNumberNonGaiaPlayers) {
		xSetPointer(dPlayerData, b);
		if(xGetInt(dPlayerData, xSkin) > 4){
			trUnitSelectClear();
			trUnitSelectByQV("P"+b+"SkinChooser");
			trUnitChangeProtoUnit("Poison SFX");
			ColouredChatToPlayer(b, "1,0.5,0", "Your skin choice has been loaded.");
		}
	}
}

rule SkinChange
inactive
minInterval 1
{
	for(p=1; <= cNumberNonGaiaPlayers) {
		trUnitSelectClear();
		trUnitSelectByQV("P"+p+"SkinChooser");
		xSetPointer(dPlayerData, p);
		for(n=1; <= 4) {
			if(trUnitDistanceToUnit(""+1*trQuestVarGet("Skin"+n+"")) < 3){
				if(xGetInt(dPlayerData, xSkin) != n){
					xSetInt(dPlayerData, xSkin, n);
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
