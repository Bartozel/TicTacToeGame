#include "Setting.h"

void Setting::SetStartPlayer(eStartPlayer programPlayer)
{
	_programPlayer = programPlayer;
}

eStartPlayer Setting::GetStartPlayer() const
{
	return _programPlayer;
}
