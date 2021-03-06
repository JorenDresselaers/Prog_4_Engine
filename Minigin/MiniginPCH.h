#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma warning(push, 0)
//disabling a warning in the sdl library because of level 4 warning level
#pragma warning( disable : 26812; disable : 4201 )
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)

