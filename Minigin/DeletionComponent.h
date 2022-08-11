#pragma once
#include "Component.h"

class DeletionComponent final : public Component
{
public:
	DeletionComponent();
	~DeletionComponent() = default;

	void SetCanDelete(bool b);
	bool GetCanDelete() const;

private:
	bool m_CanDelete;
};

