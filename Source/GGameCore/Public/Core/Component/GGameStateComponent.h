// Copyright (c) 2025 cannot206.

#pragma once

#include "Core/Component/GGameCoreComponent.h"
#include "Containers/Ticker.h"

#include "GGameStateComponent.generated.h"

class AGameStateBase;
class APlayerController;

UCLASS(Abstract, Blueprintable, BlueprintType, HideCategories = (Trigger, PhysicsVolume))
class GGAMECORE_API UGGameStateComponent : public UGGameCoreComponent
{
	GENERATED_BODY()
	
public:
	// ActorComponent
	virtual void InitializeComponent();
	virtual void UninitializeComponent();
	// ~ActorComponent

public:
	UFUNCTION(BlueprintCallable)
	AGameStateBase* GetGameState() const;

protected:
	void OnEnterPrimaryController_Internal();
	virtual void OnEnterPrimaryController() {}
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnEnterPrimaryController"))
	void K2_OnEnterPrimaryController();

public:
	UPROPERTY(Transient, BlueprintReadOnly)
	TWeakObjectPtr<APlayerController> PrimaryController;

private:
	FTSTicker::FDelegateHandle TickHandle;

};
