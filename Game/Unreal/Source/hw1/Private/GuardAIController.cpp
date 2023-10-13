// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardAIController.h"

AGuardAIController::AGuardAIController()
{
	
	PrimaryActorTick.bCanEverTick = true;
	TargetToFollow = nullptr;
}

void AGuardAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AGuardAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TargetToFollow)
	{
		FVector targetLocation = TargetToFollow->GetActorLocation();
		MoveToLocation(TargetToFollow->GetActorLocation());
	}
}

void AGuardAIController::SetTarget(AActor* _TargetToFollow)
{
	AGuardAIController::TargetToFollow = _TargetToFollow;
}
