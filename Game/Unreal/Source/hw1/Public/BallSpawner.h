// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BallSpawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HW1_API UBallSpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBallSpawner();
	// Counter for the number of times the timer has fired.
	int32 RepetitionCounter = 0;

	// Maximum number of repetitions desired.
	int32 MaxRepetitions = 30;

	// Meshes
	UStaticMesh* SphereMesh;
	UPhysicalMaterial* BouncyMaterial;
	FVector ChuteLocation;
	UPhysicalMaterial* PhysicalMaterial;
	FTimerHandle SpawnTimerHandle;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float SpawnInterval = 10.0f;
	TArray<AActor*> SpawnedActors;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Function to spawn the ball
	void SpawnBall();
	
};
