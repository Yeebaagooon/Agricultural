rule EventSetHandler
active
highFrequency
//THESE ONLY WORK IF FIRES FUNCTION, SO USE VOID!
{
	//for(p = 1; <= cNumberNonGaiaPlayers){
	//	trEventSetHandler(p, "UngarrisonDrill");
	//trEventSetHandler(13+p, "SellMinerals");
	//}
	trEventSetHandler(13, "CustomContent");
	trEventSetHandler(14, "SkinTimeEnd");
	trEventSetHandler(15, "RoundEnd");
	trEventSetHandler(16, "Intro_Cine_10");
	trEventSetHandler(17, "MusicGo");
	trEventSetHandler(18, "GoToMainMenu");
	trEventSetHandler(19, "SPHelp");
	for(x = 0; <= 48){
		trEventSetHandler(20+x, "ChooseASkin");
	}
	xsDisableSelf();
}

rule Initialise
active
highFrequency
runImmediately
{
	characterDialog("Waiting for everyone to connect.", " ", "icons\special e son of osiris icon 64");
	trUIFadeToColor(0, 0, 0, 0, 10000, false);
	trFadeOutAllSounds(0.1);
	trFadeOutMusic(0.1);
	xsDisableRule("BasicVC1");
	xsDisableRule("BasicVC2");
	if(QuickStart == 0){
	}
	trBlockAllSounds(true);
	trSetFogAndBlackmap(false, false);
	xsDisableSelf();
}

rule START
active
highFrequency
{
	trPlayerKillAllGodPowers(0);
	for(p = 1; <= cNumberNonGaiaPlayers){
		trSetCivAndCulture(p, 3, 1);
		trPlayerGrantResources(p, "Food", -10000.0);
		trPlayerGrantResources(p, "Wood", -10000.0);
		trPlayerGrantResources(p, "Gold", -10000.0);
		trPlayerGrantResources(p, "Favor", -10000.0);
		trPlayerKillAllGodPowers(p);
	}
	xsDisableRule("BasicVC1");
	xsDisableRule("BasicVC2");
	//start fade to black
	//trUIFadeToColor(1,0,0,0,0,true);
	/*
	trShowImageDialog("world a farm cabbage04", MapName + " by Yeebaagooon");
	gadgetUnreal("ShowImageBox-BordersTop");
	gadgetUnreal("ShowImageBox-BordersBottom");
	gadgetUnreal("ShowImageBox-BordersLeft");
	gadgetUnreal("ShowImageBox-BordersRight");
	gadgetUnreal("ShowImageBox-BordersLeftTop");
	gadgetUnreal("ShowImageBox-BordersLeftBottom");
	gadgetUnreal("ShowImageBox-BordersRightBottom");
	gadgetUnreal("ShowImageBox-BordersRightTop");
	gadgetUnreal("ShowImageBox-CloseButton");
	pause(0);
	*/
	characterDialog("Initialising map", " ", "icons\special e son of osiris icon 64");
	xsEnableRule("setup_data");
	xsDisableSelf();
	//HOTKEYS
	map("q", "game", "uiSetSpecialPower(220) uiSpecialPowerAtPointer");
	map("space", "game", "uiSetSpecialPower(220) uiSpecialPowerAtPointer");
	if(cNumberNonGaiaPlayers <= 5){
		MapSize = 48;
	}
	else if(cNumberNonGaiaPlayers <= 10){
		MapSize = 60;
	}
	else{
		MapSize = 72;
	}
	if(cNumberNonGaiaPlayers == 1){
		MapSize = 202;
	}
	MapCentre = xsVectorSet(MapSize/2-1,0,MapSize/2-1);
}

rule setup_data
inactive
highFrequency
{
	/*
	trQuestVarSetFromRand("Music", 1, 11);
	switch(1*trQuestVarGet("Music"))
	{
		case 1:
		{
			playSound("music\quiet\(fine layers of) slaysenflite (mellow mix).mp3");
		}
		case 2:
		{
			playSound("music\quiet\adult swim (mellow mix).mp3");
		}
		case 3:
		{
			playSound("music\quiet\behold the great science fi (mellow mix).mp3");
		}
		case 4:
		{
			playSound("music\quiet\chocolate outline (mellow mix).mp3");
		}
		case 5:
		{
			playSound("music\quiet\eat your potatoes (mellow mix).mp3");
		}
		case 6:
		{
			playSound("music\quiet\flavor cats (in the comfort zone) (mellow mix).mp3");
		}
		case 7:
		{
			playSound("music\quiet\hoping for real betterness (mellow mix).mp3");
		}
		case 8:
		{
			playSound("music\quiet\in a pile of its own good (mellow mix).mp3");
		}
		case 9:
		{
			playSound("music\quiet\never mind the slacks and bashers (mellow mix).mp3");
		}
		case 10:
		{
			playSound("music\quiet\suture self (mellow mix).mp3");
		}
		case 11:
		{
			playSound("music\quiet\the ballad of ace lebaron (mellow mix).mp3");
		}
	}
	*/
	NEXT_TRIGGER_NAME = "load1"; // the next trigger to run after data load is complete
	/*
	Add data to slots here
	
	EXAMPLE
	name | slot | maximum value
	addSavedDataQV("cow", 1, 10);
	addSavedDataDB(dPlayerData, xPlayerGold, 0, 1000);
	*/
	
	/*
	Slot 0
	Total size: 1
	*/
	addSavedDataDB(dPlayerData, xCineSeen , 0, 2);
	addSavedDataDB(dPlayerData, xPersonalBest , 0, 99999);
	//addLocalDataQV("example", 0, 1000); // the QV "example" can have an integer value from 0-999. It is stored in the first slot
	
	/*
	Slot 1
	Total size: 1000
	*/
	addLocalDataQV("VersionMessage", 1, 100);
	
	
	//Slot 2
	addSavedDataDB(dPlayerData, xWins , 2, 51);
	addSavedDataDB(dPlayerData, xSDWins , 2, 11);
	addSavedDataDB(dPlayerData, xMaxBank , 2, 101);
	
	
	
	/*
	Slot 3
	Total size: 1000
	*/
	
	/*
	Slot 4
	Total size: 0
	*/
	
	/*
	Slot 5
	Total size: 0
	*/
	
	/*
	Slot 6
	Total size: 0
	*/
	
	/*
	Slot 7
	Total size: 0
	*/
	
	/*
	Slot 8
	Total size: 0
	*/
	
	/*
	Slot 9
	Total size: 0
	*/
	
	/*
	Slot 10
	Total size: 0
	*/
	
	
	/*
	Slot 11
	Total size: 0
	*/
	
	/*
	Slot 12
	Total size: 0
	*/
	
	/*
	Slot 13
	Total size: 0
	*/
	
	/*
	Slot 14
	Total size: 0
	*/
	
	/*
	Slot 15
	Total size: 0
	*/
	addSavedDataDB(dPlayerData, xVersionControl, 15, 100);
	addSavedDataDB(dPlayerData, xSkin, 15, 100);
	addSavedDataDB(dPlayerData, xSeenSP, 15, 2);
	xsDisableSelf();
}

rule load1
inactive
highFrequency
{
	characterDialog("Loading map.", "Version "+MapVersion+"", "icons\special e son of osiris icon 64");
	xsEnableRule("load2");
	trBlockAllSounds(false);
	xsDisableSelf();
	while(cNumberNonGaiaPlayers>=trQuestVarGet("PlayerID")) {
		trQuestVarSet("PlayerID2", 0);
		while(cNumberNonGaiaPlayers>=trQuestVarGet("PlayerID2")) {
			trPlayerSetDiplomacy(trQuestVarGet("PlayerID"), trQuestVarGet("PlayerID2"), "Ally");
			trPlayerSetDiplomacy(trQuestVarGet("PlayerID2"), trQuestVarGet("PlayerID"), "Ally");
		trQuestVarSet("PlayerID2", trQuestVarGet("PlayerID2")+1);}
	trQuestVarSet("PlayerID", trQuestVarGet("PlayerID")+1);}
	
	for(p=1 ; <= cNumberNonGaiaPlayers){
		trPlayerSetDiplomacy(0, p, "Enemy");
		trTechSetStatus(p, 304, 4);
	}
	trTechSetStatus(0, 304, 4);
	xsEnableRule("Skin_DB");
}

rule load2
inactive
highFrequency
{
	characterDialog("Loading map..", "Version "+MapVersion+"", "icons\special e son of osiris icon 64");
	xsEnableRule("load3");
	xsEnableRule("Stats");
	xsEnableRule("Technologies");
	xsDisableSelf();
}

rule load3
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 1){
		characterDialog("Loading map...", "Version "+MapVersion+"", "icons\special e son of osiris icon 64");
		for(p = 1; <= cNumberNonGaiaPlayers){
			trPlayerGrantResources(p, "Food", -10000.0);
			trPlayerGrantResources(p, "Wood", -10000.0);
			trPlayerGrantResources(p, "Gold", -10000.0);
			trPlayerGrantResources(p, "Favor", -10000.0);
			trPlayerKillAllGodPowers(p);
			//this does custom content
			trSoundPlayFN("\Yeebaagooon\Agricultural Madness\test sound.mp3", "1", 13, "","");
		}
		xsEnableRule("load4");
		xsDisableSelf();
	}
}

rule load4
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 1){
		//fade out when loaded
		trSetObscuredUnits(false);
		trUnblockAllSounds();
		trLetterBox(false);
		trUIFadeToColor(0,0,0,1000,1,false);
		trOverlayTextColour(255, 125, 0);
		gadgetUnreal("ShowImageBox");
		trOverlayText(MapName, 8.0, 534, 28, 1000);
		trSetUnitIdleProcessing(true);
		xsDisableSelf();
		gadgetReal("ShowImageBox-BordersTop");
		gadgetReal("ShowImageBox-BordersBottom");
		gadgetReal("ShowImageBox-BordersLeft");
		gadgetReal("ShowImageBox-BordersRight");
		gadgetReal("ShowImageBox-BordersLeftTop");
		gadgetReal("ShowImageBox-BordersLeftBottom");
		gadgetReal("ShowImageBox-BordersRightBottom");
		gadgetReal("ShowImageBox-BordersRightTop");
		gadgetReal("ShowImageBox-CloseButton");
		//startNPCDialog(1);
		if((aiIsMultiplayer() == true) || (MultiplayerOverride == 1)){
			xsEnableRule("PaintSkinArea");
		}
		else if((aiIsMultiplayer() == false) && (MultiplayerOverride == 0)){
			xsEnableRule("StartSP");
		}
		xsEnableRule("CustomContentChat");
		//VERSION UPDATES
		int a = trCurrentPlayer();
		if(1*trQuestVarGet("VersionMessage") == 0){
			uiMessageBox("TEST VERSION DO NOT HOST");
			trQuestVarSet("VersionMessage", 0);
			xSetPointer(dPlayerData, a);
			xSetInt(dPlayerData, xVersionControl, MapVersion);
		}
		saveAllData();
		%
		for(p=1; <= cNumberNonGaiaPlayers) {
			code("trStringQuestVarSet(\"p"+p+"name\", \""+rmGetPlayerName(p)+"\");");
		}
		%
	}
}

void CustomContent(int p = 0){
	//xsSetContextPlayer(0);
	xsDisableSelf();
	trQuestVarSet("CustomContent", 1);
}



rule CustomContentChat
inactive
highFrequency
{
	if(1*trQuestVarGet("CustomContent") == 1){
		ColouredIconChat("1,0.5,0", "icons\special e son of osiris icon 64","Custom Content enabled!");
	}
	xsDisableSelf();
}
