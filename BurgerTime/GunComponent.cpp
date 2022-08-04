#include "GunComponent.h"
//#include "SceneManager.h"
//#include "InputManager.h"
#include "GameObject.h"
#include "SDL.h"
#include "BulletComponent.h"

using namespace dae;

GunComponent::GunComponent()
{
}

GunComponent::~GunComponent()
{
}

void GunComponent::Update(float deltaTime)
{
	(void)deltaTime;
	int* x{};
	int* y{};
	SDL_GetMouseState(x, y);
}

void GunComponent::Render() const
{
}

void GunComponent::Shoot(float x, float y)
{
	(void)x;
	(void)y;
	auto newBullet = std::make_shared<GameObject>();
	//newBullet->AddComponent<BulletComponent>()->Initialize(x, y, 10, 10);
}
