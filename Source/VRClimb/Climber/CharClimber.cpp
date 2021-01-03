// Fill out your copyright notice in the Description page of Project Settings.


#include "CharClimber.h"
#include "VRLocomotionCharacter.h"
#include "IXRTrackingSystem.h"
#include "Engine.h"

void ACharClimber::BeginPlay() 
{
	Super::BeginPlay();
}

void ACharClimber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharClimber::doHMDPosition_Implementation()
{
	// Get New Location
	FVector devicePosition;
	FVector HMDDelta;
	FVector hmdPosition;
	FQuat deviceRotation;
	FVector NewLocation;

	GEngine->XRSystem->GetCurrentPose(IXRTrackingSystem::HMDDeviceId, deviceRotation, hmdPosition);
	float capsuleHeight = (hmdPosition.Z / 2.f) + 15.f;

	// Account for controller base movement
	switch (climbingHand) {
	case EClimbHand::NONE:
		devicePosition = hmdPosition;
		// Adjust the Player to the new location
		HMDDelta = devicePosition - LastHMDPos;
		NewLocation = HMDDelta + GetActorLocation();
		NewLocation.Z = GetActorLocation().Z;
		break;
	case EClimbHand::LEFT:
		devicePosition = LeftMotionController->GetRelativeLocation();
		// Adjust the Player to the new location
		HMDDelta = devicePosition - LastHMDPos;
		NewLocation = GetActorLocation() - HMDDelta;
		break;
	case EClimbHand::RIGHT:
		devicePosition = RightMotionController->GetRelativeLocation();
		// Adjust the Player to the new location
		HMDDelta = devicePosition - LastHMDPos;
		NewLocation = GetActorLocation() - HMDDelta;
	}


	SetActorLocation(NewLocation);

	// Store new Location
	LastLastHMDPos = LastHMDPos;
	LastHMDPos = devicePosition;

	// Adjust the location of the Motion Controllers
	MCOrigin->SetRelativeLocation(FVector(-hmdPosition.X, -hmdPosition.Y, -capsuleHeight));

	// Reset the location of the Camera;
	HMDOrigin->SetRelativeLocation(FVector(0.f, 0.f, hmdPosition.Z - GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	

	// Adjust the capsule halfheight to be the height of the player;
	GetCapsuleComponent()->SetCapsuleHalfHeight(capsuleHeight);
}

void ACharClimber::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// PlayerInputComponent->BindAction("", EInputEvent::IE_Pressed, this, );
}
