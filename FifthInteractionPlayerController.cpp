// Fill out your copyright notice in the Description page of Project Settings.


#include "FifthInteractionPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

/*
qx = ax * sin(angle/2)
qy = ay * sin(angle/2)
qz = az * sin(angle/2)
qw = cos(angle/2)

*/

void AFifthInteractionPlayerController::AddPitchInput(float Val) {
	UE_LOG(LogTemp, Log, TEXT("Pitch : %f"), Val);
	APlayerController::AddPitchInput(Val);
	/* QUATERNION
	FVector Axis = Rotation.GetRightVector();
	float Angle = Val * 3.14f / 180.0f;
	Rotation *= FQuat(Axis.X * sin(Angle/2), Axis.Y * sin(Angle / 2), Axis.Z * sin(Angle / 2), cos(Angle/2));
	Rotation.Normalize();
	ControlRotation = Rotation.Rotator();
	*/

	//ControlRotation += UKismetMathLibrary::RotatorFromAxisAndAngle(UKismetMathLibrary::GetRightVector(ControlRotation), Val);
}
void AFifthInteractionPlayerController::AddRollInput(float Val) {
	UE_LOG(LogTemp, Log, TEXT("Roll : %f"), Val);
	APlayerController::AddRollInput(Val);
	/* QUATERNION
	FVector Axis = Rotation.GetForwardVector();
	float Angle = Val * 3.14f / 180.0f;
	Rotation *= FQuat(Axis.X * sin(Angle / 2), Axis.Y * sin(Angle / 2), Axis.Z * sin(Angle / 2), cos(Angle / 2));
	Rotation.Normalize();
	ControlRotation = Rotation.Rotator();
	*/

	//FRotator LocalRotate = UKismetMathLibrary::RotatorFromAxisAndAngle(UKismetMathLibrary::GetForwardVector(ControlRotation), Val);
}
void AFifthInteractionPlayerController::AddYawInput(float Val) {
	UE_LOG(LogTemp, Log, TEXT("Yaw : %f"), Val);
	APlayerController::AddYawInput(Val);
	/* QUATERNION
	FVector Axis = Rotation.GetUpVector();
	float Angle = Val * 3.14f / 180.0f;
	Rotation *= FQuat(Axis.X * sin(Angle / 2), Axis.Y * sin(Angle / 2), Axis.Z * sin(Angle / 2), cos(Angle / 2));
	Rotation.Normalize();	
	ControlRotation = Rotation.Rotator();
	*/

	//ControlRotation += UKismetMathLibrary::RotatorFromAxisAndAngle(UKismetMathLibrary::GetUpVector(ControlRotation), Val);

}