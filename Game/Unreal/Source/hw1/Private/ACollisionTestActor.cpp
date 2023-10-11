// Fill out your copyright notice in the Description page of Project Settings.


#include "ACollisionTestActor.h"

// Sets default values
AACollisionTestActor::AACollisionTestActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create and set up the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshFinder(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (SphereMeshFinder.Succeeded())
	{
		MeshComponent->SetStaticMesh(SphereMeshFinder.Object);
	}

	// Set up collision
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
	MeshComponent->OnComponentHit.AddDynamic(this, &AACollisionTestActor::OnHit);
	MeshComponent->SetSimulatePhysics(true);

	// Enable the generation of hit events
	MeshComponent->BodyInstance.SetInstanceNotifyRBCollision(true);
}

// Called when the game starts or when spawned
void AACollisionTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AACollisionTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AACollisionTestActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Collision detected with %s"), *OtherActor->GetName());
}