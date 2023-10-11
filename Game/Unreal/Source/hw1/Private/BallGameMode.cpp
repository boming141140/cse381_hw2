// Fill out your copyright notice in the Description page of Project Settings.


#include "BallGameMode.h"
#include "BallSpawner.h"
#include "MyCharacter.h"
#include "MyHUD.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerStart.h"
#include "WolfieGuard1Spawner.h"


ABallGameMode::ABallGameMode()
{
    BallSpawnerInstance = CreateDefaultSubobject<UBallSpawner>(TEXT("BallSpawnerInstance"));
    DefaultPawnClass = AMyCharacter::StaticClass();
    HUDClass = AMyHUD::StaticClass();
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
    FVector SpawnLocation(19385, 19467, 170);  // Temp spawn to start next to ball spawner
    FRotator SpawnRotation(0.f, 0.f, 0.f);
    return GetWorld()->SpawnActor<APlayerStart>(APlayerStart::StaticClass(), SpawnLocation, SpawnRotation);
}



