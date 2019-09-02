// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"





void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto Tank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank)
	{
		auto PlayerLocation = PlayerTank->GetActorLocation();
		Tank->AimAt(PlayerLocation);

		Tank->Fire(); // TODO Limit firing rate
	}
	
}

