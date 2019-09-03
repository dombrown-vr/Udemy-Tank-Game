// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float ThrottleAmount)
{
	
	// TODO Clamp throttle value
	auto Forwards = GetForwardVector().GetSafeNormal();
	auto ForceApplied = Forwards * ThrottleAmount * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	Tank->AddForceAtLocation(ForceApplied, ForceLocation, NAME_None);
	
}

