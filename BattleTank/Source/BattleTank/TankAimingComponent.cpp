// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::Initialise(UTankBarrel * TankBarrelToSet, UTankTurret * TankTurretToSet)
{
	if (TankBarrelToSet && TankTurretToSet)
	{
		Barrel = TankBarrelToSet;
		Turret = TankTurretToSet;
	}
}

void UTankAimingComponent::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;
	if (isReloaded)
	{
		LastFireTime = FPlatformTime::Seconds();
		if (Barrel && ProjectileBlueprint)
		{
			/// Spawn projectile at socket location on Barrel

			auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
				Barrel->GetSocketLocation("Projectile"),
				Barrel->GetSocketRotation("Projectile"));

			Projectile->LaunchProjectile(LaunchSpeed);
		}
	}
}

void UTankAimingComponent::AimAt(FVector AimLocation)
{
	if (!Barrel || !Turret) { return; }

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

	if(bAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		
		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimingComponent::MoveBarrelTowards(const FVector AimDirection)
{
	/// Work out difference between current barrel position and new aim direction
	auto AimAsRotator = AimDirection.Rotation();

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto BarrelDeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(BarrelDeltaRotator.Pitch); 

	//auto TurretRotator = Turret->GetForwardVector().Rotation();
	//auto TurretDeltaRotator = AimAsRotator - TurretRotator;
	Turret->Rotate(BarrelDeltaRotator.Yaw);
	
	if (BarrelDeltaRotator.Equals(FRotator(0.f), 0.1))
	{
		auto Time = FPlatformTime::Seconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Ready to fire! %s"), Time, *BarrelDeltaRotator.ToString());
	}
}
