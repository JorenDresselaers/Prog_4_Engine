My engine uses a component system to assign tasks to different GameObjects.
These GameObjects contain different components that then fulfill assigned tasks.
Currently it supports multiplayer for two people.
It uses the sdl mixer library to play sounds.
A scenegraph takes care of the different scenes and objects in those scenes, switching between those is as simple as changing the active scene.

The game itself is in a different directory, and new games can easily be run by inheriting from the Game class in the engine.

Github link: https://github.com/JorenDresselaers/Prog_4_Engine