// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "WolfieGuard.generated.h"

UCLASS()
class HW1_API AWolfieGuard : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWolfieGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int32 health;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	USkeletalMesh* GuardMesh;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimSequence* GuardAnimation;

	// Methods to set up the guard mesh and animation
	void SetupGuardMesh(const FString& MeshPath);
	void SetupGuardAnimation(const FString& AnimationPath);
	void DetectEnemy(UWorld* world);
	void CheckDeath();
	// Skeletal mesh component for the guard
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USkeletalMeshComponent* GuardMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCapsuleComponent* CapsuleComponent;

	float CurrentHealth;
	float MaxHealth = 3;

	// Methods to set up the guard mesh and animation
	void SetupGuardMesh(const FString& MeshPath);
	void SetupGuardAnimation(const FString& AnimationPath);
	float GetHealthPercent();

	bool IsAlive;
};