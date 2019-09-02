// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float ThrottleAmount)
{
	
	UE_LOG(LogTemp, Warning, TEXT("%s Throttle: %f"), *GetName(), ThrottleAmount);
	// TODO Clamp throttle value
	auto Forwards = GetForwardVector();
	auto ForceApplied = Forwards * ThrottleAmount * TrackMaxDrivingForce; // need to change forwardvector to tank's forward vector
	auto ForceLocation = GetComponentLocation();
	auto Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	Tank->AddForceAtLocation(ForceApplied, ForceLocation, NAME_None);
	
}

