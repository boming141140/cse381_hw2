// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMyPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Direction = GetScreenToWorldDirection();
    // Use Direction as needed or simply ignore in Tick.
}

FVector AMyPlayerController::GetScreenToWorldDirection()
{
    FVector ForwardVector;

    if (!IsLocalPlayerController()) // Ensure it's the local player
    {
        UE_LOG(LogTemp, Warning, TEXT("nOT LOCAL PLAYER"));
        return ForwardVector;
    }
        

    FVector StartLocation;
    FVector2D MousePosition;

    if (GetMousePosition(MousePosition.X, MousePosition.Y))
    {
        // Convert mouse position to world space direction
        DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, StartLocation, ForwardVector);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get mouse position."));
    }

    UE_LOG(LogTemp, Warning, TEXT("MyVector: %s"), *ForwardVector.ToString());
    return ForwardVector; // This is the direction from the screen into the game world.
}