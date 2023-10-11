// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WolfieGuard1Spawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HW1_API UWolfieGuard1Spawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWolfieGuard1Spawner();
	FVector SpawnerLocation;
	FTimerHandle SpawnTimerHandle;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float SpawnInterval = 10.0f;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<class AWolfieGuard1> WolfieGuard1Class;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnWolfieGuard1();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* GuardMeshComponent;

private:
	bool bIsWolfieGuard1Active;
};
