// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementGravityAffected.h"
#include "WorldPhysicsVolume.h"

// Sets default values for this component's properties
UMovementGravityAffected::UMovementGravityAffected()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}
void UMovementGravityAffected::BeginPlay() {
	Physics = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	IsPhysics = (Physics && Physics->IsSimulatingPhysics());
	if (IsPhysics) Mass = Physics->GetMass();
	Volume = Cast<AWorldPhysicsVolume>(GetWorld()->GetDefaultPhysicsVolume());
}

// Called every frame
void UMovementGravityAffected::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Ignore) return;
	

	FVector Impulse;
	if (LocalGravity) Impulse = LocalGravity->GetGravity(GetOwner()->GetActorLocation(), Mass);
	else Impulse = Volume->GetGravity(GetOwner(), Mass);

	if (IsPhysics) Physics->AddImpulse(Impulse * DeltaTime);
	else {	
		OnReceiveImpulse.Broadcast(Impulse / Mass * DeltaTime * DeltaTime);
	}
}


void UMovementGravityAffected::EnterGravity(UGravityComponent * NewGravity){
	LocalGravity = NewGravity;
	OnEnterGravity.Broadcast(NewGravity);
}

void UMovementGravityAffected::ExitGravity(UGravityComponent * NewGravity){
	LocalGravity = NULL;
	OnExitGravity.Broadcast(NewGravity);
}
