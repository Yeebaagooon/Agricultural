/*
IDEAS
Search //Release


Port reselctmyself()
missile r3 as uibox
if (trGetScenarioUserData(8, "Ascension MMORPG.xs") > 140785919) { }
*/



//---Controls
//\Yeebaagooon\Agricultural Madness\Test sound.mp3
int QuickStart = 0;
int MapVersion = 0;
string MapName = "Agricultural Madness";
string displayz = "";
string farmicon = "";
int MultiplayerOverride = 0;

int ThirdPlacePlayer = 0;
int SecondPlacePlayer = 0;
int FirstPlacePlayer = 0;
int TiePlayer = 0;

int MapSize = 0;
int XMax = 0;
int ZMax = 0;
int dPlayerData = 0;
int xSpyID = 0;
int xOldAnim = 0;
int xTarget = 0;
int xMissileCount = 0;

float timediff = 0;
int timelast = 0;

int RoundTime = 120;
int BankCrates = 0;
int RelicsAllowed = 0;
int MissilesAllowed = 0;
int ArrowsAllowed = 0;


int dCrates = 0;
int xUnitID = 0;
int xPosX = 0;
int xPosZ = 0;
int xTimeIn = 0;
int xTimeOut = 0;
int xSkin = 0;
int xSkinNumber = 0;
int xSkinRequirement = 0;

int dRelics = 0;
int xRelicSFX = 0;
int dMissileBox = 0;
int xMissileSFX = 0;

int dMissiles = 0;
int xOwner = 0;
int xMissilePos = 0;
int xMissileDir = 0;
int xMissileCentre = 0;
int xMissilePrev = 0;
int xWins = 0;
int xSDWins = 0;
int xMaxBank = 0;
int xSeenSP = 0;

int dArrows = 0;
int xDirection = 0;
int xArrowClock = 0;
int xArrowSFX = 0;
int xArrowBuilding = 0;
int xVectorDir = 0;

int dFlags = 0;
int xFlagX = 0;
int xFlagZ = 0;
int xFlagOwner = 0;

int dSkin = 0;
int xSkinID = 0;
int xSkinName = 0;
int xSkinUnlocked = 0;
int xGatherAnim = 0;

int tie1 = -1;
int tie2 = -1;
int tie3 = -1;
int xCineSeen = 0;
int xVersionControl = 0;
int xPersonalBest = 0;

vector MapCentre = vector(0,0,0);

int dDestroy = 0;


rule setup_first_databases
active
highFrequency
{
	dPlayerData = xInitDatabase("playerData");
	xUnitID = xInitAddInt(dPlayerData, "farmer ID", -1);
	xSpyID = xInitAddInt(dPlayerData, "Spy id", -1);
	xOldAnim = xInitAddInt(dPlayerData, "Anim id", 0);
	xTarget = xInitAddInt(dPlayerData, "target id", 0);
	xMissileCount = xInitAddInt(dPlayerData, "missile count", 0);
	xCineSeen = xInitAddInt(dPlayerData, "seen the cine", 0);
	xVersionControl = xInitAddInt(dPlayerData, "version", 0);
	xPersonalBest = xInitAddInt(dPlayerData, "pb score", 0);
	xSkin = xInitAddInt(dPlayerData, "skin id", 0);
	xOldAnim = xInitAddInt(dPlayerData, "anim", 0);
	xWins = xInitAddInt(dPlayerData, "total wins", 0);
	xSDWins = xInitAddInt(dPlayerData, "SD wins", 0);
	xMaxBank = xInitAddInt(dPlayerData, "Max points in one go", 0);
	xSeenSP = xInitAddInt(dPlayerData, "Seen SP", 0);
	xsDisableSelf();
	for(p=1; <= cNumberNonGaiaPlayers) {
		xAddDatabaseBlock(dPlayerData, true);
	}
	dCrates = xInitDatabase("Crates");
	xUnitID = xInitAddInt(dCrates, "crate ID", -1);
	xPosX = xInitAddInt(dCrates, "X Pos", 0);
	xPosZ = xInitAddInt(dCrates, "Z Pos", 0);
	xTimeIn = xInitAddInt(dCrates, "Timer in", 0);
	xTimeOut = xInitAddInt(dCrates, "Timer out", 0);
	//Using same int over different DBs only works if they are in the same order
	
	dDestroy = xInitDatabase("DestroyDB");
	xUnitID = xInitAddInt(dDestroy, "unitid", 0);
	
	dSkin = xInitDatabase("SkinsDB");
	xUnitID = xInitAddInt(dSkin, "unitid", 0);
	xSkinNumber = xInitAddInt(dSkin, "skinid", 0);
	xSkinRequirement = xInitAddInt(dSkin, "skin unlock", 0);
	xSkinName = xInitAddString(dSkin, "Skin protoname", " ");
	xSkinUnlocked = xInitAddInt(dSkin, "unlocked", 0);
	xGatherAnim = xInitAddInt(dSkin, "farm anim", 1);
	
	dFlags = xInitDatabase("Flags");
	xUnitID = xInitAddInt(dFlags, "unitid", 0);
	xFlagX = xInitAddInt(dFlags, "x", 0);
	xFlagZ = xInitAddInt(dFlags, "z", 0);
	xFlagOwner = xInitAddInt(dFlags, "p", 0);
	
	dRelics = xInitDatabase("Relics");
	xUnitID = xInitAddInt(dRelics, "relic ID", -1);
	xPosX = xInitAddInt(dRelics, "X Pos", 0);
	xPosZ = xInitAddInt(dRelics, "Z Pos", 0);
	xTimeIn = xInitAddInt(dRelics, "Timer in", 0);
	xTimeOut = xInitAddInt(dRelics, "Timer out", 0);
	xRelicSFX = xInitAddInt(dRelics, "SFX ID", 0);
	
	dMissileBox = xInitDatabase("Missilebox");
	xUnitID = xInitAddInt(dMissileBox, "relic ID", -1);
	xPosX = xInitAddInt(dMissileBox, "X Pos", 0);
	xPosZ = xInitAddInt(dMissileBox, "Z Pos", 0);
	xTimeIn = xInitAddInt(dMissileBox, "Timer in", 0);
	xTimeOut = xInitAddInt(dMissileBox, "Timer out", 0);
	xMissileSFX = xInitAddInt(dMissileBox, "SFX ID", 0);
	
	dMissiles = xInitDatabase("Missiles DB");
	xUnitID = xInitAddInt(dMissiles, "missile unit id", -1);
	xOwner = xInitAddInt(dMissiles, "missile owner", 0);
	xMissilePos = xInitAddVector(dMissiles, "position", vector(0,0,0));
	xMissileDir = xInitAddVector(dMissiles, "direction", vector(0,0,0));
	xMissileCentre = xInitAddVector(dMissiles, "centre", vector(0,0,0));
	xMissilePrev = xInitAddVector(dMissiles, "prev", vector(0,0,0));
	
	dArrows = xInitDatabase("Arrow DB");
	xUnitID = xInitAddInt(dArrows, "ID", -1);
	xPosX = xInitAddInt(dArrows, "X Pos", 0);
	xPosZ = xInitAddInt(dArrows, "Z Pos", 0);
	xTimeIn = xInitAddInt(dArrows, "Timer in", 0);
	xTimeOut = xInitAddInt(dArrows, "Timer out", 0);
	xArrowSFX = xInitAddInt(dArrows, "Unit SFX", 0);
	xArrowClock = xInitAddBool(dArrows, "Clock", true);
	xDirection = xInitAddInt(dArrows, "current dir", 0);
	xArrowBuilding = xInitAddInt(dArrows, "SFX2", 0);
	xVectorDir = xInitAddVector(dArrows, "dir", vector(0,0,0));
}

bool rayCollision(vector start = vector(0,0,0), vector dir = vector(1,0,0),
	float dist = 0, float width = 0) {
	vector pos = kbGetBlockPosition(""+xGetInt(dPlayerData,xUnitID),true);
	float current = distanceBetweenVectors(pos, start, false);
	if (current < dist) {
		vector hitbox = start + dir * current;
		if (distanceBetweenVectors(pos, hitbox, true) <= width) {
			return(true);
		}
	}
	return(false);
}

void DoMissile(){
	//xMissilePos = current pos
	//xMissileDir = direction vector
	//xMissileCenter = where the base of the obelisk is
	//xMissilePrev = last time i checked the hitbox
	xDatabaseNext(dMissiles);
	vector pos = vector(0,0,0);
	vector dir = vector(0,0,0);
	vector prev = vector(0,0,0);
	prev = xGetVector(dMissiles, xMissilePrev);
	bool hit = false;
	int playerhit = 0;
	int boomID = 0;
	pos = xGetVector(dMissiles, xMissilePos); // retrieve current pos
	pos = pos + xGetVector(dMissiles, xMissileDir) * timediff; // calculate new pos with physics
	dir = (pos - MapCentre) * 3.33; // calculate the stretch of the obelisk
	xUnitSelect(dMissiles, xUnitID);
	trSetSelectedUpVector(xsVectorGetX(dir),0.2,xsVectorGetZ(dir)); // actually stretch the obelisk
	xSetVector(dMissiles, xMissilePos, pos);
	xSetPointer(dPlayerData, xGetInt(dMissiles, xOwner));
	//>1 rather than 0 to search through all players except the owner as we start with that one
	float dist = distanceBetweenVectors(pos, prev, false);
	dir = xsVectorNormalize(dir);
	for(x=xGetDatabaseCount(dPlayerData); >1) {
		xDatabaseNext(dPlayerData);
		//2 is raw dist, 4 is squared
		if(rayCollision(prev,dir,dist+2,4)){
			hit = true;
			playerhit = xGetPointer(dPlayerData);
			break;
		}
	}
	if(hit){
		//hit effect
		xUnitSelect(dMissiles, xUnitID);
		trUnitDestroy();
		boomID = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Cinematic Block", xsVectorGetX(pos), xsVectorGetZ(pos), 0);
		trTechInvokeGodPower(0, "Tremor", pos);
		if(1*trQuestVarGet("Round") == 3){
			trUnitSelectClear();
			trUnitSelect(""+boomID);
			trUnitChangeInArea(playerhit, 1*xGetInt(dMissiles, xOwner), "Farm", "Farm", MapSize*6);
			trUnitSelectClear();
			trUnitSelect(""+boomID);
			trUnitChangeProtoUnit("Implode Sphere Effect");
			trUnitSelectClear();
			trUnitSelect(""+boomID);
			trDamageUnitPercent(100);
			playSound("pigout.wav");
		}
		else if(1*trQuestVarGet("Round") == 4){
			trUnitSelectClear();
			trUnitSelect(""+boomID);
			trUnitChangeProtoUnit("Implode Sphere Effect");
			trUnitSelectClear();
			trUnitSelect(""+boomID);
			trDamageUnitPercent(100);
			playSound("implode explode.wav");
			trUnitSelectByQV("P"+playerhit+"Farmer");
			trDamageUnitPercent(100);
			trQuestVarModify("SuddenDeaths", "+", 1);
			trPlayerKillAllGodPowers(playerhit);
		}
		else{
			trUnitSelectClear();
			trUnitSelect(""+boomID);
			trUnitChangeProtoUnit("Meteor Impact Ground");
		}
		playSound("implode explode.wav");
		//trTechGodPower(0, "Tremor", 1);
		//FREE DB LAST
		xFreeDatabaseBlock(dMissiles);
	}
	else{
		xSetVector(dMissiles, xMissilePrev, pos);
		if((xsVectorGetX(pos) < 0) || (xsVectorGetX(pos) > MapSize) || (xsVectorGetZ(pos) < 0) || (xsVectorGetZ(pos) > MapSize)){
			//remove map outside
			xUnitSelect(dMissiles, xUnitID);
			trUnitDestroy();
			xFreeDatabaseBlock(dMissiles);
		}
	}
}

