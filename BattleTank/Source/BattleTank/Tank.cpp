// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

void ATank::AimAt(FVector HitLocation)
{
	AimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrel(UTankBarrel * BarrelToSet)
{
	AimingComponent->SetBarrel(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurret(UTankTurret * TurretToSet)
{
	AimingComponent->SetTurret(TurretToSet);
}

void ATank::Fire()
{
	if (!Barrel) { return; }
	if (!ProjectileBlueprint) { return; }
	/// Spawn projectile at socket location on Barrel

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, 
	Barrel->GetSocketLocation(FName("Projectile")),
	Barrel->GetSocketRotation(FName("Projectile")));

	Projectile->LaunchProjectile(LaunchSpeed);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

