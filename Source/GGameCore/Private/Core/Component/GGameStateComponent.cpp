// Copyright (c) 2025 cannot206.

#include "Core/Component/GGameStateComponent.h"
// include Engine
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GGameStateComponent)

void UGGameStateComponent::InitializeComponent()
{
	Super::InitializeComponent();

	auto World = GetWorld();
	if (!World)
	{
		return;
	}

	for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* NextPlayer = Iterator->Get();
		if (NextPlayer && NextPlayer->PlayerState && NextPlayer->IsPrimaryPlayer() && NextPlayer->PlayerState->GetUniqueId().IsValid())
		{
			PrimaryController = NextPlayer;
			break;
		}
	}

	if (PrimaryController.IsValid())
	{
		OnEnterPrimaryController_Internal();
	}
	else
	{
		TickHandle = FTSTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateWeakLambda(
				this, [this, ThisPtr = TWeakObjectPtr<UGGameStateComponent>(this)](float DeltaTime) -> bool {
					if (!ThisPtr.IsValid())
					{
						return false;
					}

					auto World = GetWorld();
					if (!World)
					{
						if (TickHandle.IsValid())
						{
							TickHandle.Reset();
						}
						return false;
					}

					for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
					{
						APlayerController* NextPlayer = Iterator->Get();
						if (NextPlayer && NextPlayer->PlayerState && NextPlayer->IsPrimaryPlayer() && NextPlayer->PlayerState->GetUniqueId().IsValid())
						{
							PrimaryController = NextPlayer;
							TickHandle.Reset();
							OnEnterPrimaryController_Internal();
							return false;
						}
					}

					return true;
				}
			)
		);
	}
}

void UGGameStateComponent::UninitializeComponent()
{
	Super::UninitializeComponent();

	if (TickHandle.IsValid())
	{
		TickHandle.Reset();
	}
}

AGameStateBase* UGGameStateComponent::GetGameState() const
{
	return Cast<AGameStateBase>(GetOwner());
}

void UGGameStateComponent::OnEnterPrimaryController_Internal()
{
	OnEnterPrimaryController();
	K2_OnEnterPrimaryController();
}
