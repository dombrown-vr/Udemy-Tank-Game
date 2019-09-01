// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATankPlayerController();

private:
	ATank* GetControlledTank() const;


	//Starts moving the barrel of the tank so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();

	void BeginPlay() override;
	
	void Tick(float DeltaTime) override;
};
