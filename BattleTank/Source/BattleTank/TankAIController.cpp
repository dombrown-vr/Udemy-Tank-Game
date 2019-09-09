// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto Aiming = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (ensure(PlayerTank && Aiming))
	{
		MoveToActor(PlayerTank, AcceptanceRadius, true, true, false); // TODO check radius is in cm

		auto PlayerLocation = PlayerTank->GetActorLocation();
		Aiming->AimAt(PlayerLocation);

		// If aiming or locked
		if (Aiming->GetFiringState() == EFiringState::Locked)
			Aiming->Fire();		
	}
	
}

void ATankAIController::SetPawn(APawn * PawnToSet)
{
	Super::SetPawn(PawnToSet);

	if (PawnToSet)
	{
		auto PossessedTank = Cast<ATank>(PawnToSet);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDestroyed);
	}

}
void ATankAIController::OnTankDestroyed()
{

}