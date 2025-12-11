// Copyright (c) 2025 cannot206.

#include "Core/Component/GGameModeComponent.h"
// include Engine
#include "GameFramework/GameModeBase.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GGameModeComponent)

AGameModeBase* UGGameModeComponent::GetGameMode() const
{
	return Cast<AGameModeBase>(GetOwner());
}
