#include <iostream>
#include "Bus/Bus.h"
#include "Clock/Clock.h"
#include <chrono>
#include "CPU/CPU.h"

#include <SDL.h>
#include "GameLoop/GameLoop.h"
#include "Screen/Screen.h"
#include "PPU/PPU.h"
#include <memory>
#include <functional>

int main(int argc, char** argv)
{
	//std::unique_ptr<Screen> pScreen = std::make_unique<Screen>(SCREEN_WIDTH, SCREEN_HEIGHT);
	Screen screen(SCREEN_WIDTH, SCREEN_HEIGHT);
	Bus bus;
	CPU cpu(&bus);
	PPU ppu(&bus, &screen);
	GameLoop gameLoop(cpu, &ppu);
	//ppu.render();
	gameLoop.startGame();

	return 0;
}