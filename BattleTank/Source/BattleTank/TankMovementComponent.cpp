// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!TrackL || !TrackR) { return; }
	TrackL->SetThrottle(Throw);
	TrackR->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotateClockwise(float Throw)
{
	if (!TrackL || !TrackR) { return; }
	TrackL->SetThrottle(Throw);
	TrackR->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	
	TrackL = LeftTrackToSet;		
	TrackR = RightTrackToSet;
	

}
