// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
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

	bool GetLookDirection(FVector2D ScreenPosition, FVector & LookDirection) const;

	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;

};
