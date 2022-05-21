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

class Fire : public Command
{
public:
	virtual void Execute() override { std::cout << "\nFire!"; }
};

class Jump : public Command
{
public:
	virtual void Execute() override { std::cout << "\nJump!"; }
};

class Crouch : public Command
{
public:
	virtual void Execute() override { std::cout << "\nCrouch!"; }
};

class Die : public Command
{
public:
	virtual void Execute() override { std::cout << "\nDie!"; }
};