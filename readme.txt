My engine uses a component system to assign tasks to different GameObjects.
These GameObjects contain different components that then fulfill assigned tasks.
Currently it supports only multiplayer, with infinite levels.
Score is kept between levels and eventually written to a file, where you can compare it to others.
It uses the sdl mixer library to play sounds, using threading to play each file. Files that are to be played are stored in an EventQueue and played when possible.
A scenegraph takes care of the different scenes and objects in those scenes, switching between those is as simple as changing the active scene.

The game itself is in a different directory, and new games can easily be run by inheriting from the Game class in the engine.
I passed keypresses and clicks to the game, so it's easy to manipulate those even when components are not used.
Components get their parent and deltaTime passed along, so they can easily manipulate other components when necessary.

In the game itself I tried to pass as much responsibility to components as possible, to that end there's a collisionComponent that handles collision between components who contain one. The playerComponent handles player input and interactions.

Controllers are supported, but not extensively as gameplay is more focused on keyboard and mouse.

Github link: https://github.com/JorenDresselaers/Prog_4_Engine