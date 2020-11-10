// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "MovementGravityAffected.h"
#include "MovementCharacter.h"
#include "CharacterController.generated.h"

UCLASS()
class FIFTHINTERACTION_API ACharacterController : public APawn
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UMovementGravityAffected * Gravity;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UMovementCharacter * MovementCharacter;

	FRotator FreeRotation;

public:
	// Sets default values for this pawn's properties
	ACharacterController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void MoveUp(float AxisValue);

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void EnterGravity(UGravityComponent * NewGravity);
	UFUNCTION()
	void ExitGravity(UGravityComponent * NewGravity);
};
