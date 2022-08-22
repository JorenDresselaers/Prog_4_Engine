#pragma once
#include "Component.h"

class DeletionComponent final : public Component
{
public:
	DeletionComponent();
	~DeletionComponent() = default;
	DeletionComponent(const DeletionComponent& other) = delete;
	DeletionComponent(DeletionComponent&& other) = delete;
	DeletionComponent& operator=(const DeletionComponent& other) = delete;
	DeletionComponent& operator=(DeletionComponent&& other) = delete;


	void SetCanDelete(bool b);
	bool GetCanDelete() const;

private:
	bool m_CanDelete;
};

