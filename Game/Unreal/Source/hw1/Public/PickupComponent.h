// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BallClass.h"
#include "PickupComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HW1_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPickupComponent();

	// Try to pick up a ball
	UFUNCTION()
	void PickupBall(ABallClass* BallToPickup);

	// Release the held ball
	UFUNCTION()
	void ThrowBall();
	UPROPERTY()
	ABallClass* HeldBall;
};
