// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */

// Holds properties for tank barrel
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UTankBarrel();

	// -1 is max downward speed, +1 max upward
	void Elevate(float RelativeSpeed);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 5.f; // Sensible default
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinElevationDegrees = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxElevationDegrees = 40.0f;
};
