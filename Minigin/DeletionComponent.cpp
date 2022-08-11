#include "MiniginPCH.h"
#include "DeletionComponent.h"

DeletionComponent::DeletionComponent()
	: m_CanDelete{ false }
{
}

void DeletionComponent::SetCanDelete(bool b)
{
	m_CanDelete = b;
}

bool DeletionComponent::GetCanDelete() const
{
	return m_CanDelete;
}
