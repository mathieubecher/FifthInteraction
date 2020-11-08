// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gravity/GravityComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/MovementComponent.h"
#include "MovementGravityAffected.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnterGravity, UGravityComponent*, NewGravity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExitGravity, UGravityComponent*, NewGravity);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIFTHINTERACTION_API UMovementGravityAffected : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UPrimitiveComponent * Physics;
	class AWorldPhysicsVolume * Volume;
public:	
	// Sets default values for this component's properties
	UMovementGravityAffected();
	UPROPERTY(BlueprintReadWrite)
	class UGravityComponent * LocalGravity;


	UPROPERTY(BlueprintAssignable)
	FEnterGravity OnEnterGravity;
	UPROPERTY(BlueprintAssignable)
	FExitGravity OnExitGravity;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	
	void EnterGravity(UGravityComponent * NewGravity);
	void ExitGravity(UGravityComponent * NewGravity);

};
