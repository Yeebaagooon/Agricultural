void Music(int p =0){
	if(1*trQuestVarGet("CustomContent") == 0){
		switch(1*trQuestVarGet("Music"))
		{
			case 6:
			{
				playSound("music\fight\i wish i could throw shapes.mp3");
			}
			case 1:
			{
				playSound("music\fight\li'l drips.mp3");
			}
			case 2:
			{
				playSound("music\fight\meatier shower.mp3");
			}
			case 3:
			{
				playSound("music\fight\oi, that pops!!!.mp3");
			}
			case 4:
			{
				playSound("music\fight\rot loaf.mp3");
			}
			case 5:
			{
				playSound("music\fight\the fire brigade.mp3");
			}
		}
	}
}

rule RoundStart
highFrequency
inactive
{
	if (trTime() > cActivationTime + 3) {
		int points = 0;
		trChangeTerrainHeight(0,0,MapSize,MapSize,3,false);
		trClearCounterDisplay();
		trOverlayText("GO!" , 2.0, 608, 300, 1000);
		for(p=1; <= cNumberNonGaiaPlayers) {
			xSetPointer(dPlayerData, p);
			if(xGetInt(dPlayerData, xSkin) > 5){
				trUnitSelectClear();
				trUnitSelectByQV("P"+p+"Farmer");
				trUnitChangeProtoUnit("Villager Egyptian");
				trUnitSelectByQV("P"+p+"Farmer");
				trSetSelectedScale(0,2,0);
			}
			trUnitSelectClear();
			trUnitSelectByQV("P"+p+"Farmer");
			trUnitConvert(p);
			trPlayerKillAllGodPowers(p);
			points = 1*trQuestVarGet("P"+p+"Points");
			trSetCivilizationNameOverride(p, "Points: " + points);
			modifyProtounitAbsolute("Villager Greek", p, 1, 6);
			modifyProtounitAbsolute("Villager Egyptian", p, 1, 6);
			modifyProtounitAbsolute("Villager Norse", p, 1, 6);
			modifyProtounitAbsolute("Villager Chinese", p, 1, 6);
			modifyProtounitAbsolute("Villager Atlantean Hero", p, 1, 6);
			modifyProtounitAbsolute("Villager Atlantean", p, 1, 6);
		}
		xsDisableSelf();
		trSetCivAndCulture(0,3,10);
		OverlayTextPlayerColor(trCurrentPlayer());
		trOverlayText(".",0.1,1,1,1);
		playSound("cinematics\15_in\gong.wav");
		//ROUND DATA
		trQuestVarSetFromRand("Music", 1, 6);
		if(1*trQuestVarGet("CustomContent") == 0){
			switch(1*trQuestVarGet("Music"))
			{
				case 1:
				{
					playSoundFire("music\fight\i wish i could throw shapes.mp3", 17);
				}
				case 2:
				{
					playSoundFire("music\fight\li'l drips.mp3", 17);
				}
				case 3:
				{
					playSoundFire("music\fight\meatier shower.mp3", 17);
				}
				case 4:
				{
					playSoundFire("music\fight\oi, that pops!!!.mp3", 17);
				}
				case 5:
				{
					playSoundFire("music\fight\rot loaf.mp3", 17);
				}
				case 6:
				{
					playSoundFire("music\fight\the fire brigade.mp3", 17);
				}
			}
		}
		/*
		if((QuickStart == 1) && (1*trQuestVarGet("Round") < 3)){
			trQuestVarSet("Round", 3);
		}
		*/
		switch(1*trQuestVarGet("Round"))
		{
			case 1:
			//Normal
			{
				RoundTime = 120-(QuickStart*118);
				BankCrates = cNumberNonGaiaPlayers/2+2;
				RelicsAllowed = xsMax(1,cNumberNonGaiaPlayers/3);
				MissilesAllowed = 2;
				ArrowsAllowed = 0;
				playSound("\Yeebaagooon\Agricultural Madness\Round1Music.mp3");
			}
			case 2:
			//Sign powerup
			{
				RoundTime = 150-(QuickStart*140);
				BankCrates = cNumberNonGaiaPlayers/2+1;
				RelicsAllowed = xsMax(1,cNumberNonGaiaPlayers/3);
				MissilesAllowed = 2;
				ArrowsAllowed = xsMax(1,cNumberNonGaiaPlayers/4);
				playSound("\Yeebaagooon\Agricultural Madness\Round2Music.mp3");
			}
			case 3:
			//Missiles hit things
			{
				RoundTime = 180-(QuickStart*160);
				BankCrates = xsMax(1,cNumberNonGaiaPlayers/2);
				RelicsAllowed = xsMax(1,cNumberNonGaiaPlayers/3);
				MissilesAllowed = xsMax(1,cNumberNonGaiaPlayers/4);
				ArrowsAllowed =xsMax(1, cNumberNonGaiaPlayers/4);
				playSound("\Yeebaagooon\Agricultural Madness\Round3Music.mp3");
			}
			case 4:
			//Sudden Death
			{
				RoundTime = 260;
				BankCrates = 0;
				RelicsAllowed = 0;
				MissilesAllowed = 3;
				ArrowsAllowed = 0;
			}
		}
		//ALL DATA
		xResetDatabase(dCrates);
		xResetDatabase(dRelics);
		xResetDatabase(dMissileBox);
		xResetDatabase(dArrows);
		for(n=1; <= BankCrates) {
			trQuestVarSetFromRand("Random", 3500, 12000);
			xAddDatabaseBlock(dCrates, true);
			xSetInt(dCrates, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
			xSetInt(dCrates, xUnitID, -1);
		}
		for(n=1; <= RelicsAllowed) {
			trQuestVarSetFromRand("Random", 3000, 6500);
			xAddDatabaseBlock(dRelics, true);
			xSetInt(dRelics, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
			xSetInt(dRelics, xUnitID, -1);
		}
		for(n=1; <= MissilesAllowed) {
			trQuestVarSetFromRand("Random", 7000, 16000);
			xAddDatabaseBlock(dMissileBox, true);
			xSetInt(dMissileBox, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
			xSetInt(dMissileBox, xUnitID, -1);
		}
		if(ArrowsAllowed != 0){
			for(n=1; <= ArrowsAllowed) {
				trQuestVarSetFromRand("Random", 9000, 26000);
				xAddDatabaseBlock(dArrows, true);
				xSetInt(dArrows, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
				xSetInt(dArrows, xUnitID, -1);
			}
		}
		xsEnableRule("CrateProcessing");
		xsEnableRule("StopDeletes");
		xsEnableRule("ConvertSpies");
		xsEnableRule("BankReminder");
		uiZoomToProto("Villager Greek");
		uiLookAtProto("Villager Greek");
		uiZoomToProto("Villager Norse");
		uiLookAtProto("Villager Norse");
		uiZoomToProto("Villager Chinese");
		uiLookAtProto("Villager Chinese");
		uiZoomToProto("Villager Atlantean");
		uiLookAtProto("Villager Atlantean");
		uiZoomToProto("Villager Egyptian");
		uiLookAtProto("Villager Egyptian");
		if(QuickStart == 0){
			trDelayedRuleActivation("KillCPU");
		}
		if(1*trQuestVarGet("Round") != 4){
			trCounterAddTime("CDRoundTimer", RoundTime, 0, "<color={PlayerColor(2)}>Time remaining", 15);
			xsEnableRule("TimeWarn10");
		}
		else{
			//R4 stuff
			xsEnableRule("R4End");
			trUnitSelectByQV("QVEarth");
			trUnitHighlight(1000, false);
		}
	}
}

rule R4End
minInterval 3
inactive
{
	if(1*trQuestVarGet("SuddenDeaths") == tie1){
		xsDisableSelf();
		for(p=1; <= cNumberNonGaiaPlayers) {
			trUnitSelectByQV("P"+p+"Farmer");
			if(trUnitAlive() == true){
				trQuestVarModify("P"+p+"Points", "+", 1);
				xSetPointer(dPlayerData, p);
				xSetInt(dPlayerData, xSDWins, xGetInt(dPlayerData, xSDWins)+1);
			}
		}
		trUnitSelectClear();
		for(p = 1 ; <= cNumberNonGaiaPlayers){
			trUnitSelectClear();
			trUnitSelectByQV("P"+p+"Farmer");
			trUnitChangeProtoUnit("Hero Death");
			xSetPointer(dPlayerData, p);
			xSetInt(dPlayerData, xMissileCount, 0);
			trPlayerKillAllGodPowers(p);
			trUnitSelectClear();
			xUnitSelect(dPlayerData, xSpyID);
			trUnitChangeProtoUnit("Cinematic Block");
		}
		xsEnableRule("RoundsEnd");
		trUIFadeToColor(0,0,0,1000,600,true);
		trSetLighting("default", 1);
		unitTransform("armor glow small", "Rocket");
		trFadeOutMusic(2);
		trFadeOutAllSounds(2);
		xsSetContextPlayer(0);
		xsDisableSelf();
		xsDisableRule("CrateProcessing");
		for(x=xGetDatabaseCount(dRelics); >0) {
			xDatabaseNext(dRelics);
			xUnitSelect(dRelics, xRelicSFX);
			trUnitChangeProtoUnit("Rocket");
		}
		unitTransform("Tower Mirror", "Rocket");
		unitTransform("Crate", "Rocket");
		unitTransform("Torch", "Rocket");
		unitTransform("Outpost", "Rocket");
		unitTransform("Shrine", "Rocket");
		unitTransform("Vision Revealer", "Rocket");
		unitTransform("Tsunami Range Indicator", "Rocket");
		xResetDatabase(dCrates);
		xResetDatabase(dRelics);
		for (x=xGetDatabaseCount(dDestroy); > 0) {
			xDatabaseNext(dDestroy);
			xUnitSelect(dDestroy, xUnitID);
			trUnitDestroy();
			xFreeDatabaseBlock();
		}
		for(x=1 ; <= MapSize/6){
			for(z=1 ; <= MapSize/6){
				paintShopSquare(x*3-2,z*3-2, "black");
			}
		}
	}
}

rule KillCPU
highFrequency
inactive
{
	for(p=1; <= cNumberNonGaiaPlayers) {
		if((kbIsPlayerHuman(p) == false) || (kbIsPlayerResigned(p) == true)){
			trUnitSelectByQV("P"+p+"Farmer");
			trUnitChangeProtoUnit("Einheriar Boost SFX");
		}
	}
	xsDisableSelf();
}

rule TimeWarn10
highFrequency
inactive
{
	if (trTime() > (cActivationTime + RoundTime - 12)) {
		playSound("attackwarning.wav");
		trChatSend(0, "<color=1,0,0>10 SECONDS REMAINING!</color>");
		xsDisableSelf();
	}
}

rule BankReminder
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		for(p=1; <= cNumberNonGaiaPlayers) {
			if(1*trQuestVarGet("P"+p+"Points") == 0){
				ColouredChatToPlayer(p, "1,0.5,0", "Remember to bank your points by moving to a wall connector!");
				if(trCurrentPlayer() == p){
					playSound("attackwarning.wav");
					trMessageSetText("Remember to bank your points by moving to a wall connector!", 10000);
				}
			}
		}
		xsDisableSelf();
	}
}


void RoundEnd (int p = 0){
	xsSetContextPlayer(0);
	xsDisableSelf();
	xsDisableRule("CrateProcessing");
	for(x=xGetDatabaseCount(dRelics); >0) {
		xDatabaseNext(dRelics);
		xUnitSelect(dRelics, xRelicSFX);
		trUnitChangeProtoUnit("Rocket");
	}
	unitTransform("Tower Mirror", "Rocket");
	unitTransform("Crate", "Rocket");
	unitTransform("Torch", "Rocket");
	unitTransform("Outpost", "Rocket");
	unitTransform("Shrine", "Rocket");
	unitTransform("Vision Revealer", "Rocket");
	unitTransform("Tsunami Range Indicator", "Rocket");
	xResetDatabase(dCrates);
	xResetDatabase(dRelics);
	trFadeOutMusic(0.1);
	trFadeOutAllSounds(0.1);
	for(p=1 ; <= cNumberNonGaiaPlayers){
		UnitCreate(p, "Victory Marker",p*2,p*2,0);
	}
	//xResetDatabase(dMissileBox);
	for(x=1 ; <= MapSize/6){
		for(z=1 ; <= MapSize/6){
			trUnitSelectClear();
			trUnitSelectByQV("FarmX"+x+"Z"+z+"");
			trUnitChangeProtoUnit("Cinematic Block");
		}
	}
	for(p = 1 ; <= cNumberNonGaiaPlayers){
		trUnitSelectClear();
		trUnitSelectByQV("P"+p+"Farmer");
		trUnitChangeProtoUnit("Hero Death");
		xSetPointer(dPlayerData, p);
		xSetInt(dPlayerData, xMissileCount, 0);
		trPlayerKillAllGodPowers(p);
		trUnitSelectClear();
		xUnitSelect(dPlayerData, xSpyID);
		trUnitChangeProtoUnit("Cinematic Block");
	}
	playSound("cinematics\15_in\gong.wav");
	trUIFadeToColor(0,0,0,1000,600,true);
	if(1*trQuestVarGet("Round") < 3){
		xsEnableRule("Scoreboard");
	}
	else{
		xsEnableRule("RoundsEnd");
	}
	trOverlayTextColour(255, 125, 0);
	trOverlayText(".",0.1,1,1,1);
	trClearCounterDisplay();
	trChangeTerrainHeight(0,0,MapSize,MapSize,3,false);
	for (x=xGetDatabaseCount(dFlags); > 0) {
		xDatabaseNext(dFlags);
		xUnitSelect(dFlags, xUnitID);
		trUnitDestroy();
		xSetInt(dFlags, xUnitID, 0);
	}
}

void displayScores(){
	gadgetReal("player status");
	gadgetUnreal("playerstatusdialog-Header");
	gadgetUnreal("CivilizationText");
	gadgetUnreal("GPText");
	gadgetUnreal("DiplomacyText");
	gadgetUnreal("RatingText");
	gadgetUnreal("HandicapText");
	for(p = 1; <= cNumberNonGaiaPlayers){
		gadgetUnreal("Player"+p+"God");
		gadgetUnreal("Player"+p+"GP1");
		gadgetUnreal("Player"+p+"GP2");
		gadgetUnreal("Player"+p+"GP3");
		gadgetUnreal("Player"+p+"GP4");
		gadgetUnreal("Player"+p+"Diplomacy");
	}
	//gadgetUnreal("Player"+a+"Entry");
	//gadgetUnreal("Player"+c+"Entry");
	gadgetUnreal("CancelButton");
	gadgetUnreal("OkButton");
	gadgetUnreal("AcceptButton");
	gadgetUnreal("Ok");
	gadgetUnreal("PlayerStatusDialog-Rollover-Section");
}
void hideScores(){
	gadgetUnreal("player status");
}

rule Scoreboard
inactive
highFrequency
{
	if (trTime() > cActivationTime + 2) {
		xsDisableSelf();
		displayScores();
		xsEnableRule("ScoresOff");
	}
}

rule ScoresOff
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		xsDisableSelf();
		hideScores();
		trUIFadeToColor(0,0,0,1000,200,false);
		xsEnableRule("PaintTerrain");
	}
}

rule RoundsEnd
inactive
highFrequency
{
	if (trTime() > cActivationTime + 2) {
		xsDisableSelf();
		trLetterBox(true);
		int p = trCurrentPlayer();
		xSetPointer(dPlayerData, p);
		if(xGetInt(dPlayerData, xPersonalBest) < 1*trQuestVarGet("P"+p+"Points")){
			xSetInt(dPlayerData, xPersonalBest, 1*trQuestVarGet("P"+p+"Points"));
		}
		characterDialog("Game end! Your total score is " + 1*trQuestVarGet("P"+p+"Points"), "Your personal best is " + xGetInt(dPlayerData, xPersonalBest), "icons/special e son of osiris icon 64");
		xsEnableRule("EndC01");
		unitTransform("Farm", "Rocket");
		unitTransform("Flag", "Rocket");
		saveAllData();
	}
}
