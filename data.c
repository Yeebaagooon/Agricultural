int dSavedData = 0;
int xSavedDataSize = 0;
int xSavedDataSlot = 0;
int xSavedDataDB = 0;
int xSavedDataVar = 0;

int dLocalData = 0;
int xLocalDataSize = 0;
int xLocalDataSlot = 0;
int xLocalDataName = 0;

int loadNumHumans = 0;

int SavedDataArray = 0; // an array to temporarily store the slot data in memory
int swordsmanCountArray = 0; // how many swordsmen passes are needed here?
int playerDataArray = 0;

int loadProgress = 0;
int totalLoad = 0;
string NEXT_TRIGGER_NAME = "";

// keep track of the amount of space used in this slot
void recordTotalSize(int slot = 0, int size = 0) {
	if (zGetInt(swordsmanCountArray, slot) == 0) {
		zSetInt(swordsmanCountArray, slot, size);
	} else {
		zSetInt(swordsmanCountArray, slot, size * zGetInt(swordsmanCountArray, slot));
	}
}

void addSavedDataDB(int destDB = 0, int destVar = 0, int slot = 0, int size = 1) {
	xAddDatabaseBlock(dSavedData, true);
	xSetInt(dSavedData, xSavedDataSize, size);
	xSetInt(dSavedData, xSavedDataSlot, slot);
	
	xSetInt(dSavedData, xSavedDataDB, destDB);
	xSetInt(dSavedData, xSavedDataVar, destVar);
	
	recordTotalSize(slot, size);
}

void addLocalDataQV(string qvName = "", int slot = 0, int size = 1) {
	xAddDatabaseBlock(dLocalData, true);
	xSetInt(dLocalData, xLocalDataSize, size);
	xSetInt(dLocalData, xLocalDataSlot, slot);
	
	xSetString(dLocalData, xLocalDataName, qvName);
}

void showLoadProgress() {
	if((100 * loadProgress / totalLoad) >= 0){
		displayz = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		farmicon="world a farm cabbage01";
	}
	if((100 * loadProgress / totalLoad) >= 2){
		displayz = "=~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 4){
		displayz = "==~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 6){
		displayz = "===~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 8){
		displayz = "====~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 10){
		displayz = "=====~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 12){
		displayz = "======~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 14){
		displayz = "=======~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 16){
		displayz = "========~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 18){
		displayz = "=========~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 20){
		displayz = "==========~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 22){
		displayz = "===========~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 24){
		displayz = "============~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		farmicon="world a farm cabbage02";
	}
	if((100 * loadProgress / totalLoad) >= 26){
		displayz = "=============~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 28){
		displayz = "==============~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 30){
		displayz = "===============~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 32){
		displayz = "================~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 34){
		displayz = "=================~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 36){
		displayz = "==================~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 38){
		displayz = "===================~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 40){
		displayz = "====================~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 42){
		displayz = "=====================~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 44){
		displayz = "======================~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 46){
		displayz = "=======================~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 48){
		displayz = "========================~~~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 50){
		displayz = "=========================~~~~~~~~~~~~~~~~~~~~~~~~~";
		farmicon="world a farm cabbage03";
	}
	if((100 * loadProgress / totalLoad) >= 52){
		displayz = "==========================~~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 54){
		displayz = "===========================~~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 56){
		displayz = "============================~~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 58){
		displayz = "=============================~~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 60){
		displayz = "==============================~~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 62){
		displayz = "===============================~~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 64){
		displayz = "================================~~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 66){
		displayz = "=================================~~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 68){
		displayz = "==================================~~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 70){
		displayz = "===================================~~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 72){
		displayz = "====================================~~~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 74){
		displayz = "=====================================~~~~~~~~~~~~~";
		farmicon="world a farm cabbage04";
	}
	if((100 * loadProgress / totalLoad) >= 76){
		displayz = "======================================~~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 78){
		displayz = "=======================================~~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 80){
		displayz = "========================================~~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 82){
		displayz = "=========================================~~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 84){
		displayz = "==========================================~~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 86){
		displayz = "===========================================~~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 88){
		displayz = "============================================~~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 90){
		displayz = "=============================================~~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 92){
		displayz = "==============================================~~~~";
	}
	if((100 * loadProgress / totalLoad) >= 94){
		displayz = "===============================================~~~";
	}
	if((100 * loadProgress / totalLoad) >= 96){
		displayz = "================================================~~";
	}
	if((100 * loadProgress / totalLoad) >= 98){
		displayz = "=================================================~";
	}
	if((100 * loadProgress / totalLoad) >= 100){
		displayz = "==================================================";
	}
	trSoundPlayFN("default","1",-1,"Loading Data:"+ displayz,farmicon);
}

void saveAllData() {
	xsSetContextPlayer(0);
	int currentdata = 0;
	int slot = 0;
	int p = trCurrentPlayer();
	
	// save the data
	for(i=0; < 16) {
		// make all data 0 in preparation for updates
		zSetInt(SavedDataArray, i, 0);
	}
	// read data from the various quest vars in backwards order
	xSetPointer(dSavedData, 1);
	for(i=xGetDatabaseCount(dSavedData); >0) {
		xDatabaseNext(dSavedData, true); // database search is backwards this time
		// read the data in the quest var
		slot = xGetInt(dSavedData, xSavedDataSlot);
		currentdata = xGetInt(xGetInt(dSavedData, xSavedDataDB), xGetInt(dSavedData, xSavedDataVar), p);
		
		// floor and ceiling the data so it fits in the data range
		currentdata = xsMax(0, currentdata);
		currentdata = xsMin(currentdata, xGetInt(dSavedData, xSavedDataSize) - 1);
		
		// shift the slot data over and insert our data
		zSetInt(SavedDataArray, slot, zGetInt(SavedDataArray, slot) * xGetInt(dSavedData, xSavedDataSize) + currentdata);
	}
	
	// Local data
	xSetPointer(dLocalData, 1);
	for(i=xGetDatabaseCount(dLocalData); >0) {
		xDatabaseNext(dLocalData, true); // database search is backwards this time
		// read the data in the quest var
		slot = xGetInt(dLocalData, xLocalDataSlot);
		currentdata = trQuestVarGet(xGetString(dLocalData, xLocalDataName));
		
		// floor and ceiling the data so it fits in the data range
		currentdata = xsMax(0, currentdata);
		currentdata = xsMin(currentdata, xGetInt(dLocalData, xLocalDataSize) - 1);
		
		// shift the slot data over and insert our data
		zSetInt(SavedDataArray, slot, zGetInt(SavedDataArray, slot) * xGetInt(dLocalData, xLocalDataSize) + currentdata);
	}
	
	// save all the data into the slots
	for(i=0; < 16) {
		trSetCurrentScenarioUserData(i, zGetInt(SavedDataArray, i));
	}
}

void loadRawData() {
	xsSetContextPlayer(0);
	for(i=0; < 16) {
		// load all the raw data into the array
		zSetInt(SavedDataArray, i, trGetScenarioUserData(i));
		if (zGetInt(SavedDataArray, i) == -1) {
			zSetInt(SavedDataArray, i, 0);
		}
	}
	
	// Load local data here
	int slot = 0;
	int currentdata = 0;
	int val = 0;
	xSetPointer(dLocalData, 1);
	for(i=xGetDatabaseCount(dLocalData); >0) {
		slot = xGetInt(dLocalData, xLocalDataSlot);
		currentdata = zGetInt(SavedDataArray, slot);
		val = iModulo(xGetInt(dLocalData, xLocalDataSize), currentdata);
		zSetInt(SavedDataArray, slot, currentdata / xGetInt(dLocalData, xLocalDataSize));
		
		trQuestVarSet(xGetString(dLocalData, xLocalDataName), val);
		xDatabaseNext(dLocalData);
	}
}

void loadDataFromArray(int arrNum = 0, int p = 1) {
	int slot = xGetInt(dSavedData, xSavedDataSlot);
	int currentdata = zGetInt(arrNum, slot);
	int val = iModulo(xGetInt(dSavedData, xSavedDataSize), currentdata);
	zSetInt(arrNum, slot, currentdata / xGetInt(dSavedData, xSavedDataSize));
	xSetInt(xGetInt(dSavedData, xSavedDataDB), xGetInt(dSavedData, xSavedDataVar), val, p);
}

// Reads data into the Saved array
void loadAllDataMultiplayer() {
	xsSetContextPlayer(0);
	
	xSetPointer(dSavedData, 1);
	// turn all the data into vars by traversing forwards
	for(i=xGetDatabaseCount(dSavedData); >0) {
		// read the data segment
		for(p=1; < cNumberPlayers) {
			loadDataFromArray(zGetInt(playerDataArray, p), p);
		}
		xDatabaseNext(dSavedData);
	}
}

// Reads data into the Saved array
void loadAllDataSingleplayer() {
	xsSetContextPlayer(0);
	
	xSetPointer(dSavedData, 1);
	// turn all the data into vars by traversing forwards
	for(i=xGetDatabaseCount(dSavedData); >0) {
		// read the data segment
		loadDataFromArray(SavedDataArray);
		xDatabaseNext(dSavedData);
	}
}


/*
README

A slot can hold an integer value up to 1 billion. Make sure you're not using up all this space.
To calculate how much space you are using in a slot, multiply together all the various sizes of
data that are stored in that slot.

In Age of Mythology, we have 16 slots to work with, numbered 0-15.

Make sure that there are no units at the start of the map. If you want to do any
map initialization suff, make sure it is done in or after the NEXT_TRIGGER_NAME trigger.
This is to ensure that the unit names are contiguous and starting from 0, which is
important for the data load algorithm.

Also make sure that the bottom corner of the map is passable terrain at the very start. (It can be changed after data loading is done)

Also, using this will modify the cost of swordsman hero to 0 and also make swordsmen flying units.
Be wary of this side effect. You can modify it back to what you want later.

There are two functions you can use to add data:

////////////////////
// addSavedDataDB //
////////////////////
Use this when you want to save the data in a database containing player info. This data
will be synced with other players at the start of the map.

NOTE: The database must be large enough to have an entry for each player. When data is
loaded, it will be stored at the database <destDB> at the variable <destVar> at the index <p>,
where p is the player. Also, the database must be declared BEFORE this function is ever
called. You can do so by initializing the database in a highFrequency trigger that is
active at the very start before this trigger is run.

addSavedDataDB(<DB name>, <Var name>, <slot number>, <data range>);

Example: addSavedDataDB(dPlayerData, xPlayerHealth, 3, 10);
This will tell the game to keep track of the xPlayerHealth value for each player in the dPlayerData database.
Its value ranges from 0-9 and it is stored in slot 3.

////////////////////
// addLocalDataQV //
////////////////////
Use this when you want to save the data in a quest var but LOCAL. This is important because
this data is NOT transferred to other players whatsoever, and is completely local to the player.

addLocalDataQV(<QV name>, <slot number>, <data range>);

Example: addLocalDataQV("cow", 0, 10);
This will tell the game to keep track of the QV "cow". Its value is limited to the range 0-9 and it is stored in slot 0.



///////////////
// IMPORTANT //
///////////////
DO NOT MIX LOCAL AND SAVE DATA! This is very important! Each slot must contain either local data or data that is transferred
to other players, but never both!
*/


rule data_load_emergency_exit_02
highFrequency
inactive
{
	if (trTime() > cActivationTime + 7) {
		xsDisableSelf();
		trLetterBox(false);
		subModeEnter("Simulation","Editor");
		uiMessageBox("","leaveGame()");
		uiCycleCurrentActivate();
		uiCycleCurrentActivate();
		subModeLeave("Simulation","Editor");
		modeEnter("pregame");
		modeEnter("Simulation");
	}
}

rule data_load_00
active
highFrequency
{
	xsDisableSelf();
	xsEnableRule("setup_data");
	trDelayedRuleActivation("data_load_01");
	
	trLetterBox(true);
	trUIFadeToColor(0,0,0,0,0,true);
	
	/*
	The dSavedData database contains every requested piece of data. This is how
	the data will be automatically loaded for us.
	*/
	dSavedData = xInitDatabase("SavedDataSegments");
	xSavedDataSize = xInitAddInt(dSavedData, "size");
	xSavedDataSlot = xInitAddInt(dSavedData, "slot");
	xSavedDataDB = xInitAddInt(dSavedData, "database");
	xSavedDataVar = xInitAddInt(dSavedData, "variable");
	
	dLocalData = xInitDatabase("LocalDataSegments");
	xLocalDataSize = xInitAddInt(dLocalData, "size");
	xLocalDataSlot = xInitAddInt(dLocalData, "slot");
	xLocalDataName = xInitAddString(dLocalData, "name");
	
	SavedDataArray = zNewArray(mInt, 16, "SavedData"); // data for the Saved player
	
	if (aiIsMultiplayer()) {
		playerDataArray = zNewArray(mInt, cNumberPlayers, "playerData"); // a 3-dimensional array holding player data
		swordsmanCountArray = zNewArray(mInt, 16, "swordsmanCount");
		for(i=0; < 16) {
			zSetInt(swordsmanCountArray, i, 0);
		}
		for(p=1; < cNumberPlayers) {
			zSetInt(playerDataArray, p, zNewArray(mInt, 16, "p"+p+"data"));
			
			trModifyProtounit("Swordsman", p, 55, 4);
			trModifyProtounit("Swordsman", p, 2, 9999999999999999999.0);
			trModifyProtounit("Swordsman", p, 2, -9999999999999999999.0);
			trModifyProtounit("Swordsman", p, 2, 0);
			trModifyProtounit("Swordsman Hero", p, 2, 9999999999999999999.0);
			trModifyProtounit("Swordsman Hero", p, 2, -9999999999999999999.0);
			trModifyProtounit("Swordsman Hero", p, 2, 0);
			trModifyProtounit("Swordsman Hero", p, 6, -100);
			trModifyProtounit("Swordsman Hero", p, 16, 9999999999999999999.0);
			trModifyProtounit("Swordsman Hero", p, 17, 9999999999999999999.0);
			trModifyProtounit("Swordsman Hero", p, 18, 9999999999999999999.0);
			trModifyProtounit("Swordsman Hero", p, 19, 9999999999999999999.0);
			trModifyProtounit("Swordsman Hero", p, 16, -9999999999999999999.0);
			trModifyProtounit("Swordsman Hero", p, 17, -9999999999999999999.0);
			trModifyProtounit("Swordsman Hero", p, 18, -9999999999999999999.0);
			trModifyProtounit("Swordsman Hero", p, 19, -9999999999999999999.0);
			trArmyDispatch(""+p+",0","Swordsman", 32, 1 + 2 * p,0,1,0,true);
			
			if (kbIsPlayerHuman(p)) {
				loadNumHumans = 1 + loadNumHumans;
			}
		}
		
		for(p=1; < cNumberPlayers) {
			trArmyDispatch(""+p+",0","Victory Marker", 1, 1, 0, 1, 0, true);
		}
	}
}

int currentSwordsmanSlot = 0;
int currentSwordsmanMultiplier = 1;
int currentSwordsmanData = 0;

rule data_load_01
inactive
highFrequency
{
	xsDisableSelf();
	loadRawData();
	if (aiIsMultiplayer()) {
		xsEnableRule("data_load_02_send_data");
		xsEnableRule("data_load_03_receive_data");
		for(i=0; < 16) {
			// how many swordsmen are needed to transfer the data?
			int swordsmen = 0;
			for(j=0; < 6) {
				if (zGetInt(swordsmanCountArray, i) > 0) {
					zSetInt(swordsmanCountArray, i, zGetInt(swordsmanCountArray, i) / 32);
					swordsmen = swordsmen + 1;
				} else {
					break;
				}
			}
			zSetInt(swordsmanCountArray, i, swordsmen);
			totalLoad = totalLoad + swordsmen;
			
			for(p=0; < cNumberPlayers) {
				zSetInt(zGetInt(playerDataArray, p), i, 0);
			}
		}
	} else {
		loadAllDataSingleplayer();
		xsEnableRule(NEXT_TRIGGER_NAME);
	}
}



rule data_load_02_send_data
inactive
highFrequency
{
	for(i=currentSwordsmanSlot; < 16) {
		if (zGetInt(swordsmanCountArray, i) > 0) {
			zSetInt(swordsmanCountArray, i, zGetInt(swordsmanCountArray, i) - 1);
			currentSwordsmanData = iModulo(32, zGetInt(SavedDataArray, i));
			zSetInt(SavedDataArray, i, zGetInt(SavedDataArray, i) / 32);
			
			currentSwordsmanSlot = i;
			break;
		} else {
			currentSwordsmanMultiplier = 1;
		}
	}
	
	trLetterBox(false);
	trBlockAllSounds(true);
	trUnitSelectClear();
	trUnitSelectByID(currentSwordsmanData + 32 * (trCurrentPlayer() - 1));
	for(i=32; >0) {
		if (trUnitIsSelected() == false) {
			uiFindType("Swordsman");
		} else {
			break;
		}
	}
	uiTransformSelectedUnit("Swordsman Hero");
	trForceNonCinematicModels(true);
	
	trLetterBox(true);
	
	showLoadProgress();
	xsDisableSelf();
}

rule data_load_03_receive_data
inactive
highFrequency
{
	int swordsmen = 0;
	int currentdata = 0;
	for(p=1; < cNumberPlayers) {
		swordsmen = swordsmen + trPlayerUnitCountSpecific(p, "Swordsman Hero");
	}
	if (swordsmen == loadNumHumans) {
		for(p=1; < cNumberPlayers) {
			swordsmen = 32 * (p - 1);
			for(x=0; < 32) {
				if (kbGetUnitBaseTypeID(x + swordsmen) == kbGetProtoUnitID("Swordsman Hero")) {
					/* read the data */
					currentdata = zGetInt(zGetInt(playerDataArray, p), currentSwordsmanSlot) + currentSwordsmanMultiplier * x;
					
					zSetInt(zGetInt(playerDataArray, p), currentSwordsmanSlot, currentdata);
					
					trUnitSelectClear();
					trUnitSelectByID(x + swordsmen);
					trMutateSelected(kbGetProtoUnitID("Swordsman"));
					break;
				}
			}
		}
		
		loadProgress = loadProgress + 1;
		currentSwordsmanMultiplier = currentSwordsmanMultiplier * 32;
		if (loadProgress == totalLoad) {
			xsEnableRule("data_load_04_parse_data");
			xsDisableSelf();
		} else {
			xsEnableRule("data_load_02_send_data");
		}
		showLoadProgress();
	}
}

rule data_load_04_parse_data
inactive
highFrequency
{
	xsDisableSelf();
	int slot = 0;
	int currentdata = 0;
	
	for(i=0; < 32 * (cNumberPlayers - 1)) {
		trUnitSelectClear();
		trUnitSelectByID(i);
		trUnitDestroy();
	}
	
	loadAllDataMultiplayer();
	
	trSoundPlayFN("favordump.wav","1",-1,"","");
	
	xsEnableRule(NEXT_TRIGGER_NAME);
}
