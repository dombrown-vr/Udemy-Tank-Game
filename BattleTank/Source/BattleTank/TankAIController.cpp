// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto Tank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto Aiming = Tank->FindComponentByClass<UTankAimingComponent>();
	if (PlayerTank && Tank && Aiming)
	{
		MoveToActor(PlayerTank, AcceptanceRadius, true, true, false); // TODO check radius is in cm


		auto PlayerLocation = PlayerTank->GetActorLocation();
		Aiming->AimAt(PlayerLocation);

		Aiming->Fire(); 
	}
	
}

