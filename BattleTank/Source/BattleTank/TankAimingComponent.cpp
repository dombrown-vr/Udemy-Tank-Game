// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO Should this tick??

	// ...
}


void UTankAimingComponent::SetBarrel(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
	
}


void UTankAimingComponent::AimAt(FVector AimLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector OutLaunchVelocity(0);

	bool bAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")),
		AimLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	auto Time = GetWorld()->GetTimeSeconds();
	if(bAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		
		MoveBarrelTowards(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%f: Barrel elevate called"), Time);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%f: No aiming solution found"), Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(const FVector AimDirection)
{
	/// Work out difference between current barrel position and new aim direction

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(5.f); // TODO Remove hard-coded number

}