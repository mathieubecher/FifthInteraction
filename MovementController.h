// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MovementController.generated.h"


UCLASS()
class FIFTHINTERACTION_API UMovementController : public UPawnMovementComponent
{
	GENERATED_BODY()


public : 
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void ReceiveImpulse(const FVector & Impulse);
	FVector GravityInertia;
};
