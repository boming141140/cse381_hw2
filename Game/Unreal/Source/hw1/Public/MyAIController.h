// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class HW1_API AMyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AActor* TargetToFollow;
	AActor* Enemy;
	bool hasBall;
public:
	AMyAIController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SetTarget(AActor* _TargetToFollow);
	void SetEnemy(AActor* _Enemy);

	//virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
