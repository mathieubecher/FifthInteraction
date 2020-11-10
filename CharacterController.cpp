// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

	MovementController = CreateDefaultSubobject<UMovementController>(TEXT("MovementComponent"));
	MovementController->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	
}
// Called to bind functionality to input
void ACharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	//UE_LOG(LogTemp, Log, TEXT("Input create Pawn"));
	PlayerInputComponent->BindAxis("Turn", this, &ACharacterController::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterController::LookUpAtRate);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterController::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterController::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ACharacterController::MoveUp);
}

// Called every frame
void ACharacterController::Tick(float DeltaTime)
{
	if (LocalGravity) {
		TimerUp -= DeltaTime;
		if (TimerUp < 0) TimerUp = 0;
		FVector Up = FMath::Lerp(-LocalGravity->GetAttractVector(GetActorLocation()), LastUp, TimerUp);
		FVector Forward = FVector::CrossProduct(GetActorRightVector(), Up);
		FRotator Rot = UKismetMathLibrary::MakeRotFromXZ(Forward, Up);
		RootComponent->SetWorldRotation(Rot);
	}
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FreeRotation);
}

void ACharacterController::EnterGravity(UGravityComponent * NewGravity) {
	UE_LOG(LogTemp, Log, TEXT("Enter Gravity Event"));
	LocalGravity = NewGravity;
	LastUp = GetActorUpVector();
	TimerUp = 1;
}
void ACharacterController::ExitGravity(UGravityComponent * NewGravity) {
	UE_LOG(LogTemp, Log, TEXT("Exit Gravity Event"));
	LocalGravity = NULL;
}

void ACharacterController::TurnAtRate(float Rate) {
	FreeRotation.Yaw = Rate;
}

void ACharacterController::LookUpAtRate(float Rate) {
	if(LocalGravity) FreeRotation.Pitch = 0;
	else FreeRotation.Pitch = Rate;
}


void ACharacterController::MoveForward(float AxisValue) {
	if (MovementController && (MovementController->UpdatedComponent == RootComponent))
	{
		MovementController->AddInputVector(FVector::ForwardVector * AxisValue);
	}
}

void ACharacterController::MoveRight(float AxisValue) {
	if (MovementController && (MovementController->UpdatedComponent == RootComponent))
	{
		MovementController->AddInputVector(FVector::RightVector * AxisValue);
	}
}

void ACharacterController::MoveUp(float AxisValue) {
	if (MovementController && (MovementController->UpdatedComponent == RootComponent))
	{
		MovementController->AddInputVector(FVector::UpVector * AxisValue);
	}
}