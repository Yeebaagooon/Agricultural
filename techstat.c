rule Technologies
inactive
highFrequency
{
	trTechSetStatus(0, 14, 4);
	trTechSetStatus(0, 7, 4);
	trTechSetStatus(0, 20, 4);
	trTechSetStatus(0, 59, 4);
	trTechSetStatus(0, 102, 4);
	trTechSetStatus(0, 127, 4);
	trTechSetStatus(0, 411, 4);
	trTechSetStatus(0, 347, 4);
	for(p = 1; <= cNumberNonGaiaPlayers){
		trTechSetStatus(p, 1, 4);
		trTechSetStatus(p, 2, 4);
		trTechSetStatus(p, 116, 4);
		trTechSetStatus(p, 29, 4);
		trTechSetStatus(p, 353, 0);
		trTechSetStatus(p, 394, 0);
		trTechSetStatus(p, 510, 0);
		trTechSetStatus(p, 145, 0);
		trTechSetStatus(p, 144, 0);
		trTechSetStatus(p, 143, 0);
		trTechSetStatus(p, 379, 0);
		trTechSetStatus(p, 28, 4);
		trTechSetStatus(p, 30, 4);
		trTechSetStatus(p, 350, 4);
		trTechSetStatus(p, 27, 4);
		trTechSetStatus(p, 14, 4);
		trTechSetStatus(p, 7, 4);
		trTechSetStatus(p, 20, 4);
		trTechSetStatus(p, 59, 4);
		trTechSetStatus(p, 102, 4);
		for(n=930; >0) {
			trForbidProtounit(p,kbGetProtoUnitName(n));
		}
	}
	//      trUnforbidProtounit(p, "Outpost");
	//  trUnforbidProtounit(1*p, "Oracle Hero");
	xsDisableSelf();
}

rule Stats
inactive
highFrequency
{
	trModifyProtounit("Dwarf", 0, 55, 4);
	for(p = 1; <= cNumberNonGaiaPlayers){
		trModifyProtounit("Dwarf", p, 55, 4);
		trModifyProtounit("Animal Attractor", p, 55, 4);
		trModifyProtounit("Hero Greek Bellerophon", p, 55, 4);
		//trQuestVarSet("P"+p+"FlagBaseWarnF", 15);
		//modifyProtounitAbsolute("Gate", p, 0, 1000);
		modifyProtounitAbsolute("Vision Revealer", p, 6, 100);
		modifyProtounitAbsolute("Villager Greek", p, 1, 10);
		modifyProtounitAbsolute("Villager Egyptian", p, 1, 10);
		modifyProtounitAbsolute("Villager Norse", p, 1, 10);
		modifyProtounitAbsolute("Villager Chinese", p, 1, 10);
		modifyProtounitAbsolute("Villager Atlantean Hero", p, 1, 10);
		modifyProtounitAbsolute("Villager Atlantean", p, 1, 10);
		trModifyProtounit("Vision Revealer", p, 6, 100);
		trModifyProtounit("Villager Greek", p, 22, 1000);
		trModifyProtounit("Villager Egyptian", p, 22, 1000);
		trModifyProtounit("Villager Norse", p, 22, 1000);
		trModifyProtounit("Villager Chinese", p, 22, 1000);
		trModifyProtounit("Villager Atlantean Hero", p, 22, 1000);
		trModifyProtounit("Villager Atlantean", p, 22, 1000);
		modifyProtounitAbsolute("Villager Greek", p, 0, 1000);
		modifyProtounitAbsolute("Villager Egyptian", p, 0, 1000);
		modifyProtounitAbsolute("Villager Norse", p, 0, 1000);
		modifyProtounitAbsolute("Villager Chinese", p, 0, 1000);
		modifyProtounitAbsolute("Villager Atlantean Hero", p, 0, 1000);
		modifyProtounitAbsolute("Villager Atlantean", p, 0, 1000);
		modifyProtounitAbsolute("Villager Greek", p, 27, 0);
		modifyProtounitAbsolute("Villager Egyptian", p, 27, 0);
		modifyProtounitAbsolute("Villager Norse", p, 27, 0);
		modifyProtounitAbsolute("Villager Chinese", p, 27, 0);
		modifyProtounitAbsolute("Villager Atlantean Hero", p, 27, 0);
		modifyProtounitAbsolute("Villager Atlantean", p, 27, 0);
		
		modifyProtounitAbsolute("Villager Greek", p, 28, 0);
		modifyProtounitAbsolute("Villager Egyptian", p, 28, 0);
		modifyProtounitAbsolute("Villager Norse", p, 28, 0);
		modifyProtounitAbsolute("Villager Chinese", p, 28, 0);
		modifyProtounitAbsolute("Villager Atlantean Hero", p, 28, 0);
		modifyProtounitAbsolute("Villager Atlantean", p, 28, 0);
		
		modifyProtounitAbsolute("Villager Greek", p, 29, 0);
		modifyProtounitAbsolute("Villager Egyptian", p, 29, 0);
		modifyProtounitAbsolute("Villager Norse", p, 29, 0);
		modifyProtounitAbsolute("Villager Chinese", p, 29, 0);
		modifyProtounitAbsolute("Villager Atlantean Hero", p, 29, 0);
		modifyProtounitAbsolute("Villager Atlantean", p, 29, 0);
	}
	xsDisableSelf();
}

/*
The field ids are as follows:
Hitpoints=0
Speed=1
LOS=2
Train Points=3
Build Points=4
Max Contained=5
Population Count=6
Pop Cap Addition=7
Lifespan=8
Recharge Time=9
Build Limit=10
Range=11
Minimum Range=12
Num Projectiles=13
Healing Rate=14
Healing Range=15
Cost Gold=16
Cost Wood=17
Cost Food=18
Cost Favor=19
Carry Capacity Gold=20
Carry Capacity Wood=21
Carry Capacity Food=22
Carry Capacity Favor=23
Armor Hack=24
Armor Pierce=25
Armor Crush=26
Hand Attack Hack=27
Hand Attack Pierce=28
Hand Attack Crush=29
Ranged Attack Hack=30
Ranged Attack Pierce=31
Ranged Attack Crush=32
Movetype = 55
*/
