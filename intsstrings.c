//---Controls
//\Yeebaagooon\Agricultural Madness\Test sound.mp3
int QuickStart = 1;
string MapVersion = "Test Version";
string MapName = "Agricultural Madness";

int MapSize = 0;
int XMax = 0;
int ZMax = 0;
int dPlayerData = 0;
int xSpyID = 0;
int xOldAnim = 0;
int xTarget = 0;

int RoundTime = 120;
int BankCrates = 0;


int dCrates = 0;
int xUnitID = 0;
int xPosX = 0;
int xPosZ = 0;
int xTimeIn = 0;
int xTimeOut = 0;

rule setup_first_databases
active
highFrequency
{
	dPlayerData = xInitDatabase("playerData");
	xSpyID = xInitAddInt(dPlayerData, "Spy id", 0);
	xOldAnim = xInitAddInt(dPlayerData, "Anim id", 0);
	xTarget = xInitAddInt(dPlayerData, "target id", 0);
	xsDisableSelf();
	for(p=1; <= cNumberNonGaiaPlayers) {
		xAddDatabaseBlock(dPlayerData, true);
	}
	dCrates = xInitDatabase("Crates");
	xUnitID = xInitAddInt(dCrates, "crate ID", 0);
	xPosX = xInitAddInt(dCrates, "X Pos", 0);
	xPosZ = xInitAddInt(dCrates, "Z Pos", 0);
	xTimeIn = xInitAddInt(dCrates, "Timer in", 0);
	xTimeOut = xInitAddInt(dCrates, "Timer out", 0);
}
