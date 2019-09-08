// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank track is used to set maximum driving force and to apply forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))//, hidecategories = ("Collision"))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

		
public:

	UTankTrack();

	void BeginPlay() override;

	void ApplySidewaysForce();

	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float ThrottleAmount);

	void ApplyForwardsForce();
	
	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float TrackMaxDrivingForce = 40000000.f; // Assume 40ton tank and 1g accel

	UPROPERTY(VisibleAnywhere)
		float Throttle = 0.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


};
