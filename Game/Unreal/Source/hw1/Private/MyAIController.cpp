// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "NavigationSystem.h"
#include "NavFilters/NavigationQueryFilter.h"

AMyAIController::AMyAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	hasBall = false;
	TargetToFollow = nullptr;
	Enemy = nullptr;
	// Log message
	UE_LOG(LogTemp, Warning, TEXT("AMyAIController Constructor Called"));
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EPathFollowingRequestResult::Type MoveResult;

	if (TargetToFollow && !Enemy && !hasBall)
	{
		FVector targetLocation = TargetToFollow->GetActorLocation();
		MoveResult = MoveToLocation(TargetToFollow->GetActorLocation());

	}
	else if (Enemy && !hasBall)
	{
		FVector DangerDirection = Enemy->GetActorLocation() - GetPawn()->GetActorLocation();
		DangerDirection.Normalize();

		FVector RunAwayDestination = GetPawn()->GetActorLocation() - DangerDirection * 2000;
		MoveResult = MoveToLocation(RunAwayDestination);
	} 
}
void AMyAIController::SetTarget(AActor* _TargetToFollow)
{
	AMyAIController::TargetToFollow = _TargetToFollow;
}

void AMyAIController::SetEnemy(AActor* _Enemy)
{
	AMyAIController::Enemy = _Enemy;
}

/*void AMyAIController::OnPossess(APawn* InPawn)
{	
	Super::Possess(InPawn);
	//UE_LOG(LogTemp, Warning, TEXT("AI Controller has possessed %s"), *InPawn->GetName());
}
*/
void AMyAIController::OnUnPossess()
{
}
