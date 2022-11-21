rule RoundStart
highFrequency
inactive
{
	if (trTime() > cActivationTime + 3) {
		trClearCounterDisplay();
		trOverlayText("GO!" , 2.0, 608, 300, 1000);
		for(p=1; <= cNumberNonGaiaPlayers) {
			trUnitSelectClear();
			trUnitSelectByQV("P"+p+"Farmer");
			trUnitConvert(p);
			trPlayerKillAllGodPowers(p);
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
				RelicsAllowed = cNumberNonGaiaPlayers/3;
				MissilesAllowed = 2;
				ArrowsAllowed = 0;
			}
			case 2:
			//Sign powerup
			{
				RoundTime = 150;
				BankCrates = cNumberNonGaiaPlayers/2+1;
				RelicsAllowed = cNumberNonGaiaPlayers/3;
				MissilesAllowed = 2;
				ArrowsAllowed = cNumberNonGaiaPlayers/4;
			}
			case 3:
			//Missiles hit things
			{
				RoundTime = 180;
				BankCrates = cNumberNonGaiaPlayers/2;
				RelicsAllowed = cNumberNonGaiaPlayers/3;
				MissilesAllowed = 1;
				ArrowsAllowed = cNumberNonGaiaPlayers/4;
			}
		}
		//ALL DATA
		xResetDatabase(dCrates);
		xResetDatabase(dRelics);
		xResetDatabase(dMissileBox);
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
		trUnitChangeProtoUnit("Cinematic Block");
	}
	unitTransform("Tower Mirror", "Cinematic Block");
	unitTransform("Crate", "Cinematic Block");
	unitTransform("Torch", "Cinematic Block");
	unitTransform("Outpost", "Cinematic Block");
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
	xsEnableRule("Scoreboard");
	trOverlayTextColour(255, 125, 0);
	trOverlayText(".",0.1,1,1,1);
	trClearCounterDisplay();
	trChangeTerrainHeight(0,0,MapSize,MapSize,3,false);
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
