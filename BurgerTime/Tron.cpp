#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "TronGame.h"

int main(int, char* []) {
	dae::Minigin engine;

	TronGame* newGame = new TronGame();
	engine.SetGame(newGame);
	engine.Run();
	delete newGame;
	return 0;
}