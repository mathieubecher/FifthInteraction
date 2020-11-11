// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementController.h"
#include "MovementGravityAffected.h"
#include "DrawDebugHelpers.h"


void UMovementController::BeginPlay() {

	UMovementGravityAffected * MovementGravityAffected = GetOwner()->FindComponentByClass<UMovementGravityAffected>();
	MovementGravityAffected->OnReceiveImpulse.AddDynamic(this, &UMovementController::ReceiveImpulse);
}

void UMovementController::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	FHitResult Hit;
	SafeMoveUpdatedComponent(GravityInertia, UpdatedComponent->GetComponentRotation(), true, Hit);


	if (Hit.IsValidBlockingHit())
	{
		GravityInertia = ComputeSlideVector(GravityInertia, 1.f - Hit.Time, Hit.Normal, Hit);
	}


	// IGNORE LE PERSONNAGE, VARIABLE A METTRE PROBABLEMENT EN PROTECTED QUELQUE PART
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	
	FVector Up = PawnOwner->GetActorUpVector();
	FVector Forward = PawnOwner->GetActorForwardVector();
	FVector Right = PawnOwner->GetActorRightVector();

	if (GetWorld()->LineTraceSingleByChannel(Hit, PawnOwner->GetActorLocation() + -Up, PawnOwner->GetActorLocation() + -Up * 60 /*DISTANCE A PARTIR DU CENTRE DU PERSO OU ON CONSIDERE QUE C'EST LE SOL*/, ECC_WorldStatic, CollisionParams)) {
		Hit.ImpactNormal.Normalize();
		
		//DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(), PawnOwner->GetActorLocation() + Hit.Normal * 20 , FColor::Blue, false, 2, 0, 1);
		
		// SI LA NORMAL DE LA SURFACE EST SUFFISAMENT HORIZONTALE POUR MARCHER DESSUS
		if (FVector::DotProduct(Hit.ImpactNormal, Up) > 0.7f) {
			Up = Hit.ImpactNormal;
		}
		Forward = FVector::CrossProduct(PawnOwner->GetActorRightVector(), Up);
		Right = FVector::CrossProduct(Up, Forward);

		//DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(), PawnOwner->GetActorLocation() + Forward * 20, FColor::Emerald, false, 2, 0, 1);
		//DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(), PawnOwner->GetActorLocation() + Right * 20, FColor::Red, false, 2, 0, 1);
	}

	// RECUPERATION DES INPUTS
	FVector DesiredMovementThisFrame = ConsumeInputVector();
	FVector DirectionnalMove = (DesiredMovementThisFrame.X * Forward +
		DesiredMovementThisFrame.Y * Right +
		DesiredMovementThisFrame.Z * PawnOwner->GetActorUpVector()) * 500 * DeltaTime;

	// ET MAINTENANT ON BOUGE!
	SafeMoveUpdatedComponent(DirectionnalMove, UpdatedComponent->GetComponentRotation(), true, Hit);
	if (Hit.IsValidBlockingHit())
	{
		SlideAlongSurface(DirectionnalMove, 1.f - Hit.Time, Hit.Normal, Hit);
	}

}

void UMovementController::ReceiveImpulse(const FVector &Impulse) {
	GravityInertia += Impulse;
}