// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Engine/Canvas.h"

void AMyHUD::DrawHUD()
{
    Super::DrawHUD();

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
    DrawRect(GreenColor, BarPosX, BarPosY, BarWidth * (CurrentHealth / 3.0f), BarHeight);

    // Draw black outline
    DrawLine(BarPosX, BarPosY, BarPosX + BarWidth, BarPosY, FLinearColor::Black); // Top
    DrawLine(BarPosX, BarPosY, BarPosX, BarPosY + BarHeight, FLinearColor::Black); // Left
    DrawLine(BarPosX + BarWidth, BarPosY, BarPosX + BarWidth, BarPosY + BarHeight, FLinearColor::Black); // Right
    DrawLine(BarPosX, BarPosY + BarHeight, BarPosX + BarWidth, BarPosY + BarHeight, FLinearColor::Black); // Bottom

    // Draw the score text
    FString ScoreText = FString::Printf(TEXT("Score: %d"), CurrentScore);
    DrawText(ScoreText, FColor::White, 50, 50, nullptr, 1.5f);  // Positioned at (50, 50) and 1.5x scaled

    FString GuardText = FString::Printf(TEXT("Wolfie Guards: %d"), WolfieGuardCount);
    DrawText(GuardText, FColor::White, 50, 85, nullptr, 1.5f);
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
