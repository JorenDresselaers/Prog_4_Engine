#pragma once
#include <iostream>

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;
	virtual void Execute() = 0;

private:

};

class DebugFire : public Command
{
public:
	virtual void Execute() override { std::cout << "\nFire!"; }
};

class DebugJump : public Command
{
public:
	virtual void Execute() override { std::cout << "\nJump!"; }
};

class DebugCrouch : public Command
{
public:
	virtual void Execute() override { std::cout << "\nCrouch!"; }
};

class DebugDie : public Command
{
public:
	virtual void Execute() override { std::cout << "\nDie!"; }
};