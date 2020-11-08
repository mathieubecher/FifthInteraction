// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GravityComponent.h"
#include "Components/BoxComponent.h"
#include "BoxGravityComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FIFTHINTERACTION_API UBoxGravityComponent : public UGravityComponent
{
	GENERATED_BODY()
public:
	UBoxGravityComponent();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent * BoxCollision;
	
};
