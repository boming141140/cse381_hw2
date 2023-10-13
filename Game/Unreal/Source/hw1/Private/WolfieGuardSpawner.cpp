// Fill out your copyright notice in the Description page of Project Settings.

#include "WolfieGuardSpawner.h"
#include "WolfieGuard.h"
#include "GuardAIController.h"

// Sets default values for this component's properties
UWolfieGuardSpawner::UWolfieGuardSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	Guard1Spawned = false;
	Guard2Spawned = false;
	Guard3Spawned = false;
	Guard4Spawned = false;
	Guard5Spawned = false;
}


// Called when the game starts
void UWolfieGuardSpawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &UWolfieGuardSpawner::SpawnGuard, SpawnInterval, true);
}


// Called every frame
void UWolfieGuardSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWolfieGuardSpawner::SpawnGuard()
{
	//UE_LOG(LogTemp, Warning, TEXT("TRYING TO SPAWN GUARDS"));

	UWorld* CurrentWorld = GetWorld();
	FRotator SpawnRotation = FRotator(0.f);

	// Struct to hold guard spawn data
	struct FGuardSpawnData
	{
		FVector Location;
		FVector Scale;
		FVector RelativeLocation;
		FVector WorldScale;
		bool* SpawnedFlag;
		FString MeshPath;
		FString AnimationPath;
	};

	// Define an array of guard spawn data
	FGuardSpawnData GuardSpawnDatas[] = {
		{ FVector(12969, 18936, 180), FVector(0.3f, 0.3f, 0.3f), FVector(0.f, 0.f, 95), FVector(1.f, 1.f, 1.f), &Guard1Spawned, TEXT("/Game/StarterContent/model/teamq/team_q1.team_q1"), TEXT("/Game/StarterContent/model/teamq/team_q1_Anim.team_q1_Anim")},
		{ FVector(18483, 18290, 180), FVector(0.7f, 0.7f, 0.7f), FVector(0.f, 0.f, -90), FVector(1.f, 1.f, 1.f), &Guard2Spawned, TEXT("/Game/StarterContent/model/teama/team_a.team_a"), TEXT("/Game/StarterContent/model/teama/team_a_Anim.team_a_Anim")},
		{ FVector(14064, 19450, 180), FVector(1.f, 1.f, 1.f), FVector(0.f, 0.f, -35.f), FVector(0.15f, 0.15f, 0.15f), &Guard3Spawned, TEXT("/Game/StarterContent/model/teamf/team_f.team_f"), TEXT("/Game/StarterContent/model/teamf/team_f_Anim.team_f_Anim") },
		{ FVector(14064, 19600, 180), FVector(1.f, 1.f, 1.f), FVector(0.f, 0.f, -90), FVector(0.02f, 0.02f, 0.02f), &Guard4Spawned, TEXT("/Game/StarterContent/model/teamd/team_d.team_d"), TEXT("/Game/StarterContent/model/teamd/team_d_Anim.team_d_Anim") },
		{ FVector(14100, 19260, 180), FVector(1.f, 1.f, 1.f), FVector(0.f, 0.f, -35.f), FVector(70.f, 70.f, 70.f), &Guard5Spawned, TEXT("/Game/StarterContent/model/teame/team_e.team_e"), TEXT("/Game/StarterContent/model/teame/team_e_Anim.team_e_Anim") }
	};

	// Loop through and spawn guards based on spawn data
	for (const FGuardSpawnData& SpawnData : GuardSpawnDatas)
	{
		if (!(*SpawnData.SpawnedFlag))
		{
			AWolfieGuard* NewGuard = CurrentWorld->SpawnActor<AWolfieGuard>(SpawnData.Location, SpawnRotation);
			NewGuard->GetMesh()->SetRelativeLocation(SpawnData.RelativeLocation);
			NewGuard->GetMesh()->SetWorldScale3D(SpawnData.WorldScale);
			NewGuard->SetupGuardMesh(SpawnData.MeshPath);
			NewGuard->SetupGuardAnimation(SpawnData.AnimationPath);
			NewGuard->SetActorScale3D(SpawnData.Scale);
			NewGuard->AIControllerClass = AGuardAIController::StaticClass();

			if (NewGuard && !NewGuard->GetController())
			{
				AGuardAIController* NewController = GetWorld()->SpawnActor<AGuardAIController>();
				if (NewController)
				{
					NewController->Possess(NewGuard);
				}
			}
			*SpawnData.SpawnedFlag = true;
		}
	}
	/*
	if (!Guard1Spawned)
	{
		FVector SpawnLocation(12969, 18936, 180);
		AWolfieGuard* SpawnedActor = CurrentWorld->SpawnActor<AWolfieGuard>(SpawnLocation, SpawnRotation);

		// Scale down the actor
		FVector NewScale(0.3f, 0.3f, 0.3f); // Adjust these values as needed
		SpawnedActor->SetActorScale3D(NewScale);
		Guard1Spawned = true;
	}

	if (!Guard2Spawned)
	{
		FVector SpawnLocation(18483, 18290, 180);
		AWolfieGuard* SpawnedActor = CurrentWorld->SpawnActor<AWolfieGuard>(SpawnLocation, SpawnRotation);

		// Scale down the actor
		FVector NewScale(0.7f, 0.7f, 0.7f); // Adjust these values as needed
		SpawnedActor->SetActorScale3D(NewScale);
		Guard2Spawned = true;
	}

	if (!Guard3Spawned)
	{
		FVector SpawnLocation(14064, 19450, 180);
		AWolfieGuard* SpawnedActor = CurrentWorld->SpawnActor<AWolfieGuard>(SpawnLocation, SpawnRotation);
		Guard3Spawned = true;
	}

	if (!Guard4Spawned)
	{
		FVector SpawnLocation(14064, 19600, 180);
		AWolfieGuard* SpawnedActor = CurrentWorld->SpawnActor<AWolfieGuard>(SpawnLocation, SpawnRotation);
		Guard4Spawned = true;
	}

	if (!Guard5Spawned)
	{
		FVector SpawnLocation(14100, 19260, 180);
		AWolfieGuard* SpawnedActor = CurrentWorld->SpawnActor<AWolfieGuard>(SpawnLocation, SpawnRotation);

		// Scale down the actor
		//FVector NewScale(1.0f, 1.0f, 1.0f); // Adjust these values as needed
		//SpawnedActor->SetActorScale3D(NewScale);
		Guard5Spawned = true;
	}
	*/
}

