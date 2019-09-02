// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UTankBarrel * BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurret(UTankTurret * TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



protected:

	UTankAimingComponent* AimingComponent = nullptr;

private:

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 40000.f; //1000 m/s TODO Find sensible default
	
	
};
