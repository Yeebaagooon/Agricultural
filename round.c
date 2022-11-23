rule RoundStart
highFrequency
inactive
{
	if (trTime() > cActivationTime + 3) {
		int points = 0;
		trClearCounterDisplay();
		trOverlayText("GO!" , 2.0, 608, 300, 1000);
		for(p=1; <= cNumberNonGaiaPlayers) {
			trUnitSelectClear();
			trUnitSelectByQV("P"+p+"Farmer");
			trUnitConvert(p);
			trPlayerKillAllGodPowers(p);
			points = 1*trQuestVarGet("P"+p+"Points");
			trSetCivilizationNameOverride(p, "Points: " + points);
		}
		xsDisableSelf();
		OverlayTextPlayerColor(trCurrentPlayer());
		trOverlayText(".",0.1,1,1,1);
		playSound("cinematics\15_in\gong.wav");
		//ROUND DATA
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
			}
			case 2:
			//Sign powerup
			{
				RoundTime = 150-(QuickStart*148);
				BankCrates = cNumberNonGaiaPlayers/2+1;
				RelicsAllowed = xsMax(1,cNumberNonGaiaPlayers/3);
				MissilesAllowed = 2;
				ArrowsAllowed = xsMax(1,cNumberNonGaiaPlayers/4);
			}
			case 3:
			//Missiles hit things
			{
				RoundTime = 180-(QuickStart*150);
				BankCrates = xsMax(1,cNumberNonGaiaPlayers/2);
				RelicsAllowed = xsMax(1,cNumberNonGaiaPlayers/3);
				MissilesAllowed = xsMax(1,cNumberNonGaiaPlayers/4);
				ArrowsAllowed =xsMax(1, cNumberNonGaiaPlayers/4);
				trMessageSetText("Missiles will now steal farms when they hit a player!", 6000);
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
		trCounterAddTime("CDRoundTimer", RoundTime, 0, "<color={PlayerColor(2)}>Time remaining", 15);
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

rule EndC01
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		xsDisableSelf();
		trLetterBox(false);
		trUIFadeToColor(0,0,0,1000,200,false);
		xsEnableRule("ProfitChat");
	}
}

rule ProfitChat
inactive
highFrequency
{
	for(p = 1; <= cNumberNonGaiaPlayers){
		trQuestVarSet("P"+p+"Place",1);
	}
	for(p = 1; <= cNumberNonGaiaPlayers){
		for(x = 1; <= cNumberNonGaiaPlayers){
			if(1*trQuestVarGet("P"+p+"Points") < 1*trQuestVarGet("P"+x+"Points")){
				trQuestVarModify("P"+p+"Place", "+", 1);
			}
		}
	}
	trChatSend(0, "<color=1,0.5,0><u>Scores:</u></color>");
	for(x = 1; <= cNumberNonGaiaPlayers){
		for(p = 1; <= cNumberNonGaiaPlayers){
			if(1*trQuestVarGet("P"+p+"Place") == x){
				if(x == 1){
					trChatSend(0, "<color={PlayerColor("+p+")}><icon=(20)(icons/star)> {Playername("+p+")} - "+1*trQuestVarGet("P"+p+"Points")+"");
				}
				else{
					trChatSend(0, "<color={PlayerColor("+p+")}>{Playername("+p+")} - "+1*trQuestVarGet("P"+p+"Points")+"");
				}
			}
		}
	}
	for(p = 1; <= cNumberNonGaiaPlayers){
		if(1*trQuestVarGet("P"+p+"Place") == 1){
			tie1 = tie1 + 1;
		}
		if(1*trQuestVarGet("P"+p+"Place") == 2){
			tie2 = tie2 + 1;
		}
		if(1*trQuestVarGet("P"+p+"Place") == 3){
			tie3 = tie3 + 1;
		}
	}
	if(tie1 > 0){
		debugLog("Tie for first");
	}
	if(tie2 > 0){
		debugLog("Tie for second");
	}
	if(tie3 > 0){
		debugLog("Tie for third");
	}
	if(tie3 < 0){
		debugLog("No third");
	}
	xsDisableSelf();
}
