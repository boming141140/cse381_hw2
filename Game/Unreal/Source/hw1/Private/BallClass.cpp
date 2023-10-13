// Fill out your copyright notice in the Description page of Project Settings.


#include "BallClass.h"
#include "MyCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "BallShootingWofie.h"



// Sets default values
ABallClass::ABallClass()
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
	MeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
	MeshComponent->OnComponentHit.AddDynamic(this, &ABallClass::OnComponentHit);
	MeshComponent->SetSimulatePhysics(true);

	// Enable the generation of hit events
	MeshComponent->BodyInstance.SetInstanceNotifyRBCollision(true);
	
	// Apply bouncy physics material
	static ConstructorHelpers::FObjectFinder<UPhysicalMaterial> PhysicalMaterialObj(TEXT("PhysicalMaterial'/Game/StarterContent/Materials/Ballbounciness.Ballbounciness'"));

	if (PhysicalMaterialObj.Succeeded())
	{
		PhysicalMaterial = PhysicalMaterialObj.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Physical material not found!"));
	}
	MeshComponent->SetPhysMaterialOverride(PhysicalMaterial);
	owner = nullptr;
}

// Called when the game starts or when spawned
void ABallClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABallClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABallClass::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Check if the ball collided with an instance of AMyCharacter (or whatever your character class is named)

	AMyCharacter* MyCharacterInstance = Cast<AMyCharacter>(OtherActor);
	ABallShootingWofie* WofieInstance = Cast<ABallShootingWofie>(OtherActor);
	if (owner) 
	{
		if (MyCharacterInstance && MyCharacterInstance != owner)
		{
			UE_LOG(LogTemp, Warning, TEXT("Collide with player"));
			MyCharacterInstance->HealthPoints -= 1;
		}
		else if (WofieInstance && WofieInstance != owner)
		{
			UE_LOG(LogTemp, Warning, TEXT("Collide with True Wofie"));
			WofieInstance->health -= 1;
		}
		owner = nullptr;
	}
	else
	{
		if (MyCharacterInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("Collide with player"));
			if (!MyCharacterInstance->hasBall) 
			{
				owner = MyCharacterInstance;
				AActor* ParentActor = HitComponent->GetOwner();
				ABallClass* MeshActor = Cast<ABallClass>(ParentActor);
				if (MeshActor) 
				{
					MyCharacterInstance->GetBall(MeshActor);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Physical material not found!"));
				}
			}
		}
		else if (WofieInstance)
		{
			UE_LOG(LogTemp, Warning, TEXT("Collide with True Wofie"));
			if (!WofieInstance->hasBall)
			{
				owner = MyCharacterInstance;
				AActor* ParentActor = HitComponent->GetOwner();
				ABallClass* MeshActor = Cast<ABallClass>(ParentActor);
				if (MeshActor)
				{
					WofieInstance->GetBall(MeshActor);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Physical material not found!"));
				}
			}
		}
	}

}

