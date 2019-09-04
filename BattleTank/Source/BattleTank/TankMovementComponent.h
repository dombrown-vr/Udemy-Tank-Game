// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankTrack.h"
#include "TankMovementComponent.generated.h"

/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendRotateClockwise(float Throw);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

private:
	// Called from the pathfinding logic by the AI controllers
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
	UTankTrack* TrackL = nullptr;
	UTankTrack* TrackR = nullptr;	
};
