// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupComponent.h"
#include "BallClass.h"

// Sets default values for this component's properties
UPickupComponent::UPickupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	HeldBall = nullptr; // Initialize to nullptr
	// ...
}

void UPickupComponent::PickupBall(ABallClass* BallToPickup)
{
	if (!HeldBall)
	{
		UE_LOG(LogTemp, Warning, TEXT("PickupBall function has been called!"));
		// Logic to pick up ball goes here
	}
}

void UPickupComponent::ThrowBall()
{
	if (HeldBall)
	{
		// Logic to release ball goes here
		HeldBall = nullptr; // Set back to nullptr
	}
}