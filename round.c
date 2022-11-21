rule RoundStart
highFrequency
inactive
{
	if (trTime() > cActivationTime + 3) {
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
			{
				RoundTime = 120-(QuickStart*118);
				BankCrates = cNumberNonGaiaPlayers/2+1;
				RelicsAllowed = cNumberNonGaiaPlayers/3;
				MissilesAllowed = 2;
			}
			case 2:
			{
				RoundTime = 120;
				BankCrates = cNumberNonGaiaPlayers/2;
				RelicsAllowed = cNumberNonGaiaPlayers/3;
				MissilesAllowed = 2;
			}
			case 3:
			{
				RoundTime = 120;
			}
			case 4:
			{
				RoundTime = 120;
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
			trQuestVarSetFromRand("Random", 1000, 6000); //INCREASE
			xAddDatabaseBlock(dRelics, true);
			xSetInt(dRelics, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
			xSetInt(dRelics, xUnitID, -1);
		}
		for(n=1; <= MissilesAllowed) {
			trQuestVarSetFromRand("Random", 1000, 6000); //INCREASE
			xAddDatabaseBlock(dMissileBox, true);
			xSetInt(dMissileBox, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
			xSetInt(dMissileBox, xUnitID, -1);
		}
		xsEnableRule("CrateProcessing");
		xsEnableRule("StopDeletes");
		trCounterAddTime("CDRoundTimer", RoundTime, 0, "<color={PlayerColor(2)}>Time remaining", 15);
	}
}

void ProcessCrates(int count = 1) {
	int temp = 0;
	int TempX = 0;
	int TempZ = 0;
	int ABORT = 0;
	int points = 0;
	int extra = 0;
	for (x=xsMin(count, xGetDatabaseCount(dCrates)); > 0) {
		xDatabaseNext(dCrates);
		if((xGetInt(dCrates, xUnitID) == -1) && (trTimeMS() > xGetInt(dCrates, xTimeIn))){
			//Spawn crate - NEEDS EMERGENCY BREAK IF P0 HAS NO FARMS
			while (xGetInt(dCrates, xUnitID) == -1) {
				trQuestVarSetFromRand("TempX",1,XMax,true);
				trQuestVarSetFromRand("TempZ",1,ZMax,true);
				TempX = 1*trQuestVarGet("TempX");
				TempZ = 1*trQuestVarGet("TempZ");
				temp = 1*trQuestVarGet("FarmX"+TempX+"Z"+TempZ+"");
				trUnitSelectClear();
				if(trCountUnitsInArea(""+temp,0,"Farm",1) == 0){
					trChatSend(0, "Fail at X"+TempX+" Z"+TempZ+"");
					ABORT = ABORT +1;
				}
				else if(trCountUnitsInArea(""+temp,0,"Farm",1) == 1){
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Wall Connector");
					xSetInt(dCrates, xUnitID, temp);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitSetAnimationPath("3,2,0,0,0,0");
					trQuestVarSetFromRand("Random", 10000, 19000);
					xSetInt(dCrates, xTimeOut, trTimeMS()+1*trQuestVarGet("Random"));
				}
				if(ABORT > 10){
					trChatSend(0, "ABORT");
					trQuestVarSetFromRand("Random", 3500, 9000);
					xSetInt(dCrates, xTimeIn, xGetInt(dCrates, xTimeIn)+1*trQuestVarGet("Random"));
					break;
				}
			}
		}
		//Create spawned processing
		if(xGetInt(dCrates, xUnitID) != -1){
			if(trTimeMS() > xGetInt(dCrates, xTimeOut)){
				xUnitSelect(dCrates, xUnitID);
				trUnitChangeProtoUnit("Farm");
				trQuestVarSetFromRand("Random", 8000, 17000);
				xSetInt(dCrates, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
				xSetInt(dCrates, xUnitID, -1);
			}
			for(p=1; <= cNumberNonGaiaPlayers) {
				if(trCountUnitsInArea(""+xGetInt(dCrates, xUnitID),p,"All",4) == 1){
					//Player Bank
					xUnitSelect(dCrates, xUnitID);
					trUnitChangeProtoUnit("Titan Atlantean");
					xUnitSelect(dCrates, xUnitID);
					trUnitChangeProtoUnit("Farm");
					unitTransform("Titan Gate Dead", "Heavenlight");
					extra = trPlayerUnitCountSpecific(p, "Farm");
					trQuestVarSet("P"+p+"Points", 1*trQuestVarGet("P"+p+"Points")+extra);
					xUnitSelect(dCrates, xUnitID);
					trUnitChangeInArea(p, 0, "Farm", "Titan Atlantean", MapSize*6);
					trUnitChangeInArea(0, 0, "Titan Atlantean", "Farm", MapSize*6);
					trUnitChangeInArea(0, 0, "Titan Gate Dead", "Dwarf", MapSize*6);
					trUnitChangeInArea(0, 0, "Dwarf", "Qilin Heal", MapSize*6);
					points = 1*trQuestVarGet("P"+p+"Points");
					trSetCivilizationNameOverride(p, "Points: " + points);
					gadgetRefresh("unitStatPanel");
					xSetInt(dCrates, xUnitID, -1);
					trQuestVarSetFromRand("Random", 5000, 12000);
					xSetInt(dCrates, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
					if(trCurrentPlayer() == p){
						if(extra == 1){
							trOverlayText("+ " + extra + " point", 3, 615, 30, 1000);
						}
						else if(extra >= 10){
							trOverlayText("+ " + extra + " points", 3, 605, 30, 1000);
						}
						else{
							trOverlayText("+ " + extra + " points", 3, 610, 30, 1000);
						}
						playSound("tributereceived.wav");
						playSound("\cinematics\35_out\grunt wet.mp3");
					}
				}
			}
		}
	}
}

void ProcessRelics(int count = 1) {
	int temp = 0;
	int TempX = 0;
	int TempZ = 0;
	int ABORT = 0;
	int points = 0;
	int extra = 0;
	for (x=xsMin(count, xGetDatabaseCount(dRelics)); > 0) {
		xDatabaseNext(dRelics);
		if((xGetInt(dRelics, xUnitID) == -1) && (trTimeMS() > xGetInt(dRelics, xTimeIn))){
			//Spawn crate - NEEDS EMERGENCY BREAK IF P0 HAS NO FARMS
			while (xGetInt(dRelics, xUnitID) == -1) {
				trQuestVarSetFromRand("TempX",1,XMax,true);
				trQuestVarSetFromRand("TempZ",1,ZMax,true);
				TempX = 1*trQuestVarGet("TempX");
				TempZ = 1*trQuestVarGet("TempZ");
				temp = 1*trQuestVarGet("FarmX"+TempX+"Z"+TempZ+"");
				trUnitSelectClear();
				if(trCountUnitsInArea(""+temp,0,"Farm",1) == 0){
					trChatSend(0, "Fail at X"+TempX+" Z"+TempZ+"");
					ABORT = ABORT +1;
				}
				else if(trCountUnitsInArea(""+temp,0,"Farm",1) == 1){
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Titan Atlantean");
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Relic");
					xSetInt(dRelics, xUnitID, temp);
					yFindLatestReverse("TempRelicSFX", "Titan Gate Dead", 0);
					xSetInt(dRelics, xRelicSFX, 1*trQuestVarGet("TempRelicSFX"));
					trUnitSelectByQV("TempRelicSFX");
					trUnitChangeProtoUnit("Spy Eye");
					trUnitSelectByQV("TempRelicSFX");
					trMutateSelected(kbGetProtoUnitID("Tower Mirror"));
					trUnitSelectByQV("TempRelicSFX");
					trSetSelectedScale(0,0.1,0);
					trQuestVarSetFromRand("Random", 10000, 20000);
					xSetInt(dRelics, xTimeOut, trTimeMS()+1*trQuestVarGet("Random"));
				}
				if(ABORT > 10){
					trChatSend(0, "ABORT");
					trQuestVarSetFromRand("Random", 8000, 20000);
					xSetInt(dRelics, xTimeIn, xGetInt(dRelics, xTimeIn)+1*trQuestVarGet("Random"));
					break;
				}
			}
		}
		//Create spawned processing
		if(xGetInt(dRelics, xUnitID) != -1){
			if(trTimeMS() > xGetInt(dRelics, xTimeOut)){
				xUnitSelect(dRelics, xUnitID);
				trUnitChangeProtoUnit("Farm");
				trQuestVarSetFromRand("Random", 10000, 24000);
				xSetInt(dRelics, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
				xSetInt(dRelics, xUnitID, -1);
				xUnitSelect(dRelics, xRelicSFX);
				trUnitChangeProtoUnit("Cinematic Block");
			}
			for(p=1; <= cNumberNonGaiaPlayers) {
				if(trCountUnitsInArea(""+xGetInt(dRelics, xUnitID),p,"All",4) == 1){
					//Player Bank
					xUnitSelect(dRelics, xUnitID);
					trUnitChangeProtoUnit("Farm");
					xUnitSelect(dRelics, xRelicSFX);
					trUnitChangeProtoUnit("Olympus Temple SFX");
					extra = trPlayerUnitCountSpecific(p, "Farm");
					xSetInt(dRelics, xUnitID, -1);
					trQuestVarSetFromRand("Random", 5000, 12000);
					xSetInt(dRelics, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
					if(trCurrentPlayer() == p){
						playSound("tributereceived.wav");
						playSound("\cinematics\35_out\grunt wet.mp3");
					}
				}
			}
		}
	}
}

void ProcessMissiles(int count = 1) {
	int temp = 0;
	int TempX = 0;
	int TempZ = 0;
	int ABORT = 0;
	int points = 0;
	int extra = 0;
	for (x=xsMin(count, xGetDatabaseCount(dMissileBox)); > 0) {
		xDatabaseNext(dMissileBox);
		if((xGetInt(dMissileBox, xUnitID) == -1) && (trTimeMS() > xGetInt(dMissileBox, xTimeIn))){
			trQuestVarSetFromRand("TempX",1,MapSize,true);
			trQuestVarSetFromRand("TempZ",1,MapSize,true);
			TempX = 1*trQuestVarGet("TempX");
			TempZ = 1*trQuestVarGet("TempZ");
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Cinematic Block", TempX, TempZ, 0);
			trUnitSelectClear();
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Titan Atlantean");
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Crate");
			xSetInt(dMissileBox, xUnitID, temp);
			yFindLatestReverse("TempMissileSFX", "Titan Gate Dead", 0);
			xSetInt(dMissileBox, xMissileSFX, 1*trQuestVarGet("TempMissileSFX"));
			trUnitSelectByQV("TempMissileSFX");
			trUnitChangeProtoUnit("Spy Eye");
			trUnitSelectByQV("TempMissileSFX");
			trMutateSelected(kbGetProtoUnitID("Torch"));
			trUnitSelectByQV("TempMissileSFX");
			trSetSelectedScale(0,0.1,0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitSetAnimationPath("0,0,0,0,0,0");
			trQuestVarSetFromRand("Random", 6000, 19000);
			xSetInt(dMissileBox, xTimeOut, trTimeMS()+1*trQuestVarGet("Random"));
		}
		//Create spawned processing
		if(xGetInt(dMissileBox, xUnitID) != -1){
			if(trTimeMS() > xGetInt(dMissileBox, xTimeOut)){
				xUnitSelect(dMissileBox, xUnitID);
				trUnitChangeProtoUnit("Cinematic Block");
				trQuestVarSetFromRand("Random", 10000, 24000);
				xSetInt(dMissileBox, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
				xSetInt(dMissileBox, xUnitID, -1);
				xUnitSelect(dMissileBox, xMissileSFX);
				trUnitChangeProtoUnit("Cinematic Block");
			}
			for(p=1; <= cNumberNonGaiaPlayers) {
				if(trCountUnitsInArea(""+xGetInt(dMissileBox, xUnitID),p,"All",4) == 1){
					//Player Bank
					xUnitSelect(dMissileBox, xUnitID);
					trUnitChangeProtoUnit("Arkantos God Out");
					xUnitSelect(dMissileBox, xMissileSFX);
					trUnitChangeProtoUnit("Lightning Sparks Ground");
					xSetInt(dMissileBox, xUnitID, -1);
					trQuestVarSetFromRand("Random", 5000, 12000);
					xSetInt(dMissileBox, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
					xSetPointer(dPlayerData, p);
					xSetInt(dPlayerData, xMissileCount, xGetInt(dPlayerData, xMissileCount)+1);
					trTechGodPower(p, "Vision", 100);
					if(trCurrentPlayer() == p){
						playSound("lightningstrike3.wav");
					}
				}
			}
		}
	}
}


rule CrateProcessing
highFrequency
inactive
{
	timediff = 0.001 * (trTimeMS() - timelast); // calculate timediff
	timelast = trTimeMS();
	ProcessCrates(BankCrates);
	ProcessRelics(RelicsAllowed);
	ProcessMissiles(MissilesAllowed);
	unitTransform("Vision SFX", "Cinematic Block");
	for (x=xGetDatabaseCount(dMissiles); > 0) {
		DoMissile();
	}
	for(p=1; <= cNumberNonGaiaPlayers) {
		if(trPlayerGetPopulation(p) > 99){
			yFindLatestReverse("Temp", "Vision Revealer", p);
			vector pos = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Farmer"), true);
			xAddDatabaseBlock(dMissiles, true);
			xSetInt(dMissiles, xUnitID, trGetNextUnitScenarioNameNumber());
			xSetInt(dMissiles, xOwner, p);
			xSetVector(dMissiles, xMissilePos, pos);
			xSetVector(dMissiles, xMissilePrev, pos);
			xSetVector(dMissiles, xMissileDir, getUnitVector(pos, kbGetBlockPosition(""+1*trQuestVarGet("Temp"), true), 15.0));
			UnitCreate(0, "Dwarf", MapSize/2-1, MapSize/2-1, 0);
			xUnitSelect(dMissiles, xUnitID);
			trUnitChangeProtoUnit("Spy Eye");
			xUnitSelect(dMissiles, xUnitID);
			trMutateSelected(kbGetProtoUnitID("Outpost"));
			xUnitSelect(dMissiles, xUnitID);
			trSetSelectedScale(0,0,0);
			trUnitSelectByQV("Temp");
			trUnitDestroy();
		}
	}
}

rule StopDeletes
minInterval 1
inactive
{
	for(x=1; <= XMax) {
		for(z=1; <= ZMax) {
			//check
			trUnitSelectClear();
			trUnitSelectByQV("FarmX"+x+"Z"+z+"");
			if (trUnitDead()) {
				//rebuild
				trQuestVarSet("FarmX"+x+"Z"+z+"", trGetNextUnitScenarioNameNumber());
				UnitCreate(0, "Cinematic Block", x*6-4, z*6-4, 0);
				trUnitSelectClear();
				trUnitSelectByQV("FarmX"+x+"Z"+z+"");
				trUnitChangeProtoUnit("Farm");
			}
		}
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
	}
	playSound("cinematics\15_in\gong.wav");
	trUIFadeToColor(0,0,0,1000,600,true);
	xsEnableRule("Scoreboard");
	trOverlayTextColour(255, 125, 0);
	trOverlayText(".",0.1,1,1,1);
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
