// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BallSpawner.h"
#include "BallGameMode.generated.h"
/**
 * 
 */
UCLASS()
class HW1_API ABallGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ABallGameMode();
	UBallSpawner* BallSpawnerInstance;
	virtual void BeginPlay() override;

};
