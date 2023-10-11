// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallClass.h"
#include "Camera/CameraComponent.h"
#include "MyPlayerController.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class HW1_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	int32 HealthPoints;
	bool hasBall;
	FVector OriginalScale;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyCharacter")
	UStaticMeshComponent* MeshComponentForCharacter;
	UPROPERTY()
	ABallClass* ActualBall;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Spring Arm Component to follow the camera behind the player
	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;*/

	//Player follow camera
	AMyPlayerController* ScreenController;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComp;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//Called for forwards/backward input

	void MoveForward(float InputAxis);

	//called for left/right side input

	void MoveRight(float InputAxis);

	void HandleShootBall();

	void GetBall(ABallClass* ball);

	void PitchInput(float val);

	void ShootBallInScreenCenterDirection(UStaticMeshComponent* Ball);

	FVector GetScreenToWorldDirection();

};
