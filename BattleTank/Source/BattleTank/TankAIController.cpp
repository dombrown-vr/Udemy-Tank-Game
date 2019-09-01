// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"




ATank* ATankAIController::GetControlledTank() const
{
	auto Tank = Cast<ATank>(GetPawn());
	check(Tank);
	return Tank;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	UE_LOG(LogTemp, Warning, TEXT("TankAIController possessing %s"), *ControlledTank->GetName());


	auto PlayerTank = GetPlayerTank();
	UE_LOG(LogTemp, Warning, TEXT("AI Tank: %s found player at Tank: %s"), *ControlledTank->GetName(), *PlayerTank->GetName());
}
ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	auto PlayerTank = Cast<ATank>(PlayerController->GetPawn());
	check(PlayerTank);
	return PlayerTank;
}
