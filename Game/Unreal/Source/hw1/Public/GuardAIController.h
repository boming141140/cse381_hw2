// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GuardAIController.generated.h"

/**
 * 
 */
UCLASS()
class HW1_API AGuardAIController : public AAIController
{
	GENERATED_BODY()
public:
	AActor* TargetToFollow;
public:
	AGuardAIController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SetTarget(AActor* _TargetToFollow);
};
