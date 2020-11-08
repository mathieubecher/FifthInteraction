// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereGravityComponent.h"

// Sets default values for this component's properties
USphereGravityComponent::USphereGravityComponent()
{
	Type = GravityType::SPHERE;
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(this);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &USphereGravityComponent::EnterGravity);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &USphereGravityComponent::ExitGravity);
}
	