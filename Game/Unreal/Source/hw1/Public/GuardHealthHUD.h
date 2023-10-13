// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GuardHealthHUD.generated.h"

/**
 * 
 */
UCLASS()
class HW1_API AGuardHealthHUD : public AHUD
{
	GENERATED_BODY()

public:
    // Default constructor
    AGuardHealthHUD();

    // Override DrawHUD function
    virtual void DrawHUD() override;
};
