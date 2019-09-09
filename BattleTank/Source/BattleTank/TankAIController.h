// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 * 
 */

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:

	void Tick(float DeltaTime) override;

private:

	virtual void SetPawn(APawn* PawnToSet) override;

	void OnTankDestroyed();

	//How close can the AI tank can get to the player
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float AcceptanceRadius = 10000.f;
};
