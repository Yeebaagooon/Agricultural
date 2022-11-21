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
	if(QuickStart == 0){
	}
	trBlockAllSounds(true);
	trArmyDispatch("0,0", "Cinematic Block", 1, 0, 0, 0, 0, false);
	for(p = 1; <= cNumberNonGaiaPlayers){
		deployLocHeading(0, p*2, "Victory Marker", p, 180);
	}
	trSetFogAndBlackmap(false, false);
	%
	for(p=1; <= cNumberNonGaiaPlayers) {
		code("trStringQuestVarSet(\"p"+p+"name\", \""+rmGetPlayerName(p)+"\");");
	}
	%
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
	characterDialog("Initialising map", " ", "icons\special e son of osiris icon 64");
	xsEnableRule("load1");
	xsDisableSelf();
	//HOTKEYS
	map("q", "game", "uiSetSpecialPower(220) uiSpecialPowerAtPointer");
	if(cNumberNonGaiaPlayers <= 5){
		MapSize = 48;
	}
	else if(cNumberNonGaiaPlayers <= 10){
		MapSize = 60;
	}
	else{
		MapSize = 72;
	}
	MapCentre = xsVectorSet(MapSize/2-1,0,MapSize/2-1);
}

rule load1
inactive
highFrequency
{
	characterDialog("Loading map.", ""+MapVersion+"", "icons\special e son of osiris icon 64");
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
	}
	trTechSetStatus(0, 304, 4);
}

rule load2
inactive
highFrequency
{
	characterDialog("Loading map..", ""+MapVersion+"", "icons\special e son of osiris icon 64");
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
		characterDialog("Loading map...", ""+MapVersion+"", "icons\special e son of osiris icon 64");
		for(p = 1; <= cNumberNonGaiaPlayers){
			trPlayerGrantResources(p, "Food", -10000.0);
			trPlayerGrantResources(p, "Wood", -10000.0);
			trPlayerGrantResources(p, "Gold", -10000.0);
			trPlayerGrantResources(p, "Favor", -10000.0);
			trPlayerKillAllGodPowers(p);
			//this does custom content
			//trSoundPlayFN("\Yeebaagooon\Agricultural Madness\test sound.mp3", "1", 13, "","");
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
		xsEnableRule("PaintSkinArea");
		//xsEnableRule("CustomContentChat");
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
