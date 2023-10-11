// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "BallClass.generated.h"


UCLASS()
class HW1_API ABallClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallClass();
	bool collided = true;
	AActor* owner;
	// Meshes
	UStaticMesh* SphereMesh;
	UStaticMeshComponent* MeshComponent;
	UPhysicalMaterial* PhysicalMaterial;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
