// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardHealthHUD.h"
#include "WolfieGuard.h"


AGuardHealthHUD::AGuardHealthHUD()
{
}

void AGuardHealthHUD::DrawHUD()
{
    Super::DrawHUD();
    /*
    // Iterate through all the guards in the world
    for (TActorIterator<AWolfieGuard> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        AWolfieGuard* Guard = *ActorItr;

        if (Guard && Guard->IsAlive())  // Assuming you have an IsAlive method or similar
        {
            FVector2D ScreenLocation;
            // Convert the guard's world location to screen location
            ProjectWorldLocationToScreen(Guard->GetActorLocation(), ScreenLocation);

            // Define dimensions of the health bar
            float BarWidth = 50.0f;
            float BarHeight = 10.0f;

            // Calculate the width based on the guard's current health
            float HealthPercentage = Guard->GetCurrentHealth() / Guard->GetMaxHealth();
            float HealthWidth = FMath::Lerp(0.0f, BarWidth, HealthPercentage);

            // Draw the background (gray bar)
            DrawRect(FLinearColor::Gray, ScreenLocation.X - BarWidth / 2, ScreenLocation.Y - 60, BarWidth, BarHeight);

            // Draw the health (green bar)
            DrawRect(FLinearColor::Green, ScreenLocation.X - BarWidth / 2, ScreenLocation.Y - 60, HealthWidth, BarHeight);
        }
    }
    */
}
