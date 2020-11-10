// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "../MovementGravityAffected.h"
#include "../WorldPhysicsVolume.h"

// Sets default values for this component's properties
UGravityComponent::UGravityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGravityComponent::BeginPlay()
{
	Super::BeginPlay();
	AWorldPhysicsVolume * Volume = Cast<AWorldPhysicsVolume>(GetWorld()->GetDefaultPhysicsVolume());
	Volume->AddGravityComponent(this);
}	


// Called every frame
void UGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


FVector UGravityComponent::GetAttractVector(FVector Position) {
	FVector Direction = Position - GetOwner()->GetActorLocation();
	Direction.Normalize();
	if (Type == GravityType::SPHERE) return -Direction;
	else {
		float forward = FVector::DotProduct(Direction, GetOwner()->GetActorForwardVector());
		float up = FVector::DotProduct(Direction, GetOwner()->GetActorUpVector());
		float right = FVector::DotProduct(Direction, GetOwner()->GetActorRightVector());

		if (UKismetMathLibrary::Abs(forward) > UKismetMathLibrary::Abs(right) && UKismetMathLibrary::Abs(forward) > UKismetMathLibrary::Abs(up)) {
			if (forward < 0) return GetOwner()->GetActorForwardVector();
			else return GetOwner()->GetActorForwardVector() * -1;
		}
		else if (UKismetMathLibrary::Abs(up) > UKismetMathLibrary::Abs(right) && UKismetMathLibrary::Abs(up) > UKismetMathLibrary::Abs(forward)) {
			if (up < 0) return GetOwner()->GetActorUpVector();
			else return GetOwner()->GetActorUpVector() * -1;
		}
		else {
			if (right < 0) return GetOwner()->GetActorRightVector();
			else return GetOwner()->GetActorRightVector() * -1;
		}
	}
}

FVector UGravityComponent::GetGravity(FVector Position, float ActorMass)
{
	FVector Direction;
	float Distance;

	Direction = GetAttractVector(Position);
	Distance = FVector::DotProduct(Position - GetOwner()->GetActorLocation(), Direction)/100;

	float Magnitude = Mass * ActorMass / (Distance * Distance);
	return Direction * Magnitude;
}

void UGravityComponent::EnterGravity(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner()) return;

	UE_LOG(LogTemp, Log, TEXT("Hi stranger!"));
	UMovementGravityAffected * GravityAffected = (UMovementGravityAffected*)OtherActor->GetComponentByClass(UMovementGravityAffected::StaticClass());
	if (GravityAffected) GravityAffected->EnterGravity(this);
}

void UGravityComponent::ExitGravity(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){
	UMovementGravityAffected * GravityAffected = (UMovementGravityAffected*)OtherActor->GetComponentByClass(UMovementGravityAffected::StaticClass());
	if (GravityAffected) GravityAffected->ExitGravity(this);
}
