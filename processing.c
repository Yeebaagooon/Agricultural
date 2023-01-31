void ProcessFlags(int count = 1) {
	xsSetContextPlayer(0);
	int owner = 0;
	for (x=xsMin(count, xGetDatabaseCount(dFlags)); > 0) {
		xDatabaseNext(dFlags);
		owner = kbUnitGetOwner(kbGetBlockID(""+1*trQuestVarGet("FarmX"+xGetInt(dFlags,xFlagX)+"Z"+xGetInt(dFlags,xFlagZ)+"")));
		if(owner != xGetInt(dFlags, xFlagOwner)){
			if(xGetInt(dFlags, xUnitID) != 0){
				xUnitSelect(dFlags, xUnitID);
				trUnitDestroy();
				//break;
			}
			xSetInt(dFlags, xFlagOwner, owner);
		}
		if(owner != 0){
			xSetInt(dFlags, xFlagOwner, owner);
			if(kbGetBlockID(""+xGetInt(dFlags, xUnitID)) < 0){
				xSetInt(dFlags, xUnitID, 1*trGetNextUnitScenarioNameNumber());
				UnitCreate(owner, "Dwarf", 1*xGetInt(dFlags,xFlagX)*6-3, 1*xGetInt(dFlags,xFlagZ)*6-3, 0);
				xUnitSelect(dFlags, xUnitID);
				trUnitChangeProtoUnit("Spy Eye");
				xUnitSelect(dFlags, xUnitID);
				trMutateSelected(kbGetProtoUnitID("Flag"));
				xUnitSelect(dFlags, xUnitID);
				trUnitSetAnimationPath("0,1,0,0,0,0");
				xSetInt(dFlags, xFlagOwner, owner);
			}
		}
	}
}

//if (owner != old owner) { delete flag }
//if (owner != 0 and flag is dead) { spawn a new flag)



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
					//trChatSend(0, "Fail at X"+TempX+" Z"+TempZ+"");
					ABORT = ABORT +1;
				}
				else if(trCountUnitsInArea(""+temp,0,"Farm",1) == 1){
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Wall Connector");
					xSetInt(dCrates, xUnitID, temp);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitSetAnimationPath("3,2,0,0,0,0");
					trQuestVarSetFromRand("Random", 15000, 25000);
					xSetInt(dCrates, xTimeOut, trTimeMS()+1*trQuestVarGet("Random"));
				}
				if(ABORT > 10){
					//trChatSend(0, "ABORT");
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
					xSetPointer(dPlayerData, p);
					if(xGetInt(dPlayerData, xMaxBank) < extra){
						xSetInt(dPlayerData, xMaxBank, extra);
					}
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

void ProcessArrows(int count = 1) {
	int temp = 0;
	int TempX = 0;
	int TempZ = 0;
	int ABORT = 0;
	int points = 0;
	int extra = 0;
	for (x=xsMin(count, xGetDatabaseCount(dArrows)); > 0) {
		xDatabaseNext(dArrows);
		if((xGetInt(dArrows, xUnitID) == -1) && (trTimeMS() > xGetInt(dArrows, xTimeIn))){
			//Spawn Arrow - NEEDS EMERGENCY BREAK IF P0 HAS NO FARMS
			while (xGetInt(dArrows, xUnitID) == -1) {
				trQuestVarSetFromRand("TempX",1,XMax,true);
				trQuestVarSetFromRand("TempZ",1,ZMax,true);
				TempX = 1*trQuestVarGet("TempX");
				TempZ = 1*trQuestVarGet("TempZ");
				temp = 1*trQuestVarGet("FarmX"+TempX+"Z"+TempZ+"");
				trUnitSelectClear();
				if(trCountUnitsInArea(""+temp,0,"Farm",1) == 0){
					//trChatSend(0, "Fail at X"+TempX+" Z"+TempZ+"");
					ABORT = ABORT +1;
				}
				else if(trCountUnitsInArea(""+temp,0,"Farm",1) == 1){
					trQuestVarSetFromRand("Heading", 1,4);
					xSetInt(dArrows, xDirection, 1*trQuestVarGet("Heading"));
					if(1*trQuestVarGet("Heading") == 3){
						xSetVector(dArrows, xVectorDir, vector(1,0,0));
					}
					if(1*trQuestVarGet("Heading") == 2){
						xSetVector(dArrows, xVectorDir, vector(0,0,-1));
					}
					if(1*trQuestVarGet("Heading") == 1){
						xSetVector(dArrows, xVectorDir, vector(-1,0,0));
					}
					if(1*trQuestVarGet("Heading") == 4){
						xSetVector(dArrows, xVectorDir, vector(0,0,1));
					}
					//4 is down, 1 is RIGHT, 2 is up, 3 is LEFT
					//it was 3 but really 1 then went 4 then back to 1
					xSetInt(dArrows, xPosX, TempX);
					xSetInt(dArrows, xPosZ, TempZ);
					xSetInt(dArrows, xArrowSFX, trGetNextUnitScenarioNameNumber());
					UnitCreate(0, "Cinematic Block", TempX*6-3, TempZ*6-3, 0);
					xSetInt(dArrows, xArrowBuilding, trGetNextUnitScenarioNameNumber());
					UnitCreate(0, "Cinematic Block", TempX*6-3, TempZ*6-3, 90*xGetInt(dArrows, xDirection));
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Cinematic Block");
					trUnitSelectClear();
					xUnitSelect(dArrows, xArrowBuilding);
					trUnitChangeProtoUnit("Spy Eye");
					xUnitSelect(dArrows, xArrowBuilding);
					trMutateSelected(kbGetProtoUnitID("Shrine"));
					xUnitSelect(dArrows, xArrowBuilding);
					trSetSelectedScale(0.3,0.3,0.3);
					xUnitSelect(dArrows, xArrowBuilding);
					trUnitSetAnimationPath("1,0,0,0,0,0");
					xSetInt(dArrows, xUnitID, temp);
					xUnitSelect(dArrows, xArrowSFX);
					trUnitChangeProtoUnit("Spy Eye");
					xUnitSelect(dArrows, xArrowSFX);
					trMutateSelected(kbGetProtoUnitID("Tsunami Range Indicator"));
					xUnitSelect(dArrows, xArrowSFX);
					trSetUnitOrientation(xGetVector(dArrows, xVectorDir), vector(0,1,0));
					trQuestVarSetFromRand("Random", 19000, 26000);
					xSetInt(dArrows, xTimeOut, trTimeMS()+1*trQuestVarGet("Random"));
					xSetInt(dArrows, xTimeIn, trTimeMS()+2500);
					if (iModulo(2, trTime()) == 0) { //if is divisble by 2
						xSetBool(dArrows, xArrowClock, true);
					}
					else{
						xSetBool(dArrows, xArrowClock, false);
					}
				}
				if(ABORT > 10){
					//trChatSend(0, "ABORT");
					trQuestVarSetFromRand("Random", 3500, 9000);
					xSetInt(dArrows, xTimeIn, xGetInt(dArrows, xTimeIn)+1*trQuestVarGet("Random"));
					break;
				}
			}
		}
		//Create spawned processing
		if(xGetInt(dArrows, xUnitID) != -1){
			if(trTimeMS() > xGetInt(dArrows, xTimeIn)){
				//rotate
				xSetInt(dArrows, xTimeIn, trTimeMS()+2500);
				if(xGetBool(dArrows, xArrowClock) == true){
					xSetInt(dArrows, xDirection, xGetInt(dArrows, xDirection)+1);
					xSetVector(dArrows, xVectorDir, rotationMatrix(xGetVector(dArrows, xVectorDir), 0, 1));
				}
				else{
					xSetInt(dArrows, xDirection, xGetInt(dArrows, xDirection)-1);
					xSetVector(dArrows, xVectorDir, rotationMatrix(xGetVector(dArrows, xVectorDir), 0, -1));
				}
				if(xGetInt(dArrows, xDirection) == 5){
					xSetInt(dArrows, xDirection, 1);
				}
				if(xGetInt(dArrows, xDirection) == 0){
					xSetInt(dArrows, xDirection, 4);
				}
				xUnitSelect(dArrows, xArrowSFX);
				trSetUnitOrientation(xGetVector(dArrows, xVectorDir), vector(0,1,0));
			}
			if(trTimeMS() > xGetInt(dArrows, xTimeOut)){
				xUnitSelect(dArrows, xUnitID);
				trUnitChangeProtoUnit("Farm");
				xUnitSelect(dArrows, xArrowSFX);
				trUnitDestroy();
				xUnitSelect(dArrows, xArrowBuilding);
				trUnitDestroy();
				trQuestVarSetFromRand("Random", 8000, 17000);
				xSetInt(dArrows, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
				xSetInt(dArrows, xUnitID, -1);
			}
			for(p=1; <= cNumberNonGaiaPlayers) {
				if(trCountUnitsInArea(""+xGetInt(dArrows, xUnitID),p,"All",4) == 1){
					//Player Bank
					xUnitSelect(dArrows, xUnitID);
					trUnitChangeProtoUnit("Farm");
					xUnitSelect(dArrows, xUnitID);
					trUnitConvert(p);
					xUnitSelect(dArrows, xArrowSFX);
					trUnitDestroy();
					xUnitSelect(dArrows, xArrowBuilding);
					trUnitDestroy();
					//4 is down, 1 is RIGHT, 2 is up, 3 is LEFT
					if(xGetInt(dArrows, xDirection) == 3){
						for(n = 0 ; < xGetInt(dArrows, xPosX)){
							trUnitSelectByQV("FarmX"+n+"Z"+xGetInt(dArrows, xPosZ)+"");
							trUnitConvert(p);
							trUnitSelectByQV("FarmX"+n+"Z"+xGetInt(dArrows, xPosZ)+"");
							trUnitHighlight(0.5, false);
						}
					}
					if(xGetInt(dArrows, xDirection) == 1){
						for(n = ZMax ; > xGetInt(dArrows, xPosX)){
							trUnitSelectByQV("FarmX"+n+"Z"+xGetInt(dArrows, xPosZ)+"");
							trUnitConvert(p);
							trUnitSelectByQV("FarmX"+n+"Z"+xGetInt(dArrows, xPosZ)+"");
							trUnitHighlight(0.5, false);
						}
					}
					if(xGetInt(dArrows, xDirection) == 4){
						for(n = 0 ; < xGetInt(dArrows, xPosZ)){
							trUnitSelectByQV("FarmX"+xGetInt(dArrows, xPosX)+"Z"+n+"");
							trUnitConvert(p);
							trUnitSelectByQV("FarmX"+xGetInt(dArrows, xPosX)+"Z"+n+"");
							trUnitHighlight(0.5, false);
						}
					}
					if(xGetInt(dArrows, xDirection) == 2){
						for(n = XMax ; > xGetInt(dArrows, xPosZ)){
							trUnitSelectByQV("FarmX"+xGetInt(dArrows, xPosX)+"Z"+n+"");
							trUnitConvert(p);
							trUnitSelectByQV("FarmX"+xGetInt(dArrows, xPosX)+"Z"+n+"");
							trUnitHighlight(0.5, false);
						}
					}
					xUnitSelect(dArrows, xUnitID);
					trUnitChangeInArea(p,0,"Wall Connector", "Wall Connector", MapSize*8);
					//trUnitSetAnimationPath("3,2,0,0,0,0");
					xSetInt(dArrows, xUnitID, -1);
					trQuestVarSetFromRand("Random", 5000, 12000);
					xSetInt(dArrows, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
					if(trCurrentPlayer() == p){
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
	string relictext = "Error";
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
					//trChatSend(0, "Fail at X"+TempX+" Z"+TempZ+"");
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
					//trChatSend(0, "ABORT");
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
			trQuestVarSet("RelicEffect", 0);
			for(p=1; <= cNumberNonGaiaPlayers) {
				if(trCountUnitsInArea(""+xGetInt(dRelics, xUnitID),p,"Unit",4) == 1){
					//Player Bank
					xSetPointer(dPlayerData, p);
					xUnitSelect(dRelics, xUnitID);
					trUnitChangeProtoUnit("Farm");
					xUnitSelect(dRelics, xRelicSFX);
					trUnitChangeProtoUnit("Olympus Temple SFX");
					extra = trPlayerUnitCountSpecific(p, "Farm");
					trQuestVarSetFromRand("Random", 12000, 23000);
					xSetInt(dRelics, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
					//RELIC EFFECT HERE
					trQuestVarSetFromRand("RelicEffect", 1, 8);
					switch(1*trQuestVarGet("RelicEffect"))
					{
						case 1:
						{
							BankCrates = BankCrates+1;
							relictext = "Extra bank crate added to this round";
							trQuestVarSetFromRand("Random", 3500, 5000);
							xAddDatabaseBlock(dCrates, true);
							xSetInt(dCrates, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
							xSetInt(dCrates, xUnitID, -1);
						}
						case 2:
						{
							MissilesAllowed = MissilesAllowed+1;
							relictext = "Extra missile crate added to this round";
							trQuestVarSetFromRand("Random", 2000, 7000);
							xAddDatabaseBlock(dMissileBox, true);
							xSetInt(dMissileBox, xTimeIn, trTimeMS()+1*trQuestVarGet("Random"));
							xSetInt(dMissileBox, xUnitID, -1);
						}
						case 3:
						//Double bank current
						{
							extra = xsMax(trPlayerUnitCountSpecific(p, "Farm")*2, trPlayerUnitCountSpecific(p, "Farm")+4);
							trQuestVarSet("P"+p+"Points", 1*trQuestVarGet("P"+p+"Points")+extra);
							points = 1*trQuestVarGet("P"+p+"Points");
							trSetCivilizationNameOverride(p, "Points: " + points);
							gadgetRefresh("unitStatPanel");
							relictext = "+ " + extra + " points!";
							trUnitSelectByQV("P"+p+"Farmer");
							trUnitChangeInArea(p, 0, "Farm", "Titan Atlantean", MapSize*6);
							trUnitChangeInArea(0, 0, "Titan Atlantean", "Farm", MapSize*6);
							trUnitChangeInArea(0, 0, "Titan Gate Dead", "Dwarf", MapSize*6);
							trUnitChangeInArea(0, 0, "Dwarf", "Poison SFX", MapSize*6);
							if(xGetInt(dPlayerData, xMaxBank) < extra){
								xSetInt(dPlayerData, xMaxBank, extra);
							}
						}
						case 4:
						//bank current but keep
						{
							extra = xsMax(3,trPlayerUnitCountSpecific(p, "Farm"));
							trQuestVarSet("P"+p+"Points", 1*trQuestVarGet("P"+p+"Points")+extra);
							points = 1*trQuestVarGet("P"+p+"Points");
							trSetCivilizationNameOverride(p, "Points: " + points);
							gadgetRefresh("unitStatPanel");
							relictext = "+ " + extra + " points!";
							if(xGetInt(dPlayerData, xMaxBank) < extra){
								xSetInt(dPlayerData, xMaxBank, extra);
							}
						}
						case 5:
						//+5 points
						{
							extra = 5;
							trQuestVarSet("P"+p+"Points", 1*trQuestVarGet("P"+p+"Points")+extra);
							points = 1*trQuestVarGet("P"+p+"Points");
							trSetCivilizationNameOverride(p, "Points: " + points);
							gadgetRefresh("unitStatPanel");
							relictext = "+ " + extra + " points!";
							if(xGetInt(dPlayerData, xMaxBank) < extra){
								xSetInt(dPlayerData, xMaxBank, extra);
							}
						}
						case 6:
						//convert nearby
						{
							xUnitSelect(dRelics, xUnitID);
							for(n=0; <= cNumberNonGaiaPlayers) {
								trUnitChangeInArea(n, p, "Farm", "Farm", 9);
							}
							trUnitSelectClear();
							relictext = "Nearby farms converted";
						}
						case 7:
						//+2 speed
						{
							trModifyProtounit("Villager Greek", p, 1, 2);
							trModifyProtounit("Villager Egyptian", p, 1, 2);
							trModifyProtounit("Villager Norse", p, 1, 2);
							trModifyProtounit("Villager Chinese", p, 1, 2);
							trModifyProtounit("Villager Atlantean Hero", p, 1, 2);
							trModifyProtounit("Villager Atlantean", p, 1, 2);
							relictext = "+2 speed";
						}
						case 8:
						//+2 missiles
						{
							trTechGodPower(p, "Vision", 2);
							relictext = "+2 missiles granted";
						}
					}
					xSetInt(dRelics, xUnitID, -1);
					if(trCurrentPlayer() == p){
						playSound("tributereceived.wav");
						playSound("\cinematics\35_out\grunt wet.mp3");
						uiMessageBox(relictext);
						if(trGetGPData(p,1,0) != 0){
							trClearCounterDisplay();
							trSetCounterDisplay("Missile count: " + trGetGPData(p,1,0));
						}
					}
				}
			}
			trQuestVarSet("RelicEffect", 0);
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
			trQuestVarSetFromRand("Random", 10000, 19000);
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
				if(trCountUnitsInArea(""+xGetInt(dMissileBox, xUnitID),p,"Unit",4) == 1){
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
					trTechGodPower(p, "Vision", 1);
					trQuestVarModify("P"+p+"MissileMsg", "+", 1);
					if(trCurrentPlayer() == p){
						playSound("lightningstrike3.wav");
						trClearCounterDisplay();
						trSetCounterDisplay("Missile count: " + trGetGPData(p,1,0));
						if((1*trQuestVarGet("P"+p+"MissileMsg") == 1) && (xGetInt(dPlayerData, xWins) == 0)){
							trMessageSetText("To use a missile press 'Q' and it will fire to your cursor.", 8000);
						}
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
	if(1*trQuestVarGet("Round") != 4){
		ProcessCrates(BankCrates);
		ProcessRelics(RelicsAllowed);
		ProcessFlags(XMax*ZMax);
	}
	if(ArrowsAllowed != 0){
		ProcessArrows(ArrowsAllowed);
	}
	ProcessMissiles(MissilesAllowed);
	unitTransform("Vision SFX", "Cinematic Block");
	for (x=xGetDatabaseCount(dMissiles); > 0) {
		DoMissile();
	}
	for(p=1; <= cNumberNonGaiaPlayers) {
		trPlayerGrantResources(p, "Food", -1000);
		trPlayerGrantResources(p, "Wood", -1000);
		trPlayerGrantResources(p, "Gold", -1000);
		trPlayerGrantResources(p, "Favor", -1000);
		trPlayerGrantResources(p, "Food", 1*trPlayerUnitCountSpecific(p, "Farm"));
		if(trPlayerGetPopulation(p) > 99){
			playSound("skypassageout.wav");
			yFindLatest("Temp", "Vision Revealer", p);
			vector pos = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Farmer"), true);
			xAddDatabaseBlock(dMissiles, true);
			//unitTransform("Vision Revealer", "Rocket");
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
			if(trCurrentPlayer() == p){
				trClearCounterDisplay();
				trSetCounterDisplay("Missile count: " + trGetGPData(p,1,0));
			}
		}
		if(trPlayerGetPopulation(p) > 150){
			debugLog("Missile error");
			unitTransform("Vision Revealer", "Rocket");
		}
		if(playerIsPlaying(p) == false){
			//resign stuff
			trUnitSelectByQV("P"+p+"Farmer");
			trUnitChangeProtoUnit("Einheriar Boost SFX");
		}
	}
}

rule StopDeletes
minInterval 1
inactive
{
	if(1*trQuestVarGet("Round") != 4){
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
}
