// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possessing %s"), *GetControlledTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possessing no pawn"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/// Aim through crosshair
}

ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	//Get world location line trace through crosshair
	//if it hits something
		//get controlled tank to aim at this point
}