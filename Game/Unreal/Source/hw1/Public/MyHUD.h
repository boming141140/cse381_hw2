// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CanvasItem.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class HW1_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
    // Called every frame
    virtual void DrawHUD() override;

    // Sets the player's current health. Clamps the value between 0 and 3.
    void SetHealth(int32 NewHealth);

    // Sets the player's current score
    void SetScore(int32 NewScore);

    // Sets the Wolfie Guard count
    void SetWolfieGuardCount(int32 NewCount);

private:
    // Player's health (0 - 3)
    int32 CurrentHealth = 3;

    // Player's score (number of one true wolfies killed)
    int32 CurrentScore = 0;

    // Number of Wolfie Guards alive
    int32 WolfieGuardCount = 5;
};
