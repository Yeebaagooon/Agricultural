rule CineChoice
inactive
highFrequency
{
	if (trTime() > cActivationTime + 1) {
		int CineVotes = 0;
		xsDisableSelf();
		trUIFadeToColor(0,0,0,800,100,false);
		trPaintTerrain(0,0,MapSize,MapSize,0,0,true);
		for(p=1; <= cNumberNonGaiaPlayers) {
			xSetPointer(dPlayerData, p);
			CineVotes = CineVotes+xGetInt(dPlayerData, xCineSeen);
		}
		if(QuickStart == 1){
			CineVotes = cNumberNonGaiaPlayers;
		}
		if(CineVotes == cNumberNonGaiaPlayers){
			xsEnableRule("PaintTerrain");
		}
		else{
			trLetterBox(true);
			xsEnableRule("Intro_Cine_01");
			int a = trCurrentPlayer();
			xSetPointer(dPlayerData, a);
			if(xGetInt(dPlayerData, xCineSeen) == 0){
				characterDialog("Yeebaagooon", "Welcome to " + MapName +"!", "icons/special e son of osiris icon 64");
			}
			else{
				characterDialog("Yeebaagooon", "We've got some new players today so I need to go through the cinematic with them.", "icons/special e son of osiris icon 64");
			}
			trQuestVarSet("Yeeb", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Cinematic Block", MapSize/2+1, MapSize/2+1, 180);
			trQuestVarSet("YeebEgg", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Cinematic Block", MapSize/2+1, MapSize/2+1, 40);
			trQuestVarSet("YeebDecor", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Cinematic Block", MapSize/2+1, MapSize/2+1, 0);
			trUnitSelectByQV("Yeeb");
			trUnitChangeProtoUnit("Pharaoh of Osiris XP");
			trUnitSelectByQV("YeebEgg");
			trUnitChangeProtoUnit("Phoenix Egg");
			trUnitSelectByQV("YeebEgg");
			trSetSelectedScale(2,2,2);
			trCameraCut(xsVectorSet(MapSize/2+1,13.823794,MapSize/12-7), vector(0.002290,-0.296856,0.954920), vector(0.000712,0.954922,0.296856), vector(0.999997,0.000000,-0.002398));
			trPaintTerrain(0,0,MapSize*2,MapSize*2,5,4,false);
			int z = MapSize/12;
			for(x=1 ; <= MapSize/6){
				paintShopSquare(x*3-2,z*3-3, "black");
			}
			if(MapSize == 48){
				PaintAtlantisArea(MapSize/6+3,MapSize/6+3,MapSize/6+5,MapSize/6+5,0,73);
			}
			if(MapSize == 60){
				PaintAtlantisArea(MapSize/6+4,MapSize/6+4,MapSize/6+6,MapSize/6+6,0,73);
			}
			if(MapSize == 72){
				PaintAtlantisArea(MapSize/6+5,MapSize/6+5,MapSize/6+7,MapSize/6+7,0,73);
			}
			trUnitSelectByQV("YeebDecor");
			trUnitChangeProtoUnit("Plenty Vault");
			trUnitSelectByQV("YeebDecor");
			trSetSelectedScale(0.5,-0.5,0.5);
		}
	}
}

rule Intro_Cine_01
inactive
highFrequency
{
	if (trTime() > cActivationTime + 3) {
		xsDisableSelf();
		characterDialog("Yeebaagooon", "Task your villager on a farm.", "icons/special e son of osiris icon 64");
		trQuestVarSet("Farmcandytime", trTimeMS()+500);
		xsEnableRule("Intro_Cine_02");
	}
}

rule Intro_Cine_02
inactive
highFrequency
{
	if (trTimeMS() > cActivationTime + 1*trQuestVarGet("Farmcandytime")) {
		trQuestVarModify("Farmcandytime", "+", 500);
		trQuestVarModify("Farmcandynumber", "+", 1);
		int temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Cinematic Block", MapSize/2-16+6*trQuestVarGet("Farmcandynumber"), MapSize/2-6, 0);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Farm");
		if(1*trQuestVarGet("Farmcandynumber") == 2){
			trQuestVarSet("FirstFarm", temp);
		}
		if(1*trQuestVarGet("Farmcandynumber") == 3){
			trQuestVarSet("SecondFarm", temp);
		}
		if(1*trQuestVarGet("Farmcandynumber") > 3){
			xsDisableSelf();
			xsEnableRule("Intro_Cine_03");
			trQuestVarSet("TempBank", temp);
		}
		trPlayerSetDiplomacy(0,1,"Ally");
	}
}

rule Intro_Cine_03
inactive
highFrequency
{
	xsDisableSelf();
	int temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(1, "Cinematic Block", MapSize/2-10, MapSize/2-6, 0);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit("Villager Greek");
	trQuestVarSet("CineVillager", temp);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitDoWorkOnUnit(""+1*trQuestVarGet("FirstFarm"),-1);
	xsEnableRule("Intro_Cine_04");
}

rule Intro_Cine_04
inactive
highFrequency
{
	if (trPlayerUnitCountSpecific(1, "Farm") == 1) {
		xsDisableSelf();
		int temp = trGetNextUnitScenarioNameNumber();
		characterDialog("Yeebaagooon", "This will convert that farm to your ownership.", "icons/special e son of osiris icon 64");
		UnitCreate(1, "Cinematic Block", MapSize/2-4, MapSize/2-6, 90);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Flag");
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitSetAnimationPath("0,1,0,0,0,0");
		xsEnableRule("Intro_Cine_05");
		xsEnableRule("Intro_Cine_07");
	}
}

rule Intro_Cine_05
inactive
highFrequency
{
	if (trTime() > cActivationTime + 1) {
		xsDisableSelf();
		trUnitSelectByQV("CineVillager");
		trUnitDoWorkOnUnit(""+1*trQuestVarGet("SecondFarm"),-1);
		xsEnableRule("Intro_Cine_06");
	}
}

rule Intro_Cine_06
inactive
highFrequency
{
	if (trPlayerUnitCountSpecific(1, "Farm") == 2) {
		xsDisableSelf();
		int temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(1, "Cinematic Block", MapSize/2+2, MapSize/2-6, 90);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Flag");
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitSetAnimationPath("0,1,0,0,0,0");
	}
}

rule Intro_Cine_07
inactive
highFrequency
{
	if (trTime() > cActivationTime + 3) {
		xsDisableSelf();
		characterDialog("Yeebaagooon", "Then move to a wall connector to bank your farms.", "icons/special e son of osiris icon 64");
		trUnitSelectByQV("TempBank");
		trUnitChangeProtoUnit("Wall Connector");
		trUnitSelectByQV("TempBank");
		trUnitSetAnimationPath("3,2,0,0,0,0");
		trUnitSelectByQV("TempBank");
		trUnitHighlight(3, false);
		xsEnableRule("Intro_Cine_08");
	}
}

rule Intro_Cine_08
inactive
highFrequency
{
	if (trTime() > cActivationTime + 2) {
		xsDisableSelf();
		trUnitSelectByQV("CineVillager");
		trUnitMoveToPoint(MapSize/2+8,3,MapSize/2-6,16,false);
		xsEnableRule("Intro_Cine_09");
	}
}

rule Intro_Cine_09
inactive
highFrequency
{
	if (trTime() > cActivationTime + 2) {
		xsDisableSelf();
		characterDialog("Yeebaagooon", "This converts your farms into points.", "icons/special e son of osiris icon 64");
		xsEnableRule("Intro_Cine_11");
	}
}

void Intro_Cine_10(int p = 0){
	xsDisableSelf();
	trUnitSelectByQV("TempBank");
	trUnitChangeProtoUnit("Titan Atlantean");
	trUnitSelectByQV("TempBank");
	trUnitChangeProtoUnit("Farm");
	unitTransform("Titan Gate Dead", "Heavenlight");
	playSound("tributereceived.wav");
	playSound("\cinematics\35_out\grunt wet.mp3");
	trOverlayText("+ 2 points", 3, 605, 30, 1000);
	unitTransform("Flag", "Qilin Heal");
	trUnitSelectByQV("Yeeb");
	trUnitChangeInArea(1, 0, "Farm", "Farm", MapSize*6);
}

rule Intro_Cine_11
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		xsDisableSelf();
		characterDialog("Yeebaagooon", "There are three rounds, and plenty of powerups!", "icons/special e son of osiris icon 64");
		xsEnableRule("Intro_Cine_12");
		unitTransform("Farm", "Rocket");
		unitTransform("Villager Greek", "Hero Death");
		createCameraTrack(3800);
		trCameraCut(xsVectorSet(MapSize/2+1,13.823794,-1), vector(0.002290,-0.296856,0.954920), vector(0.000712,0.954922,0.296856), vector(0.999997,0.000000,-0.002398));
		addCameraTrackWaypoint();
		trCameraCut(xsVectorSet(MapSize/2+1,9.862794,MapSize/2-10), vector(0.002290,-0.296856,0.954920), vector(0.000712,0.954922,0.296856), vector(0.999997,0.000000,-0.002398));
		addCameraTrackWaypoint();
		playCameraTrack();
		trPaintTerrain(0,0,MapSize*2,MapSize*2,5,4,false);
		if(MapSize == 48){
			PaintAtlantisArea(MapSize/6+3,MapSize/6+3,MapSize/6+5,MapSize/6+5,0,73);
		}
		if(MapSize == 60){
			PaintAtlantisArea(MapSize/6+4,MapSize/6+4,MapSize/6+6,MapSize/6+6,0,73);
		}
		if(MapSize == 72){
			PaintAtlantisArea(MapSize/6+5,MapSize/6+5,MapSize/6+7,MapSize/6+7,0,73);
		}
	}
}

rule Intro_Cine_12
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		xsDisableSelf();
		characterDialog("Yeebaagooon", "Oh, and of course you can steal farms from other players.", "icons/special e son of osiris icon 64");
		xsEnableRule("Intro_Cine_13");
	}
}

rule Intro_Cine_13
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		xsDisableSelf();
		trUnitSelectByQV("Yeeb");
		trUnitChangeProtoUnit("Hero Death");
		trUnitSelectByQV("YeebEgg");
		trDamageUnitPercent(100);
		trUnitSelectByQV("YeebDecor");
		trUnitChangeProtoUnit("Ragnorok SFX");
		xsEnableRule("PaintTerrain");
		trLetterBox(false);
		ColouredChat("1,0.5,0", "The cinematic will not play if all players have seen it.");
		trPlayerSetDiplomacy(0,1,"Enemy");
		//data
		for(p=1; <= cNumberNonGaiaPlayers) {
			xSetPointer(dPlayerData, p);
			xSetInt(dPlayerData, xCineSeen, 1);
		}
	}
}


