#pragma once
struct SDL_Window;
class GameObject;
class Game;
namespace dae
{
	class Minigin final
	{
	public:
		void Initialize();
		bool SetGame(Game* newGame);
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		Game* m_Game{};

		//GameObject* m_Pepper;
	};
}