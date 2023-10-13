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
		UE_LOG(LogTemp, Warning, TEXT("Target location: %s"), *targetLocation.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Trying to get ball"));
		MoveResult = MoveToLocation(TargetToFollow->GetActorLocation());
		if (MoveResult == EPathFollowingRequestResult::Failed)
		{
			UE_LOG(LogTemp, Error, TEXT("Move to get ball failed."));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Move to get ball initiated."));
		}
		FVector MyLocation = GetPawn()->GetActorLocation();
		UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
		if (NavSystem)
		{
			FNavLocation RandomReachablePoint;
			TSharedPtr<FNavigationQueryFilter> QueryFilter = MakeShareable(new FNavigationQueryFilter());
			bool bIsReachable = NavSystem->GetRandomReachablePointInRadius(MyLocation, 10000.0f, RandomReachablePoint, nullptr, QueryFilter);

			if (bIsReachable)
			{
				// Check if the reachable point is close to the target location.
				if ((RandomReachablePoint.Location - targetLocation).Size() < 100.0f) // Considered near if within 100 units.
				{
					UE_LOG(LogTemp, Warning, TEXT("	"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("The target location might not be directly reachable, but there's a reachable point near it at: %s"), *RandomReachablePoint.Location.ToString());
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("The target location is not reachable."));
			}
		}
	}
	else if (Enemy && !hasBall)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to run away"));
		FVector DangerDirection = Enemy->GetActorLocation() - GetPawn()->GetActorLocation();
		DangerDirection.Normalize();

		FVector RunAwayDestination = GetPawn()->GetActorLocation() - DangerDirection * 2000;
		MoveResult = MoveToLocation(RunAwayDestination);
		if (MoveResult == EPathFollowingRequestResult::Failed)
		{
			UE_LOG(LogTemp, Error, TEXT("Move to run away failed."));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Move to run away initiated."));
		}
	}
	else
	{
		// Logging for debugging purposes:
		if (!TargetToFollow)
		{
			UE_LOG(LogTemp, Warning, TEXT("TargetToFollow is null."));
		}

		if (Enemy)
		{
			UE_LOG(LogTemp, Warning, TEXT("Enemy is detected."));
		}

		if (hasBall)
		{
			UE_LOG(LogTemp, Warning, TEXT("AI has a ball."));
		}
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
