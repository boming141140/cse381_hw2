// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BallSpawner.h"
#include "GameFramework/Actor.h"
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
	void CheckAndPrintActorName(UObject* PotentialSubobject);
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	void SummonTrueWofie();
	void SummonNavMesh(UWorld* world);
};
