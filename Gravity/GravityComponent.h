// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "GravityComponent.generated.h"

UENUM(BlueprintType)
enum GravityType
{
	SPHERE=0 UMETA(DisplayName = "SPHERE"),
	BOX=1 UMETA(DisplayName = "BOX"),
	CYLINDER=2 UMETA(DisplayName = "CYLINDER"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIFTHINTERACTION_API UGravityComponent : public USceneComponent
{
	GENERATED_BODY()	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity")
	TEnumAsByte<GravityType> Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity")
	bool HasAtmosphere;
public:	
	// Sets default values for this component's properties
	UGravityComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity")
	float Mass = 50;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Gravity")
	virtual FVector GetAttractVector(FVector Position);

	UFUNCTION(BlueprintCallable, Category = "Gravity")
	virtual FVector GetGravity(FVector Position, float ActorMass);


	UFUNCTION(BlueprintCallable, Category = "Gravity")
	virtual void EnterGravity(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Gravity")
	virtual void ExitGravity(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


		
};
