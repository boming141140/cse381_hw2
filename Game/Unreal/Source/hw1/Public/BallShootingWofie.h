// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallClass.h"
#include "GameFramework/Character.h"
#include "BallShootingWofie.generated.h"

UCLASS()
class HW1_API ABallShootingWofie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABallShootingWofie();
	float health;
	bool hasBall;
	ABallClass* ActualBall;
	UAnimSequence* ShootingAnimation;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float MaxHealth = 3;
	
	void StartShootingAnimation();
	void FindTheClosetBall(UWorld* world);
	void DetectEnemy(UWorld* world);
	void CombatCheck();
	void GetBall(ABallClass* ball);
	void ShotBall(FVector Direction);
	void CheckDeath();
	float GetHealthPercent();
	bool IsAlive;
};
