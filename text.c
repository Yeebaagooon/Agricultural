/*
Set up the numbers corresponding to dialogs
const int NPC_RELIC_TRANSPORTER = 0;
const int NPC_RELIC_TRANSPORTER_WTF = 1;
*/
void startNPCDialog(int npc = 0) {
	if (trQuestVarGet("currentNPCProgress") == 0) {
		xsEnableRule("npc_talk_01");
		trQuestVarSet("currentNPC", npc);
		trQuestVarSet("currentNPCProgress", 0);
	}
}

int npcDiag(int npc = 0, int dialog = 0) {
	dialog = dialog + 1;
	string extra = "";
	int p = 0;
	switch(npc)
	{
		case 1:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("Launching this map in singleplayer requires no AI players.");
				}
				case 2:
				{
					dialog = 0;
					trShowChoiceDialog("Do you know how to do this?", "Yes", 18, "No", 19);
				}
			}
		}
		case 2:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("On the random map screen you will see a 'Customize Opponents' button.");
				}
				case 2:
				{
					uiMessageBox("Click this and make sure all slots are set to 'Closed'.");
				}
				case 3:
				{
					uiMessageBox("Then press ok and relaunch this map.");
				}
				case 4:
				{
					dialog = 0;
					modeEnter("Campaign");
					modeEnter("Pregame");
				}
				
			}
		}
		case 3:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("In singeplayer mode you can select skins to use online.");
					trCameraCut(vector(99.460289,251.724258,-217.012619), vector(0.004524,-0.707107,0.707092), vector(0.004524,0.707106,0.707093), vector(0.999980,0.000000,-0.006398));
				}
				case 2:
				{
					uiMessageBox("The first row charts your online wins.");
					trCameraCut(vector(19.760197,56.723843,-41.718472), vector(0.004524,-0.707107,0.707092), vector(0.004524,0.707107,0.707093), vector(0.999980,0.000000,-0.006398));
				}
				case 3:
				{
					uiMessageBox("You gain a pip for every win.");
					trCameraCut(vector(9.784211,17.783848,-6.673924), vector(0.004524,-0.707107,0.707092), vector(0.004524,0.707107,0.707093), vector(0.999980,0.000000,-0.006398));
				}
				case 4:
				{
					//RELEASE
					uiMessageBox("And can equip any skin with UNLOCK.");
					trCameraCut(vector(6.937281,13.763847,-1.495604), vector(0.004524,-0.707107,0.707092), vector(0.004524,0.707107,0.707093), vector(0.999980,0.000000,-0.006398));
				}
				case 5:
				{
					uiMessageBox("The second row charts your maximum single point score.");
					trCameraCut(vector(40.844231,43.943848,-28.653074), vector(0.005213,-0.579731,0.814791), vector(0.003709,0.814808,0.579719), vector(0.999980,0.000000,-0.006398));
				}
				case 6:
				{
					uiMessageBox("This is the number of points you receive from a wall connector/relic.");
					trCameraCut(vector(40.844231,43.943848,-28.653074), vector(0.005213,-0.579731,0.814791), vector(0.003709,0.814808,0.579719), vector(0.999980,0.000000,-0.006398));
					
				}
				case 7:
				{
					uiMessageBox("The third row charts your personal best score.");
					trCameraCut(vector(29.957218,43.943848,-4.702938), vector(0.005213,-0.579731,0.814791), vector(0.003709,0.814808,0.579719), vector(0.999980,0.000000,-0.006398));
					
				}
				case 8:
				{
					uiMessageBox("The final row has some more unique conditions.");
					trCameraCut(vector(24.138248,43.943848,14.234679), vector(0.005213,-0.579731,0.814791), vector(0.003709,0.814808,0.579719), vector(0.999980,0.000000,-0.006398));
					
				}
				case 9:
				{
					uiMessageBox("Click a unit to equip it or find out how to unlock it!");
					trCameraCut(vector(23.398306,123.743713,-101.420784), vector(0.004524,-0.707107,0.707092), vector(0.004524,0.707107,0.707093), vector(0.999980,0.000000,-0.006398));
					dialog = 0;
					xSetPointer(dPlayerData, 1);
					xSetInt(dPlayerData, xSeenSP, 1);
					saveAllData();
				}
			}
		}
		case 4:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("This skin is locked! You need to play Yeebaagooon's Motherload map to unlock.");
				}
				case 2:
				{
					uiMessageBox("Subscribe to Motherload on the steam workshop.");
					dialog = 0;
				}
			}
		}
		case 5:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("This skin is locked! You need to defeat Mr. Natas in Motherload to unlock.");
				}
				case 2:
				{
					uiMessageBox("Subscribe to Motherload on the steam workshop.");
					dialog = 0;
				}
			}
		}
		case 6:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("This skin is locked! You need to win a sudden death round to unlock.");
				}
				case 2:
				{
					uiMessageBox("To trigger sudden death - tie for 1st place.");
					dialog = 0;
				}
			}
		}
		case 7:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("This skin is locked! You need 100 percent completion in Motherload to unlock.");
				}
				case 2:
				{
					uiMessageBox("Subscribe to Motherload on the steam workshop.");
					dialog = 0;
				}
			}
		}
		case 8:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("This skin is locked! You need to win Ascension MMORPG to unlock.");
				}
				case 2:
				{
					uiMessageBox("Subscribe to Ascension on the steam workshop.");
					dialog = 0;
				}
			}
		}
		case 9:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("This skin is locked! You need to win Ascension MMORPG to unlock.");
				}
				case 2:
				{
					uiMessageBox("Subscribe to Ascension on the steam workshop.");
					dialog = 0;
				}
			}
		}
		
	}
	return(dialog);
}

rule npc_talk_01
inactive
highFrequency
{
	xsDisableSelf();
	trQuestVarSet("currentNPCProgress",
		npcDiag(1*trQuestVarGet("currentNPC"), 1*trQuestVarGet("currentNPCProgress")));
	if (trQuestVarGet("currentNPCProgress") > 0) {
		trDelayedRuleActivation("npc_talk_02");
	}
}

rule npc_talk_02
inactive
highFrequency
{
	if ((trQuestVarGet("currentNPCProgress") > 0) &&
		(trIsGadgetVisible("ingame-messagedialog") == false) &&
		(trIsGadgetVisible("ShowImageBox") == false)) {
		trDelayedRuleActivation("npc_talk_01");
		xsDisableSelf();
	}
}
