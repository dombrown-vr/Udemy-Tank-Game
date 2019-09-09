// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Gets current health between 0.0 and 1.0
	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealth() const;

private:

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser
	) override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	int32 TotalHealth = 100.f;

	int32 CurrentHealth;
};
