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
		}
		xsDisableSelf();
		OverlayTextPlayerColor(trCurrentPlayer());
		playSound("cinematics\15_in\gong.wav");
		//ROUND DATA
		switch(1*trQuestVarGet("Round"))
		{
			case 1:
			{
				RoundTime = 120-(QuickStart*100);
				BankCrates = cNumberNonGaiaPlayers/2+1;
			}
			case 2:
			{
				RoundTime = 120;
				BankCrates = cNumberNonGaiaPlayers/2;
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
		for(n=1; <= BankCrates) {
			trQuestVarSetFromRand("Random", 3500, 12000);
			xSetInt(dCrates, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
			xSetInt(dCrates, xUnitID, -1);
			xAddDatabaseBlock(dCrates, true);
		}
		trChatSend(0, ""+xGetDatabaseCount(dCrates));
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

rule CrateProcessing
highFrequency
inactive
{
	ProcessCrates(BankCrates);
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
	xsDisableSelf();
	xsDisableRule("CrateProcessing");
	for(x=xGetDatabaseCount(dCrates); >0) {
		xDatabaseNext(dCrates);
		xFreeDatabaseBlock(dCrates);
	}
	aiPlanDestroy(dCrates);
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
	}
	playSound("cinematics\15_in\gong.wav");
	trUIFadeToColor(0,0,0,1000,600,true);
	xsEnableRule("Scoreboard");
	trChatSend(0, ""+xGetDatabaseCount(dCrates));
	trOverlayTextColour(255, 125, 0);
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
