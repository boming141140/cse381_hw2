// Fill out your copyright notice in the Description page of Project Settings.


#include "WolfieGuard1Spawner.h"
#include "WolfieGuard1.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UWolfieGuard1Spawner::UWolfieGuard1Spawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bIsWolfieGuard1Active = false;
}


// Called when the game starts
void UWolfieGuard1Spawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//RetrieveChuteLocation(SpawnerLocation, GetWorld());
	//GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &UBallSpawner::SpawnBall, SpawnInterval, true);
	SpawnWolfieGuard1();
}


// Called every frame
void UWolfieGuard1Spawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWolfieGuard1Spawner::SpawnWolfieGuard1()
{
	if (!bIsWolfieGuard1Active && WolfieGuard1Class)
	{
		UE_LOG(LogTemp, Warning, TEXT("TRYING TO SPAWN WOLFIE GUARD"));
		FActorSpawnParameters SpawnParams;

		// Specify the location and rotation for spawning the actor
		FVector SpawnLocation = FVector(13782, 18636, 343);  // replace with your desired location
		FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f); // replace with your desired rotation

		GetWorld()->SpawnActor<AWolfieGuard1>(WolfieGuard1Class, SpawnLocation, SpawnRotation, SpawnParams);
		bIsWolfieGuard1Active = true;
	}
}

