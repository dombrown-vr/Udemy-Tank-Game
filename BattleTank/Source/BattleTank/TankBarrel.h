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
	// -1 is max downward speed, +1 max upward
	void Elevate(float RelativeSpeed);
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 20.f; // Sensible default
	
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegrees = 0.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegrees = 45.0f;
};
