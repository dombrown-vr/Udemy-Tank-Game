// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;			
	}

}

bool UTankAimingComponent::IsBarrelMoving()
{
	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.005);
}

void UTankAimingComponent::Initialise(UTankBarrel * TankBarrelToSet, UTankTurret * TankTurretToSet)
{
	if (ensure(TankBarrelToSet && TankTurretToSet))
	{
		Barrel = TankBarrelToSet;
		Turret = TankTurretToSet;
	}
}

void UTankAimingComponent::Fire()
{

	if (FiringState != EFiringState::Reloading)
	{
		LastFireTime = FPlatformTime::Seconds();
		if (!ensure(Barrel && ProjectileBlueprint)) { return; }
			/// Spawn projectile at socket location on Barrel

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation("Projectile"),
			Barrel->GetSocketRotation("Projectile"));

		Projectile->LaunchProjectile(LaunchSpeed);
		
	}
}

void UTankAimingComponent::AimAt(FVector AimLocation)
{
	
	if (ensure(!(Barrel && Turret))) { return; }

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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		
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
	
	if (FMath::Abs(BarrelDeltaRotator.Yaw) > 180)
		Turret->Rotate(-BarrelDeltaRotator.Yaw);
	else
		Turret->Rotate(BarrelDeltaRotator.Yaw);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *BarrelDeltaRotator.ToString());
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}
