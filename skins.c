void NewSkin(string protounitname = "", int required = 0, int anim = 1, vector scale = vector(2,2,2)){
	xAddDatabaseBlock(dSkin, true);
	xSetInt(dSkin, xUnitID, 0);
	xSetInt(dSkin, xSkinUnlocked, 0);
	xSetInt(dSkin, xGatherAnim, anim);
	xSetVector(dSkin, xSkinScale, scale);
	xSetString(dSkin, xSkinName, protounitname);
	xSetInt(dSkin, xSkinRequirement, required);
	trModifyProtounit(protounitname, 0, 55, 4);
	trModifyProtounit(protounitname, 0, 1, -40);
}
//Extra variable, anim for farm (attack as default)


rule Skin_DB
highFrequency
inactive
{
	//DEFAULT SKINS
	NewSkin("Villager Atlantean", 0);
	NewSkin("Villager Greek", 0);
	NewSkin("Villager Egyptian", 0);
	NewSkin("Villager Norse", 0);
	NewSkin("Villager Chinese", 0);
	//WIN SKINS
	NewSkin("Eitri", 1, 9);
	trQuestVarSet("WinSkin", 1*xGetPointer(dSkin));
	NewSkin("Brokk", 2, 9);
	NewSkin("Kastor", 3);
	NewSkin("Sphinx", 4, 39);
	NewSkin("Valkyrie", 5, 50,vector(1.5,1.5,1.5));
	NewSkin("Rhinocerous", 6);
	NewSkin("Colossus", 7, 46,vector(1.25,1.25,1.25));
	//shrinker
	NewSkin("Shade XP", 8,1);
	NewSkin("Automaton SPC", 9, 50);
	NewSkin("General Melagius", 10, 39);
	NewSkin("Fire Giant", 12, 6,vector(1.5,1.5,1.5));
	//mild shrinker
	NewSkin("Frost Giant", 14, 40, vector(1.5,1.5,1.5));
	NewSkin("Carcinos", 16, 18 ,vector(1.5,1.5,1.5));
	NewSkin("Fishing Ship Atlantean", 18, 30,vector(1.5,1.5,1.5));
	NewSkin("Bear", 20, 3);
	NewSkin("Pharaoh", 22, 33);
	NewSkin("Kastor Adult", 24, 51);
	NewSkin("Azure Dragon", 26, 1, vector(1,1,1));
	NewSkin("Amanra", 28);
	NewSkin("Bella", 30, 3);
	NewSkin("Walking Berry Bush", 35,1, vector(2,2,2));
	NewSkin("Snowman", 40,1, vector(2,2,2));
	NewSkin("Harpy Scout", 45,1, vector(2,2,2));
	NewSkin("Flying Purple Hippo", 50,1,vector(1.5,1.5,1.5));
	//POINT SKINS
	NewSkin("Chicken", 25, 2, vector(4,4,4));
	trQuestVarSet("PointSkin", 1*xGetPointer(dSkin));
	NewSkin("Mountain Giant", 30, 39);
	NewSkin("Hero Ragnorok", 35, 4);
	NewSkin("Argus", 40, 40, vector(1,1,1));
	NewSkin("Servant", 45, 50);
	NewSkin("Setna", 50, 50);
	NewSkin("Oracle Hero", 55, 52);
	NewSkin("Giant Duck-billed Platypus", 60, 1, vector(1.1,1.1,1.1));
	NewSkin("Nidhogg", 65, 1, vector(1,1,1));
	NewSkin("Earth Dragon", 80, 1, vector(1,1,1));
	//no walk anim
	NewSkin("Arkantos God", 100, 26);
	//PB SKINS
	NewSkin("Hero Greek Bellerophon", 200, 3);
	trQuestVarSet("PBSkin", 1*xGetPointer(dSkin));
	NewSkin("Forkboy", 300, 1, vector(1,1,1));
	NewSkin("Guardian XP", 400, 3, vector(1,1,1));
	//OTHER SKINS
	NewSkin("Athena", 0, 25);
	trQuestVarSet("ExtraSkin", 1*xGetPointer(dSkin));
	NewSkin("Fire Siphon", 0,1,vector(1,1,1));
	NewSkin("Gargarensis", 0, 30, vector(1,1,1));
	//huge float
	NewSkin("Minotaur", 0, 26);
	NewSkin("Pharaoh of Osiris XP", 0, 25);
	NewSkin("Hoplite", 0);
	//END = 48
	xsDisableSelf();
}

rule Animations
highFrequency
inactive
{
	int anim = 0;
	for(p=1 ; <= cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(xGetInt(dPlayerData, xSkin) <= 4){
			continue;
		}
		if(xGetInt(dPlayerData, xSkin) > 4){
			anim = 0;
			anim = kbUnitGetAnimationActionType(kbGetBlockID(""+1*trQuestVarGet("P"+p+"Farmer")+""));
			xSetPointer(dPlayerData, p);
			if((xGetInt(dPlayerData, xOldAnim) == anim) || (xGetInt(dPlayerData, xOldAnim) == -10)){
				continue;
				//Stop if no anim change
			}
			//NO NEED FOR THIS, USE DATAbase
			xSetInt(dPlayerData, xOldAnim, anim);
			//Walk
			if((anim == 10) || (anim == 11)){
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitOverrideAnimation(15, 0, true, true, -1, 0);
			}
			//Gather
			if((anim == 5)){
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitOverrideAnimation(xGetInt(dSkin, xGatherAnim, xGetInt(dPlayerData, xSkin)), 0, true, true, -1, 0);
			}
			//Idle
			if((anim == 9)){
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitOverrideAnimation(2, 0, true, true, -1, 0);
			}
			//Flail
			if((anim == 29)){
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitOverrideAnimation(24, 0, true, true, -1, 0);
			}
		}
	}
}

string SkinProto(int id = 0) {
	string msg = "WTF That's not a skin!";
	msg = xGetString(dSkin, xSkinName, xGetInt(dPlayerData, xSkin));
	//Sekret sekret 3rd param of index
	return(msg);
}

rule ConvertSpies
highFrequency
inactive
{
	vector scale = xsVectorSet(dSkin, xSkinScale, xGetInt(dPlayerData, xSkin));
	for(p=1 ; <= cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		scale = xGetVector(dSkin, xSkinScale, xGetInt(dPlayerData, xSkin));
		if(xGetInt(dPlayerData, xSkin) > 4){
			xUnitSelect(dPlayerData, xSpyID);
			trUnitChangeProtoUnit("Villager Greek");
			xUnitSelect(dPlayerData, xSpyID);
			trUnitConvert(p);
			xUnitSelect(dPlayerData, xSpyID);
			trUnitChangeProtoUnit("Spy Eye");
			xUnitSelect(dPlayerData, xSpyID);
			trMutateSelected(kbGetProtoUnitID(""+SkinProto(xGetInt(dPlayerData, xSkin))));
			xUnitSelect(dPlayerData, xSpyID);
			trSetSelectedScale(xsVectorGetX(scale),xsVectorGetY(scale),xsVectorGetZ(scale));
		}
	}
	xsDisableSelf();
}

rule PaintTerrain
highFrequency
inactive
{
	//if (trTime() > cActivationTime + 1) {
	xsDisableSelf();
	trQuestVarSet("Round", 1*trQuestVarGet("Round")+1);
	if(1*trQuestVarGet("Round") != 4){
		for(x=1 ; <= MapSize/6){
			for(z=1 ; <= MapSize/6){
				paintShopSquare(x*3-2,z*3-2, "black");
				trQuestVarSet("FarmX"+x+"Z"+z+"", trGetNextUnitScenarioNameNumber());
				UnitCreate(0, "Cinematic Block", x*6-4, z*6-4, 0);
				xAddDatabaseBlock(dFlags, true);
				xSetInt(dFlags, xUnitID, 0);
				xSetInt(dFlags, xFlagX, x);
				xSetInt(dFlags, xFlagZ, z);
				xSetInt(dFlags, xFlagOwner, 0);
			}
		}
		trBlockAllSounds(true);
		for(x=1 ; <= MapSize/6){
			for(z=1 ; <= MapSize/6){
				trUnitSelectClear();
				trUnitSelectByQV("FarmX"+x+"Z"+z+"");
				trUnitChangeProtoUnit("Farm");
			}
		}
		trUnblockAllSounds();
	}
	XMax = MapSize/6;
	ZMax = MapSize/6;
	trVectorQuestVarSet("dir", xsVectorSet(MapSize*-0.3, 0, MapSize*-0.3));
	trVectorQuestVarSet("CentreMap", xsVectorSet(MapSize*0.5-1, 0, MapSize*0.5-1));
	float baseCos = xsCos(6.283185 / cNumberNonGaiaPlayers);
	float baseSin = xsSin(6.283185 / cNumberNonGaiaPlayers);
	int heading = 45+(360/cNumberNonGaiaPlayers);
	for(p=1; <= cNumberNonGaiaPlayers) {
		trVectorQuestVarSet("base", trVectorQuestVarGet("CentreMap") + trVectorQuestVarGet("dir"));
		trQuestVarSet("P"+p+"Farmer", trGetNextUnitScenarioNameNumber());
		heading = heading-(360/cNumberNonGaiaPlayers);
		if(heading > 360){
			heading = heading-360;
		}
		if(heading < 0){
			heading = heading+360;
		}
		UnitCreate(p, "Cinematic Block", trVectorQuestVarGetX("base"), trVectorQuestVarGetZ("base"), heading);
		trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
		trUnitSelectClear();
		trUnitSelectByQV("P"+p+"Farmer");
		xSetPointer(dPlayerData, p);
		xSetInt(dPlayerData, xUnitID, 1*trQuestVarGet("P"+p+"Farmer"));
		switch(xGetInt(dPlayerData, xSkin))
		{
			case 0:
			{
				trUnitChangeProtoUnit("Villager Atlantean");
			}
			case 1:
			{
				trUnitChangeProtoUnit("Villager Greek");
			}
			case 2:
			{
				trUnitChangeProtoUnit("Villager Egyptian");
			}
			case 3:
			{
				trUnitChangeProtoUnit("Villager Norse");
			}
			case 4:
			{
				trUnitChangeProtoUnit("Villager Chinese");
			}
		}
		if(xGetInt(dPlayerData, xSkin) > 5){
			trUnitChangeProtoUnit("Villager Egyptian");
		}
		trUnitSelectByQV("P"+p+"Farmer");
		if(xGetInt(dPlayerData, xSkin) > 5){
			trSetSelectedScale(0,2,0);
			spyEffect(1*trQuestVarGet("P"+p+"Farmer"), kbGetProtoUnitID(""+SkinProto(xGetInt(dPlayerData, xSkin))), xsVectorSet(dPlayerData,xSpyID,p), xGetVector(dSkin, xSkinScale, xGetInt(dPlayerData, xSkin)));
		}
		else{
			trSetSelectedScale(2,2,2);
			trUnitSelectByQV("P"+p+"Farmer");
			trUnitConvert(0);
		}
		//Sudden death detsroy players who aren't playing
		if(1*trQuestVarGet("Round") == 4){
			if(1*trQuestVarGet("P"+p+"Place") != 1){
				trUnitSelectByQV("P"+p+"Farmer");
				trUnitDestroy();
			}
			trPaintTerrain(0,0,MapSize,MapSize,5,4);
			trQuestVarSet("QVEarth", trGetNextUnitScenarioNameNumber());
			UnitCreate(0, "Cinematic Block", MapSize/2, MapSize/2, 0);
			trUnitSelectByQV("QVEarth");
			trUnitChangeProtoUnit("Spy Eye");
			trUnitSelectByQV("QVEarth");
			trMutateSelected(kbGetProtoUnitID("Earth"));
			trUnitSelectByQV("QVEarth");
			trSetSelectedScale(4.7,-0.1,4.7);
			trUnitSelectByQV("QVEarth");
			trUnitHighlight(1000, false);
			xAddDatabaseBlock(dDestroy, true);
			xSetInt(dDestroy, xUnitID,1*trQuestVarGet("QVEarth"));
			for(x=0 ; < MapSize){
				trQuestVarSetFromRand("TempX", 0, MapSize, false);
				trQuestVarSetFromRand("TempZ", 0, MapSize, false);
				trQuestVarSet("TempUnit", trGetNextUnitScenarioNameNumber());
				trArmyDispatch("0,0", "Victory Marker", 1, 1*trQuestVarGet("TempX"),0,1*trQuestVarGet("TempZ"),0,false);
				trUnitSelectByQV("TempUnit");
				trUnitChangeProtoUnit("Armor Glow Small");
				xAddDatabaseBlock(dDestroy, true);
				xSetInt(dDestroy, xUnitID,1*trQuestVarGet("TempUnit"));
			}
		}
	}
	trCameraCut(vector(-63.781834,123.743729,-63.781834), vector(0.500000,-0.707107,0.500000), vector(0.500000,0.707107,0.500000), vector(0.707107,0.000000,-0.707107));
	int a = trCurrentPlayer();
	trUnitSelectClear();
	trUnitSelectByQV("P"+a+"Farmer");
	trUnitHighlight(3, true);
	uiLookAtUnit(kbGetBlockID(""+1*trQuestVarGet("P"+a+"Farmer")));
	trOverlayText("Round " + 1*trQuestVarGet("Round") , 5.0, 608, 300, 1000);
	xsEnableRule("RoundStart");
	xsEnableRule("Animations");
	trDelayedRuleActivation("HideSpies");
	if(1*trQuestVarGet("Round") == 2){
		ColouredIconChat("1,0.5,0", "world a tsunami range indicator", "Arrow shrines convert entire rows of farms!");
	}
	if(1*trQuestVarGet("Round") == 3){
		uiMessageBox("Missiles will now steal farms when they hit a player!");
	}
}

rule HideSpies
highFrequency
inactive
{
	for(p=1; <= cNumberNonGaiaPlayers) {
		xSetPointer(dPlayerData, p);
		if(xGetInt(dPlayerData, xSkin) > 4){
			trUnitSelectByQV("P"+p+"Farmer");
			trUnitChangeProtoUnit("Cinematic Block");
		}
	}
	xsDisableSelf();
}

rule PaintSkinArea
highFrequency
inactive
{
	xsDisableSelf();
	trPaintTerrain(0,0,MapSize,MapSize,2,1);
	trPaintTerrainCircle(MapSize/4-1, MapSize/4-1, 9, 0, 95);
	trPaintTerrain(0,0,0,0,2,1, true);
	trVectorQuestVarSet("dir", xsVectorSet(14, 0, 0));
	trVectorQuestVarSet("CentreMap", xsVectorSet(MapSize*0.5-1, 0, MapSize*0.5-1));
	//Cceate Skins
	float baseCos = xsCos(6.283185 / 4);
	float baseSin = xsSin(6.283185 / 4);
	int heading = 390;
	for(n=1; <= 4) {
		trVectorQuestVarSet("base", trVectorQuestVarGet("CentreMap") + trVectorQuestVarGet("dir"));
		trQuestVarSet("Skin"+n+"", trGetNextUnitScenarioNameNumber());
		heading = heading-90;
		UnitCreate(0, "Cinematic Block", trVectorQuestVarGetX("base"), trVectorQuestVarGetZ("base"), heading);
		trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
		trUnitSelectClear();
		trUnitSelectByQV("Skin"+n+"");
		switch(n)
		{
			case 1:
			{
				trUnitChangeProtoUnit("Villager Greek");
			}
			case 2:
			{
				trUnitChangeProtoUnit("Villager Egyptian");
			}
			case 3:
			{
				trUnitChangeProtoUnit("Villager Norse");
			}
			case 4:
			{
				trUnitChangeProtoUnit("Villager Chinese");
			}
		}
		trUnitSelectClear();
		trUnitSelectByQV("Skin"+n+"");
		trSetSelectedScale(2,2,2);
		trUnitSelectByQV("Skin"+n+"");
		trUnitOverrideAnimation(9,0,true,true,-1,0);
		xsEnableRule("SkinChooserDeploy");
		trCameraCut(vector(-63.781834,123.743729,-63.781834), vector(0.500000,-0.707107,0.500000), vector(0.500000,0.707107,0.500000), vector(0.707107,0.000000,-0.707107));
	}
}

rule SkinChooserDeploy
inactive
highFrequency
{
	xsDisableSelf();
	//Create choosers
	trVectorQuestVarSet("dir", xsVectorSet(4,0,0));
	trVectorQuestVarSet("CentreMap", xsVectorSet(MapSize*0.5-1, 0, MapSize*0.5-1));
	float baseCos = xsCos(6.283185 / cNumberNonGaiaPlayers);
	float baseSin = xsSin(6.283185 / cNumberNonGaiaPlayers);
	int heading = 270+(360/cNumberNonGaiaPlayers);
	for(p=1; <= cNumberNonGaiaPlayers) {
		heading = heading-(360/cNumberNonGaiaPlayers);
		trVectorQuestVarSet("base", trVectorQuestVarGet("CentreMap") + trVectorQuestVarGet("dir"));
		trQuestVarSet("P"+p+"SkinChooser", trGetNextUnitScenarioNameNumber());
		UnitCreate(p, "Cinematic Block", trVectorQuestVarGetX("base"), trVectorQuestVarGetZ("base"), heading);
		trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
		trUnitSelectClear();
		trUnitSelectByQV("P"+p+"SkinChooser");
		trUnitChangeProtoUnit("Villager Atlantean Hero");
		xSetPointer(dPlayerData, p);
		if(xGetInt(dPlayerData, xSkin) <= 5){
			xSetInt(dPlayerData, xSkin, 0);
		}
		if(p == trCurrentPlayer()){
			trUnitSelectClear();
			trUnitSelectByQV("P"+p+"SkinChooser");
			trUnitHighlight(30, true);
		}
	}
	trMessageSetText("Move to a villager to choose your skin (cosmetic only). If all players delete the counter ends.", 10000);
	trCounterAddTime("CDSkin", 20-(10*QuickStart), 0, "<color={PlayerColor(1)}>Time remaining", 14);
	xsEnableRule("SkinChange");
	xsEnableRule("SkinEarlyEnd");
	xsEnableRule("SkinKillCPU");
	for(b=1; <= cNumberNonGaiaPlayers) {
		xSetPointer(dPlayerData, b);
		if(xGetInt(dPlayerData, xSkin) > 5){
			trUnitSelectClear();
			trUnitSelectByQV("P"+b+"SkinChooser");
			trUnitChangeProtoUnit("Poison SFX");
			ColouredChatToPlayer(b, "1,0.5,0", "Your skin choice has been loaded.");
		}
	}
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
}

rule SkinKillCPU
inactive
highFrequency
{
	for(p=1; <= cNumberNonGaiaPlayers) {
		xSetPointer(dPlayerData, p);
		if((kbIsPlayerHuman(p) == false) || (kbIsPlayerResigned(p) == true)){
			trUnitSelectByQV("P"+p+"SkinChooser");
			trUnitChangeProtoUnit("Einheriar Boost SFX");
			xSetInt(dPlayerData, xCineSeen, 1);
		}
	}
	xsDisableSelf();
}

rule SkinChange
inactive
minInterval 1
{
	for(p=1; <= cNumberNonGaiaPlayers) {
		trUnitSelectClear();
		trUnitSelectByQV("P"+p+"SkinChooser");
		xSetPointer(dPlayerData, p);
		for(n=1; <= 4) {
			if(trUnitDistanceToUnit(""+1*trQuestVarGet("Skin"+n+"")) < 3){
				if(xGetInt(dPlayerData, xSkin) != n){
					xSetInt(dPlayerData, xSkin, n);
					switch(n)
					{
						case 1:
						{
							trUnitChangeProtoUnit("Villager Greek");
						}
						case 2:
						{
							trUnitChangeProtoUnit("Villager Egyptian");
						}
						case 3:
						{
							trUnitChangeProtoUnit("Villager Norse");
						}
						
						case 4:
						{
							trUnitChangeProtoUnit("Villager Chinese");
						}
					}
					if(p == trCurrentPlayer()){
						trUnitSelectClear();
						trUnitSelectByQV("P"+p+"SkinChooser");
						trUnitHighlight(1, true);
					}
				}
			}
		}
	}
}

void SkinTimeEnd (int p = 0){
	xsDisableSelf();
	xsEnableRule("SkinCommonEnd");
}

rule SkinEarlyEnd
inactive
highFrequency
{
	int CallsToEnd = 0;
	for(p=1; <= cNumberNonGaiaPlayers) {
		if(trPlayerGetPopulation(p) == 0){
			CallsToEnd = CallsToEnd+1;
		}
	}
	if(CallsToEnd == cNumberNonGaiaPlayers){
		xsDisableSelf();
		xsEnableRule("SkinCommonEnd");
		trCounterAbort("CDSkin");
		trMessageSetText("Move to a villager to choose your skin (cosmetic only). If all players delete the counter ends.", 1);
	}
}

rule SkinCommonEnd
inactive
highFrequency
{
	xsDisableSelf();
	trCounterAbort("CDSkin");
	xsDisableRule("SkinChange");
	xsDisableRule("SkinEarlyEnd");
	for(p=1; <= cNumberNonGaiaPlayers) {
		trUnitSelectClear();
		trUnitSelectByQV("P"+p+"SkinChooser");
		trUnitChangeProtoUnit("Hero Death");
		modifyProtounitAbsolute("Villager Greek", p, 1, 6);
		modifyProtounitAbsolute("Villager Egyptian", p, 1, 6);
		modifyProtounitAbsolute("Villager Norse", p, 1, 6);
		modifyProtounitAbsolute("Villager Chinese", p, 1, 6);
		modifyProtounitAbsolute("Villager Atlantean Hero", p, 1, 6);
		modifyProtounitAbsolute("Villager Atlantean", p, 1, 6);
	}
	for(n=1; <= 4) {
		trUnitSelectClear();
		trUnitSelectByQV("Skin"+n+"");
		trUnitChangeProtoUnit("Heavenlight");
	}
	trFadeOutAllSounds(0.1);
	trFadeOutMusic(0.1);
	playSound("ageadvance.wav");
	trUIFadeToColor(0,0,0,800,199,true);
	xsEnableRule("CineChoice");
}
