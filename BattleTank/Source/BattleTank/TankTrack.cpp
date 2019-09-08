// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
	// Calculate Slippage Speed
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	// Calculate required acceleration to correct
	auto CorrectingAcceleration = -(SlippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector());
	// Calculate and apply sideways force (F = ma)
	auto TankComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankComponent->GetMass() * CorrectingAcceleration / 2.f; // Divide by 2 as there are 2 tracks
	TankComponent->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float ThrottleAmount)
{
	Throttle = FMath::Clamp<float>(Throttle + ThrottleAmount, -1.f, 1.f);	
}
void UTankTrack::ApplyForwardsForce()
{
	auto Forwards = GetForwardVector().GetSafeNormal();
	auto ForceApplied = Forwards * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	Tank->AddForceAtLocation(ForceApplied, ForceLocation, NAME_None);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	// Drive Track
	ApplySidewaysForce();
	ApplyForwardsForce();
	Throttle = 0.f;
}

