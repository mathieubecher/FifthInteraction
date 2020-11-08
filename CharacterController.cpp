// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"

// Sets default values
ACharacterController::ACharacterController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComponent"));
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetCollisionProfileName(TEXT("Pawn"));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	Gravity = CreateDefaultSubobject<UMovementGravityAffected>(TEXT("Gravity"));
	Gravity->OnEnterGravity.AddDynamic(this, &ACharacterController::EnterGravity);
	Gravity->OnExitGravity.AddDynamic(this, &ACharacterController::ExitGravity);
}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("Test create Pawn"));
	
}
// Called to bind functionality to input
void ACharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacterController::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterController::LookUpAtRate);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterController::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterController::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ACharacterController::MoveUp);
}

// Called every frame
void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterController::EnterGravity(UGravityComponent * NewGravity) {
	UE_LOG(LogTemp, Log, TEXT("Enter Gravity Event"));
}
void ACharacterController::ExitGravity(UGravityComponent * NewGravity) {
	UE_LOG(LogTemp, Log, TEXT("Exit Gravity Event"));
}

void ACharacterController::TurnAtRate(float Rate) {
	AddActorLocalRotation(FRotator(0, Rate, 0));
}

void ACharacterController::LookUpAtRate(float Rate) {
	AddActorLocalRotation(FRotator(Rate, 0, 0));

}


void ACharacterController::MoveForward(float AxisValue) {

}

void ACharacterController::MoveRight(float AxisValue) {

}

void ACharacterController::MoveUp(float AxisValue) {

}