// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRLocomotionCharacter.h"
#include "CharClimber.generated.h"

UENUM(BlueprintType)
enum class EClimbHand : uint8 {
	NONE,
	LEFT,
	RIGHT
};

/**
 * 
 */
UCLASS()
class VRCLIMB_API ACharClimber : public AVRLocomotionCharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EClimbHand climbingHand = EClimbHand::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LastLastHMDPos;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Climb
	virtual void doHMDPosition_Implementation() override;

	// Controls

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
