// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	FVector HitLocation; // Out parameter
	if (!GetPawn()) { return; }; // if not possessing
	if (GetSightRayHitLocation(HitLocation))
	{
		if (ensure(AimingComponent)) 
			AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	/// Find crosshair pixel position on screen
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto CrosshairScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	/// Deproject the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(CrosshairScreenLocation, LookDirection))
	{
		return (GetLookVectorHitLocation(LookDirection, OutHitLocation));
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	/// Line trace along that direction (look direction)
	FHitResult HitResult;
	FVector Start = PlayerCameraManager->GetCameraLocation(); // Location of crosshair in world
	FVector End = Start + (LineTraceRange * LookDirection); // Disctance from Start in LookDirection
	
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult,
				Start, 
				End, 
				ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}	
	HitLocation = FVector(0.f);
	return false;
}

void ATankPlayerController::OnTankDestroyed()
{
	if (!ensure(GetPawn())) { return; }
	StartSpectatingOnly();
}

void ATankPlayerController::SetPawn(APawn * PawnToSet)
{
	Super::SetPawn(PawnToSet);
	if(PawnToSet)
	{
		auto PossessedTank = Cast<ATank>(PawnToSet);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDestroyed);
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenPosition, FVector& LookDirection) const
{
	FVector WorldLocation; // To be discarded
	if (DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldLocation, LookDirection))
	{
		return true;
	}
	else
	{
		return false;
	}
}


