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
					dialog = 0;
				}
				case 2:
				{
					dialog = 0;
					trShowChoiceDialog("Do you know how to do this?", "Yes", 18, "No", 19);
				}
			}
		}
		case 4:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("Great! Now make it to the end line and we can begin.");
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
