// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FifthInteractionPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FIFTHINTERACTION_API AFifthInteractionPlayerController : public APlayerController
{
	GENERATED_BODY()

protected :
	FQuat Rotation;
public:
	virtual void AddPitchInput(float Val) override;
	virtual void AddRollInput(float Val) override;
	virtual void AddYawInput(float Val) override;

};
