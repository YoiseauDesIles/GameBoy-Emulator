#include "GameLoop.h"

GameLoop::GameLoop(CPU & cpu)
	:mCPU(cpu)
{
}

void GameLoop::startGame()
{
	Uint64 frameStart;
	Uint64 frameEnd;

	int cycles = 0;

	// frameStart
	frameStart = SDL_GetPerformanceCounter();
	mIsRunning = true;
	int cnt = 0;

	while (mIsRunning)
	{
		while (cycles < cyclesPerFrame)
		{
			//TODO Faire une methode qui gere tous les processus du CPU par frame
			u8 currCycle = mCPU.executeOpcode(0x01);
			mCPU.callInterruptHandler();
			cycles += currCycle;
		}
		std::cout << "Nombre d'instructions : " << cycles / 4 << std::endl; 
		std::cout << "Nombre de cycles : " << cycles << std::endl; 

		cycles -= cyclesPerFrame;

		std::cout << "Nombre de cycles apr�s reset : " << cycles << std::endl;


		frameEnd = SDL_GetPerformanceCounter();

		while (true)
		{
			frameEnd = SDL_GetPerformanceCounter();
			double frameElapsedInSec = (double)(frameEnd - frameStart) / SDL_GetPerformanceFrequency();

			if (frameElapsedInSec >= timePerFrame)
			{
				std::cout << "frameElapsedInSec" << frameElapsedInSec << "\n";
				cnt++;
				break;
			}
		}

		frameStart = frameEnd;

		if (cnt >= 60)
		{
			std::cout << "fin du programme" << "\n";
			break;
		}

		

	}
}