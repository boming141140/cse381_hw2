// Fill out your copyright notice in the Description page of Project Settings.


#include "BallGameMode.h"
#include "BallSpawner.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


ABallGameMode::ABallGameMode()
{
    BallSpawnerInstance = CreateDefaultSubobject<UBallSpawner>(TEXT("BallSpawnerInstance"));
    DefaultPawnClass = AMyCharacter::StaticClass();
}

void ABallGameMode::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Using GameMode: %s"), *this->GetName());
    UE_LOG(LogTemp, Warning, TEXT("Default Pawn Class: %s"), *DefaultPawnClass->GetName());
    CheckAndPrintActorName(BallSpawnerInstance);
    
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



