//#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "BurgerTimeGame.h"

int main(int, char* []) {
	dae::Minigin engine;

	BurgerTimeGame* newGame = new BurgerTimeGame();
	engine.SetGame(newGame);
	engine.Run();
	return 0;
}