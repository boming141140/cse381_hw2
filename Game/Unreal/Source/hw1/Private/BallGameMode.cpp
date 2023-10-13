// Fill out your copyright notice in the Description page of Project Settings.


#include "BallGameMode.h"
#include "BallSpawner.h"
#include "MyCharacter.h"
#include "MyHUD.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "BallShootingWofie.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "GameFramework/PlayerStart.h"
#include "MyAIController.h"



ABallGameMode::ABallGameMode()
{
    BallSpawnerInstance = CreateDefaultSubobject<UBallSpawner>(TEXT("BallSpawnerInstance"));
    DefaultPawnClass = AMyCharacter::StaticClass();
    HUDClass = AMyHUD::StaticClass();
    //GuardSpawnerInstance = CreateDefaultSubobject<UWolfieGuard1Spawner>(TEXT("GuardSpawnerInstance"));
    GuardSpawnerInstance = CreateDefaultSubobject<UWolfieGuardSpawner>(TEXT("GuardSpawnerInstance"));
}

void ABallGameMode::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Using GameMode: %s"), *this->GetName());
    UE_LOG(LogTemp, Warning, TEXT("Default Pawn Class: %s"), *DefaultPawnClass->GetName());
    CheckAndPrintActorName(BallSpawnerInstance);

    // Cast the default HUD to your custom HUD class
    AMyHUD* GameHUD = Cast<AMyHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

    if (GameHUD)
    {
        // Example: set initial health and score values
        GameHUD->SetHealth(3);
        GameHUD->SetScore(0);
    }
    SummonTrueWofie();
    //(GetWorld());
}

void ABallGameMode::CheckAndPrintActorName(UObject* PotentialSubobject)
{
    if (!PotentialSubobject)
    {
        return;
    }

    // Get the outer (the object that contains or owns this object)
    UObject* Outer = PotentialSubobject->GetOuter();

    // If the outer is an actor, then this object is a direct subobject of an actor.
    if (AActor* OwningActor = Cast<AActor>(Outer))
    {
        UE_LOG(LogTemp, Warning, TEXT("The object is a subobject of actor: %s"), *OwningActor->GetName());
        return;
    }

    // If the outer isn't nullptr, it might be another UObject which itself could be contained within an AActor.
    while (Outer)
    {
        Outer = Outer->GetOuter();
        if (AActor* OwningActor = Cast<AActor>(Outer))
        {
            UE_LOG(LogTemp, Warning, TEXT("The object is a subobject of actor: %s"), *OwningActor->GetName());
            return;
        }
    }

    // If we reach here, the UObject is not a subobject of any actor.
    UE_LOG(LogTemp, Warning, TEXT("The object is not a subobject of any actor."));
}

AActor* ABallGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
    //FVector SpawnLocation(11785, 19467, 170);  // Replace with your coordinates
    FVector SpawnLocation(13385, 19467, 170);  // Temp spawn to start next to ball spawner
    FRotator SpawnRotation(0.f, 0.f, 0.f);
    return GetWorld()->SpawnActor<APlayerStart>(APlayerStart::StaticClass(), SpawnLocation, SpawnRotation);
}

void ABallGameMode::SummonTrueWofie()
{
    // Gather all PlayerStarts in the level
    TArray<APlayerStart*> SpawnPoints;
    for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
    {
        SpawnPoints.Add(*It);
    }

    // Check if we have at least 5 spawn points
    if (SpawnPoints.Num() >= 5)
    {
        for (int32 i = 0; i < 5; i++)
        {
            // Spawn the enemy at the PlayerStart's location
            ABallShootingWofie* NewWofie = GetWorld()->SpawnActor<ABallShootingWofie>(ABallShootingWofie::StaticClass(), SpawnPoints[i]->GetActorLocation(), FRotator::ZeroRotator);

            NewWofie->AIControllerClass = AMyAIController::StaticClass();

            if (NewWofie && !NewWofie->GetController())
            {
                AMyAIController* NewController = GetWorld()->SpawnActor<AMyAIController>();
                if (NewController)
                {
                    NewController->Possess(NewWofie);
                }
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Not enough spawn points defined!"));
    }
}


void ABallGameMode::SummonNavMesh(UWorld* world)
{
    FVector Location(16380.0, 19464.0, 38.0);  // Temp spawn to start next to ball spawner
    FRotator Rotation(0.f, 0.f, 0.f);
    ANavMeshBoundsVolume* NavMeshVolume = world->SpawnActor<ANavMeshBoundsVolume>(Location, Rotation);
    if (NavMeshVolume)
    {
        NavMeshVolume->SetActorScale3D(FVector(200.0f, 200.0f, 20.0f));  // This would set its scale which affects its size. Adjust accordingly.
    }
    
}
