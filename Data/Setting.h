#pragma once
#include "Enum/eStartPlayer.h"


class Setting
{
public:
	void SetStartPlayer(eStartPlayer programPlayer);
	eStartPlayer GetStartPlayer() const;

private:
	eStartPlayer _programPlayer;
};

