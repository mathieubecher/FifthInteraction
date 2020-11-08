// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GravityComponent.h"
#include "SphereGravityComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FIFTHINTERACTION_API USphereGravityComponent : public UGravityComponent
{
	GENERATED_BODY()
public :
	USphereGravityComponent();
protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent * SphereCollision;
};
