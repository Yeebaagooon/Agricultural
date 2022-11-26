rule EndC01
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		xsDisableSelf();
		//trLetterBox(false);
		trUIFadeToColor(0,0,0,1000,200,false);
		xsEnableRule("ProfitChat");
		playSound("cinematics\22_out\music (wussy mix).mp3");
		//	trPaintTerrain(0,0,MapSize,MapSize,5,4,false);
	}
}

rule EndCThird
inactive
highFrequency
{
	xsDisableSelf();
	trCameraCut(vector(6.148290,18.263809,-27.566420), vector(0.003350,-0.167604,0.985849), vector(0.000570,0.985855,0.167603), vector(0.999994,0.000000,-0.003398));
	if(tie3 > 0){
		if(tie3 == 1){
			for(p = 1; <= cNumberNonGaiaPlayers){
				if(p != ThirdPlacePlayer){
					if(1*trQuestVarGet("P"+p+"Place") == 3){
						TiePlayer = p;
					}
				}
			}
			characterDialog("Tie for third place - " +1*trQuestVarGet("P"+ThirdPlacePlayer+"Points") + " points", ""+trStringQuestVarGet("p"+ThirdPlacePlayer+"name") + " and " +trStringQuestVarGet("p"+TiePlayer+"name"), "");
			trUnitSelectByQV("ThirdPlace");
			trMutateSelected(kbGetProtoUnitID("Cinematic Block"));
			FloatingUnit("Hoplite", 7,12,8 ,180, 1,1,1);
			trUnitSelectByQV("QVRelic");
			trUnitConvert(TiePlayer);
			trUnitSelectByQV("QVRelic");
			xSetPointer(dPlayerData, TiePlayer);
			trMutateSelected(kbGetProtoUnitID(""+SkinProto(xGetInt(dPlayerData, xSkin))));
			FloatingUnit("Hoplite", 9,12,8 ,180, 1,1,1);
			trUnitSelectByQV("QVRelic");
			trUnitConvert(ThirdPlacePlayer);
			trUnitSelectByQV("QVRelic");
			xSetPointer(dPlayerData, ThirdPlacePlayer);
			trMutateSelected(kbGetProtoUnitID(""+SkinProto(xGetInt(dPlayerData, xSkin))));
		}
		characterDialog("Multiple tie for third place - " +1*trQuestVarGet("P"+ThirdPlacePlayer+"Points") + " points", " ", "");
	}
	else{
		//run
		OverlayTextPlayerColor(ThirdPlacePlayer);
		trOverlayText("3rd Place: "+trStringQuestVarGet("p"+ThirdPlacePlayer+"name"), 4, 545, 30, 1000);
		characterDialog(""+1*trQuestVarGet("P"+ThirdPlacePlayer+"Points") + " points", "", "");
		trUnitSelectByQV("ThirdPlace");
		trUnitConvert(ThirdPlacePlayer);
		trUnitSelectByQV("ThirdPlace");
		xSetPointer(dPlayerData, ThirdPlacePlayer);
		trMutateSelected(kbGetProtoUnitID(""+SkinProto(xGetInt(dPlayerData, xSkin))));
	}
	xsEnableRule("FireSecond");
}

rule FireSecond
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		xsDisableSelf();
		xsEnableRule("EndCSecond");
	}
}

rule EndCSecond
inactive
highFrequency
{
	xsDisableSelf();
	trCameraCut(vector(40.951347,21.263809,-26.724661), vector(0.003350,-0.167604,0.985849), vector(0.000570,0.985855,0.167603), vector(0.999994,0.000000,-0.003398));
	if(tie2 > 0){
		if(tie2 == 1){
			for(p = 1; <= cNumberNonGaiaPlayers){
				if(p != SecondPlacePlayer){
					if(1*trQuestVarGet("P"+p+"Place") == 2){
						TiePlayer = p;
					}
				}
			}
			characterDialog("Tie for second place - " +1*trQuestVarGet("P"+SecondPlacePlayer+"Points") + " points", ""+trStringQuestVarGet("p"+SecondPlacePlayer+"name") + " and " +trStringQuestVarGet("p"+TiePlayer+"name"), "");
			trUnitSelectByQV("SecondPlace");
			trMutateSelected(kbGetProtoUnitID("Cinematic Block"));
			FloatingUnit("Hoplite", 7,12,8 ,180, 1,1,1);
			trUnitSelectByQV("QVRelic");
			trUnitConvert(TiePlayer);
			trUnitSelectByQV("QVRelic");
			xSetPointer(dPlayerData, TiePlayer);
			trMutateSelected(kbGetProtoUnitID(""+SkinProto(xGetInt(dPlayerData, xSkin))));
			FloatingUnit("Hoplite", 9,12,8 ,180, 1,1,1);
			trUnitSelectByQV("QVRelic");
			trUnitConvert(SecondPlacePlayer);
			trUnitSelectByQV("QVRelic");
			xSetPointer(dPlayerData, SecondPlacePlayer);
			trMutateSelected(kbGetProtoUnitID(""+SkinProto(xGetInt(dPlayerData, xSkin))));
		}
		characterDialog("Multiple tie for second place - " +1*trQuestVarGet("P"+SecondPlacePlayer+"Points") + " points", " ", "");
	}
	else{
		//run
		OverlayTextPlayerColor(SecondPlacePlayer);
		trOverlayText("2nd Place: "+trStringQuestVarGet("p"+SecondPlacePlayer+"name"), 4, 545, 30, 1000);
		characterDialog(""+1*trQuestVarGet("P"+SecondPlacePlayer+"Points") + " points", "", "");
		xsEnableRule("FireFirst");
		trUnitSelectByQV("SecondPlace");
		trUnitConvert(SecondPlacePlayer);
		trUnitSelectByQV("SecondPlace");
		xSetPointer(dPlayerData, SecondPlacePlayer);
		trMutateSelected(kbGetProtoUnitID(""+SkinProto(xGetInt(dPlayerData, xSkin))));
	}
}

rule FireFirst
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		xsDisableSelf();
		xsEnableRule("EndCFirst");
	}
}

rule EndCFirst
inactive
highFrequency
{
	xsDisableSelf();
	trCameraCut(vector(23.205647,24.203808,-27.564360), vector(0.003350,-0.167604,0.985849), vector(0.000570,0.985854,0.167603), vector(0.999994,-0.000000,-0.003398));
	if(tie1 > 0){
		debugLog("Tie for First");
	}
	else{
		//run
		OverlayTextPlayerColor(FirstPlacePlayer);
		trOverlayText("1st Place: "+trStringQuestVarGet("p"+FirstPlacePlayer+"name"), 5, 545, 30, 1000);
		characterDialog(""+1*trQuestVarGet("P"+FirstPlacePlayer+"Points") + " points", "", "");
		xsEnableRule("FinishTrack");
		trUnitSelectByQV("FirstPlace");
		trUnitConvert(FirstPlacePlayer);
		trUnitSelectByQV("FirstPlace");
		xSetPointer(dPlayerData, FirstPlacePlayer);
		trMutateSelected(kbGetProtoUnitID(""+SkinProto(xGetInt(dPlayerData, xSkin))));
	}
}

rule FinishTrack
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		xsDisableSelf();
		createCameraTrack(5000);
		trCameraCut(vector(23.205647,24.203808,-27.564360), vector(0.003350,-0.167604,0.985849), vector(0.000570,0.985854,0.167603), vector(0.999994,-0.000000,-0.003398));
		addCameraTrackWaypoint();
		trCameraCut(vector(23.701241,30.623808,-88.526428), vector(0.003350,-0.167604,0.985849), vector(0.000570,0.985855,0.167603), vector(0.999994,0.000000,-0.003398));
		addCameraTrackWaypoint();
		playCameraTrack();
		xsEnableRule("EndGame_MP_01");
		characterDialog(" ", " ", "");
	}
}

rule EndGame_MP_01
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		xsDisableSelf();
		trLetterBox(false);
		xsEnableRule("EndGame_MP_02");
		createCameraTrack(5000);
		trCameraCut(vector(23.701241,30.623808,-88.526428), vector(0.003350,-0.167604,0.985849), vector(0.000570,0.985855,0.167603), vector(0.999994,0.000000,-0.003398));
		addCameraTrackWaypoint();
		trCameraCut(vector(23.701241,30.623808,-88.526428), vector(0.003350,-0.167604,0.985849), vector(0.000570,0.985855,0.167603), vector(0.999994,0.000000,-0.003398));
		addCameraTrackWaypoint();
		playCameraTrack();
		
		for(p = 1; <= cNumberNonGaiaPlayers){
			trQuestVarSet("P"+p+"Place",1);
		}
		for(p = 1; <= cNumberNonGaiaPlayers){
			for(x = 1; <= cNumberNonGaiaPlayers){
				if(1*trQuestVarGet("P"+p+"Points") < 1*trQuestVarGet("P"+x+"Points")){
					trQuestVarModify("P"+p+"Place", "+", 1);
				}
			}
		}
		trChatSend(0, "<color=1,0.5,0><u>Scores:</u></color>");
		for(x = 1; <= cNumberNonGaiaPlayers){
			for(p = 1; <= cNumberNonGaiaPlayers){
				if(1*trQuestVarGet("P"+p+"Place") == x){
					if(x == 1){
						trChatSend(0, "<color={PlayerColor("+p+")}><icon=(20)(icons/star)> {Playername("+p+")} - "+1*trQuestVarGet("P"+p+"Points")+"");
					}
					else{
						trChatSend(0, "<color={PlayerColor("+p+")}>{Playername("+p+")} - "+1*trQuestVarGet("P"+p+"Points")+"");
					}
				}
			}
		}
	}
}

rule EndGame_MP_02
inactive
highFrequency
{
	if (trTime() > cActivationTime + 1) {
		createCameraTrack(5000);
		trCameraCut(vector(23.701241,30.623808,-88.526428), vector(0.003350,-0.167604,0.985849), vector(0.000570,0.985855,0.167603), vector(0.999994,0.000000,-0.003398));
		addCameraTrackWaypoint();
		trCameraCut(vector(23.701241,30.623808,-88.526428), vector(0.003350,-0.167604,0.985849), vector(0.000570,0.985855,0.167603), vector(0.999994,0.000000,-0.003398));
		addCameraTrackWaypoint();
		playCameraTrack();
		for(p = 1; <= cNumberNonGaiaPlayers){
			if(p != FirstPlacePlayer){
				//loser
				trSetPlayerDefeated(p);
			}
			else if(p == FirstPlacePlayer){
				trSetPlayerWon(p);
			}
		}
		xsDisableSelf();
		trEndGame();
	}
}

rule ThirdNormal_01
inactive
highFrequency
{
	xsDisableSelf();
}

rule ProfitChat
inactive
highFrequency
{
	for(p = 1; <= cNumberNonGaiaPlayers){
		trQuestVarSet("P"+p+"Place",1);
	}
	for(p = 1; <= cNumberNonGaiaPlayers){
		for(x = 1; <= cNumberNonGaiaPlayers){
			if(1*trQuestVarGet("P"+p+"Points") < 1*trQuestVarGet("P"+x+"Points")){
				trQuestVarModify("P"+p+"Place", "+", 1);
			}
		}
	}
	/*
	trChatSend(0, "<color=1,0.5,0><u>Scores:</u></color>");
	for(x = 1; <= cNumberNonGaiaPlayers){
		for(p = 1; <= cNumberNonGaiaPlayers){
			if(1*trQuestVarGet("P"+p+"Place") == x){
				if(x == 1){
					trChatSend(0, "<color={PlayerColor("+p+")}><icon=(20)(icons/star)> {Playername("+p+")} - "+1*trQuestVarGet("P"+p+"Points")+"");
				}
				else{
					trChatSend(0, "<color={PlayerColor("+p+")}>{Playername("+p+")} - "+1*trQuestVarGet("P"+p+"Points")+"");
				}
			}
		}
	}
	*/
	for(p = 1; <= cNumberNonGaiaPlayers){
		if(1*trQuestVarGet("P"+p+"Place") == 1){
			tie1 = tie1 + 1;
			FirstPlacePlayer = p;
		}
		if(1*trQuestVarGet("P"+p+"Place") == 2){
			tie2 = tie2 + 1;
			SecondPlacePlayer = p;
		}
		if(1*trQuestVarGet("P"+p+"Place") == 3){
			tie3 = tie3 + 1;
			ThirdPlacePlayer = p;
		}
	}
	if(tie1 > 0){
		debugLog("Tie for first");
	}
	if(tie2 > 0){
		debugLog("Tie for second");
	}
	if(tie3 > 0){
		debugLog("Tie for third");
	}
	if(tie3 < 0){
		debugLog("No third");
	}
	xsDisableSelf();
	xsEnableRule("BuildFirst");
	trCameraCut(vector(23.701241,30.623808,-88.526428), vector(0.003350,-0.167604,0.985849), vector(0.000570,0.985855,0.167603), vector(0.999994,0.000000,-0.003398));
	trRenderSky(true, "SkySunset");
	if(tie3 != -1){
		xsEnableRule("EndCThird");
		xsEnableRule("BuildThird");
		xsEnableRule("BuildSecond");
	}
	else{
		xsEnableRule("BuildSecond");
		xsEnableRule("EndCSecond");
	}
}

rule BuildThird
inactive
highFrequency
{
	xsDisableSelf();
	int temp = 0;
	for(x=1 ; <= 2){
		for(z=1 ; <= 2){
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Cinematic Block", x*4, z*4, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Wall Connector");
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitSetAnimationPath("1,2,0,0,0,0");
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trSetSelectedScale(1,1.5,1);
		}
	}
	FloatingUnitAnimIdle("Wall Connector", 8,11.5,8 ,0, 2.8,0.1,2.8);
	trUnitSelectClear();
	trUnitSelectByQV("QVHero");
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("1,2,0,0,0,0");
	FloatingUnitAnimIdle("Columns", 8,12,10 ,180, 5,1,1);
	trUnitSelectClear();
	trUnitSelectByQV("QVHero");
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("1,0,0,0,0,0");
	//Main unit
	FloatingUnitAnimIdle("Hoplite", 8,12,8 ,180, 1,1,1);
	trQuestVarSet("ThirdPlace", 1*trQuestVarGet("QVRelic"));
}

rule BuildSecond
inactive
highFrequency
{
	xsDisableSelf();
	int temp = 0;
	for(x=1 ; <= 2){
		for(z=1 ; <= 2){
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Cinematic Block", x*4+35, z*4, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Columns");
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitSetAnimationPath("2,0,0,0,0,0");
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trSetSelectedScale(2,3,2);
		}
		FloatingUnitAnimIdle("Torch", x*4+36,13,5.5 ,180, 1,1,1);
		trUnitSelectClear();
		trUnitSelectByQV("QVHero");
		trUnitSelectByQV("QVRelic");
		trUnitSetAnimationPath("2,1,0,0,0,0");
		FloatingUnitAnimIdle("Torch", x*4+36,13,9 ,180, 1,1,1);
		trUnitSelectClear();
		trUnitSelectByQV("QVHero");
		trUnitSelectByQV("QVRelic");
		trUnitSetAnimationPath("2,0,0,0,0,0");
	}
	FloatingUnitAnimIdle("Wall Connector", 42,14,8 ,0, 2.8,0.1,2.8);
	trUnitSelectClear();
	trUnitSelectByQV("QVHero");
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("2,1,0,0,0,0");
	FloatingUnitAnimIdle("Columns", 42,14.5,10 ,180, 5,1,1);
	trUnitSelectClear();
	trUnitSelectByQV("QVHero");
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("2,0,0,0,0,0");
	//Main unit
	FloatingUnitAnimIdle("Hoplite", 42,14.5,8 ,180, 1,1,1);
	trQuestVarSet("SecondPlace", 1*trQuestVarGet("QVRelic"));
}

rule BuildFirst
inactive
highFrequency
{
	xsDisableSelf();
	int temp = 0;
	for(x=1 ; <= 3){
		for(z=1 ; <= 3){
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Cinematic Block", x*2+18, z*2+2, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Wall Connector");
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitSetAnimationPath("0,2,0,0,0,0");
		}
	}
	for(x=1 ; <= 2){
		for(z=1 ; <= 2){
			FloatingUnitAnimIdle("Wall Connector", x*4+18,7.5,z*4+2 ,0, 1,1,1);
			trUnitSelectClear();
			trUnitSelectByQV("QVHero");
			trUnitSelectByQV("QVRelic");
			trUnitSetAnimationPath("0,3,0,0,0,0");
			FloatingUnitAnimIdle("Outpost", x*4+18,7.5,z*4+2 ,0, 1,1,1);
			FloatingUnitAnimIdle("Columns", x*4+18,15.5,z*4+2 ,0, 1,1,1);
			FloatingUnitAnimIdle("Tower Mirror", x*4+18,19.5,z*4+2 ,0, 0,0,0);
			FloatingUnitAnimIdle("Valkyrie", x*4+18,19.5,z*4+2 ,0, 0,0,0);
			FloatingUnitAnimIdle("Garrison Flag Sky Passage", x*4+18,19.5,z*4+2 ,0, 0,0,0);
			FloatingUnitAnimIdle("Obelisk", 24,7.5,z*4+2 ,0, 1,1,1);
			trUnitSelectClear();
			trUnitSelectByQV("QVHero");
			trUnitSelectByQV("QVRelic");
			trUnitSetAnimationPath("2,0,0,0,0,0");
		}
		FloatingUnitAnimIdle("Obelisk", x*4+18,7.5,8 ,0, 1,1,1);
		trUnitSelectClear();
		trUnitSelectByQV("QVHero");
		trUnitSelectByQV("QVRelic");
		trUnitSetAnimationPath("2,0,0,0,0,0");
	}
	
	FloatingUnitAnimIdle("Wall Connector", 24,18,8 ,0, 2.8,0.1,2.8);
	trUnitSelectClear();
	trUnitSelectByQV("QVHero");
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("0,1,0,0,0,0");
	FloatingUnitAnimIdle("Columns", 24,18.5,10 ,180, 5,1,1);
	trUnitSelectClear();
	trUnitSelectByQV("QVHero");
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("0,0,0,0,0,0");
	//Main unit
	FloatingUnitAnimIdle("Hoplite", 24,18.5,8 ,180, 1,1,1);
	trQuestVarSet("FirstPlace", 1*trQuestVarGet("QVRelic"));
	
}

/*
ALL
trCameraCut(vector(23.701241,30.623808,-88.526428), vector(0.003350,-0.167604,0.985849), vector(0.000570,0.985855,0.167603), vector(0.999994,0.000000,-0.003398));

3   trCameraCut(vector(6.148290,18.263809,-27.566420), vector(0.003350,-0.167604,0.985849), vector(0.000570,0.985855,0.167603), vector(0.999994,0.000000,-0.003398));
2     trCameraCut(vector(40.951347,21.263809,-26.724661), vector(0.003350,-0.167604,0.985849), vector(0.000570,0.985855,0.167603), vector(0.999994,0.000000,-0.003398));
1    trCameraCut(vector(23.205647,24.203808,-27.564360), vector(0.003350,-0.167604,0.985849), vector(0.000570,0.985854,0.167603), vector(0.999994,-0.000000,-0.003398));
*/
