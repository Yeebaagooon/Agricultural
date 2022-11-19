rule RoundStart
highFrequency
inactive
{
	if (trTime() > cActivationTime + 3) {
		trOverlayText("GO!" , 2.0, 608, 300, 1000);
		for(p=1; <= cNumberNonGaiaPlayers) {
			trUnitSelectClear();
			trUnitSelectByQV("P"+p+"Farmer");
			trUnitConvert(p);
		}
		xsDisableSelf();
		playSound("cinematics\15_in\gong.wav");
	}
}
