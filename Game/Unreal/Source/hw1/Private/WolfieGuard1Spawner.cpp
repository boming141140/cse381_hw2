// Fill out your copyright notice in the Description page of Project Settings.


#include "WolfieGuard1Spawner.h"

// Sets default values for this component's properties
UWolfieGuard1Spawner::UWolfieGuard1Spawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWolfieGuard1Spawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWolfieGuard1Spawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

