// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementCharacter.h"
#include "MovementGravityAffected.h"


void UMovementCharacter::BeginPlay() {

	UMovementGravityAffected * MovementGravityAffected = GetOwner()->FindComponentByClass<UMovementGravityAffected>();
	MovementGravityAffected->OnReceiveImpulse.AddDynamic(this, &UMovementCharacter::ReceiveImpulse);
}

void UMovementCharacter::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	FHitResult Hit;
	SafeMoveUpdatedComponent(GravityInertia, UpdatedComponent->GetComponentRotation(), true, Hit);
	if (Hit.IsValidBlockingHit())
	{
		GravityInertia = ComputeSlideVector(GravityInertia, 1.f - Hit.Time, Hit.Normal, Hit);
		SlideAlongSurface(GravityInertia, 1.f - Hit.Time, Hit.Normal, Hit);
	}
}

void UMovementCharacter::ReceiveImpulse(const FVector &Impulse) {
	GravityInertia += Impulse;
}