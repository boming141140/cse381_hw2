// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "WolfieGuard.h"
#include "BallShootingWofie.h"
#include "EngineUtils.h"
#include "MyCharacter.h"

void AMyHUD::DrawHUD()
{
    Super::DrawHUD();

    AddScore();
    AddPlayerHUD();
    AddGuardHealthBars();
}

void AMyHUD::SetHealth(int32 NewHealth)
{
    CurrentHealth = FMath::Clamp(NewHealth, 0, 3);  // Ensure it's between 0 and 3
}

void AMyHUD::SetScore(int32 NewScore)
{
    CurrentScore = NewScore;
}

void AMyHUD::SetWolfieGuardCount(int32 NewCount)
{
    WolfieGuardCount = NewCount;
}

void AMyHUD::SetGameOver(bool boo)
{
    bIsGameOver = boo;
}

void AMyHUD::GameOverDisplayScreen()
{
    AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    const float CenterX = Canvas->SizeX / 2;
    const float CenterY = Canvas->SizeY / 2;

    FString GameOverText = bHasWon ? TEXT("You Won!") : TEXT("You Lost!");
    DrawText(GameOverText, FColor::White, CenterX - 50, CenterY - 40, nullptr, 2.0f); // Adjust the positioning values based on your needs

    FString ScoreText = FString::Printf(TEXT("Score: %d"), PlayerCharacter);
    DrawText(ScoreText, FColor::White, CenterX - 50, CenterY, nullptr, 1.5f); // Adjust the positioning values based on your needs

}

void AMyHUD::AddPlayerHUD()
{
    // Access the player and its health percentage
    AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    float HealthPercentage = 1.0f; // Default to full health if something goes wrong
    if (PlayerCharacter)
    {
        // You can cast to your custom player character class if needed
        auto MyPlayer = Cast<AMyCharacter>(PlayerCharacter); // Replace AMyCharacter with your character class name if different
        if (MyPlayer)
        {
            HealthPercentage = MyPlayer->GetHealthPercent();
        }
    }

    // Define the health bar dimensions
    const float BarWidth = 200.0f;
    const float BarHeight = 25.0f;
    const float BarPosX = (Canvas->SizeX / 2) - (BarWidth / 2);
    const float BarPosY = Canvas->SizeY - 50;  // 50 units from the bottom

    // Draw the background white bar
    FLinearColor WhiteColor = FLinearColor::White;
    DrawRect(WhiteColor, BarPosX, BarPosY, BarWidth, BarHeight);

    // Draw the inner green bar, scaled by HealthPercentage
    FLinearColor GreenColor = FLinearColor::Green;
    DrawRect(GreenColor, BarPosX, BarPosY, BarWidth * HealthPercentage, BarHeight);

    // Define crosshair dimensions
    const float CrosshairSize = 10.0f;

    // Calculate the center of the screen
    const float CenterX = Canvas->SizeX / 2;
    const float CenterY = Canvas->SizeY / 2;

    // Draw crosshair
    DrawLine(CenterX - CrosshairSize, CenterY, CenterX + CrosshairSize, CenterY, FLinearColor::White); // Horizontal line
    DrawLine(CenterX, CenterY - CrosshairSize, CenterX, CenterY + CrosshairSize, FLinearColor::White); // Vertical line
}

void AMyHUD::AddGuardHealthBars()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();

    if (!PC) return; // If no player controller, exit

    FVector CameraLocation = PC->PlayerCameraManager->GetCameraLocation();

    for (TActorIterator<AWolfieGuard> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        AWolfieGuard* Guard = *ActorItr;

        if (Guard && Guard->IsAlive)
        {
            FVector GuardLocation = Guard->GetActorLocation();
            FVector2D ScreenPosition;

            if (PC->ProjectWorldLocationToScreen(GuardLocation, ScreenPosition))
            {
                FHitResult HitResult;
                FCollisionQueryParams Params;
                Params.AddIgnoredActor(Guard); // Ignore the guard itself in the trace
                Params.AddIgnoredActor(PC->GetPawn()); // Ignore the player in the trace

                // Perform the line trace (visibility check)
                bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, GuardLocation, ECC_Visibility, Params);

                // Only show the health bar if there was no hit, indicating a clear line of sight to the guard
                if (!bHit || (HitResult.GetActor() == Guard))
                {
                    const float BarWidth = 50.0f;
                    const float BarHeight = 10.0f;
                    const float BarPosX = ScreenPosition.X - BarWidth / 2;
                    const float BarPosY = ScreenPosition.Y - 60; // Adjust to position the health bar above the guard

                    // Draw background
                    DrawRect(FLinearColor::White, BarPosX, BarPosY, BarWidth, BarHeight);

                    // Draw health
                    float HealthPercentage = Guard->GetHealthPercent();
                    DrawRect(FLinearColor::Green, BarPosX, BarPosY, BarWidth * HealthPercentage, BarHeight);
                }
            }
        }
    }
    for (TActorIterator<ABallShootingWofie> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        ABallShootingWofie* Guard = *ActorItr;

        if (Guard && Guard->IsAlive)
        {
            FVector GuardLocation = Guard->GetActorLocation();
            FVector2D ScreenPosition;

            if (PC->ProjectWorldLocationToScreen(GuardLocation, ScreenPosition))
            {
                FHitResult HitResult;
                FCollisionQueryParams Params;
                Params.AddIgnoredActor(Guard); // Ignore the guard itself in the trace
                Params.AddIgnoredActor(PC->GetPawn()); // Ignore the player in the trace

                // Perform the line trace (visibility check)
                bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, GuardLocation, ECC_Visibility, Params);

                // Only show the health bar if there was no hit, indicating a clear line of sight to the guard
                if (!bHit || (HitResult.GetActor() == Guard))
                {
                    const float BarWidth = 50.0f;
                    const float BarHeight = 10.0f;
                    const float BarPosX = ScreenPosition.X - BarWidth / 2;
                    const float BarPosY = ScreenPosition.Y - 60; // Adjust to position the health bar above the guard

                    // Draw background
                    DrawRect(FLinearColor::White, BarPosX, BarPosY, BarWidth, BarHeight);

                    // Draw health
                    float HealthPercentage = Guard->GetHealthPercent();
                    DrawRect(FLinearColor::Green, BarPosX, BarPosY, BarWidth * HealthPercentage, BarHeight);
                }
            }
        }
    }
}

void AMyHUD::AddScore()
{
    // Draw the score text
    FString ScoreText = FString::Printf(TEXT("Score: %d"), CurrentScore);
    DrawText(ScoreText, FColor::White, 50, 50, nullptr, 1.5f);  // Positioned at (50, 50) and 1.5x scaled

    FString GuardText = FString::Printf(TEXT("Wolfie Guards: %d"), WolfieGuardCount);
    DrawText(GuardText, FColor::White, 50, 85, nullptr, 1.5f);
}
