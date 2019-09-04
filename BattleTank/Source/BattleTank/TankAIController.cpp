// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto Tank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius, true, true, false); // TODO check radius is in cm


		auto PlayerLocation = PlayerTank->GetActorLocation();
		Tank->AimAt(PlayerLocation);

		Tank->Fire(); 
	}
	
}

