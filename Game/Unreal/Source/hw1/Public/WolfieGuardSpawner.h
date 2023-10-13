// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WolfieGuardSpawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HW1_API UWolfieGuardSpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWolfieGuardSpawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SpawnGuard();
private:
	FTimerHandle SpawnTimerHandle;
	float SpawnInterval = 10.0f;
	bool Guard1Spawned;
	bool Guard2Spawned;
	bool Guard3Spawned;
	bool Guard4Spawned;
	bool Guard5Spawned;
};
