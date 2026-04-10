#include <iostream>
#include "Data/Setting.h"
#include "Game/GameManager.h"

int main(int argc, char* argv[])
{
	std::cerr << "process started";
	Setting setting;
	if (argc > 1 && std::string_view(argv[1]) == "--player1")
		setting.SetStartPlayer(eStartPlayer::Bot);

	GameManager gm;
	
	try
	{
		std::cerr << "game started";
		gm.Start(setting);
		return 0;
	}
	catch (const std::exception& e)
	{

		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}
	catch (...)
	{
		std::cerr << "Error: unknown exception\n";
		return 1;
	}
}