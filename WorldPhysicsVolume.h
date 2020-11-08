// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPhysicsVolume.h"
#include "Gravity/GravityComponent.h"
#include "WorldPhysicsVolume.generated.h"

/**
 * 
 */
UCLASS()
class FIFTHINTERACTION_API AWorldPhysicsVolume : public ADefaultPhysicsVolume
{
	GENERATED_BODY()
private :
	TArray<UGravityComponent*> Gravitys;
public :
	UFUNCTION(BlueprintCallable)
	FVector GetGravity(AActor * Actor, float Mass);
	virtual void BeginPlay() override;
	void AddGravityComponent(UGravityComponent * Gravity);
};
