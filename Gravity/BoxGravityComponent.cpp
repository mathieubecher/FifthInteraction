// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxGravityComponent.h"

UBoxGravityComponent::UBoxGravityComponent()
{
	Type = GravityType::BOX;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(this);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &UBoxGravityComponent::EnterGravity);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &UBoxGravityComponent::ExitGravity);
}
