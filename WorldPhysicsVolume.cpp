// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPhysicsVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"


void AWorldPhysicsVolume::BeginPlay() {
	
}

FVector AWorldPhysicsVolume::GetGravity(AActor * Actor, float Mass) {

	FVector Inertia(0, 0, 0);

	for (int i = 0; i < Gravitys.Num(); i++) {
		if (Gravitys[i]->GetOwner() != Actor) Inertia += Gravitys[i]->GetGravity(Actor->GetActorLocation(), Mass);
	}
	return Inertia;
}
void AWorldPhysicsVolume::AddGravityComponent(UGravityComponent * Gravity) {
	Gravitys.Add(Gravity);
}