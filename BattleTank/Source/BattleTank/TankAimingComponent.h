// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrel(UTankBarrel* BarrelToSet);

	void AimAt(FVector AimLocation, float LaunchSpeed);

	void MoveBarrelTowards(const FVector AimDirection);

private:
	UTankBarrel* Barrel = nullptr;
	UStaticMeshComponent* Turret = nullptr;
	
};
