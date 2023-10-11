// Fill out your copyright notice in the Description page of Project Settings.


#include "BallClass.h"

// Sets default values
ABallClass::ABallClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshFinder(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (SphereMeshFinder.Succeeded())
	{
		SphereMesh = SphereMeshFinder.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Shape_Sphere is not found!"));
	}
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetMobility(EComponentMobility::Movable);
	MeshComponent->SetStaticMesh(SphereMesh);

	// Add the dynamic for hit
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->OnComponentHit.AddDynamic(this, &ABallClass::OnHit);
	owner = nullptr;
}

// Called when the game starts or when spawned
void ABallClass::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentHit.AddDynamic(this, &ABallClass::OnHit);
}

// Called every frame
void ABallClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABallClass::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//if (OtherActor && OtherActor != this)
	//{
		// Check if the actor we hit is the player
		/*APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

		// If it is the player, set the owner
		if (Player)
		{
			//Player is holding a ball then dealt damage
			//ToDo
			owner = Player;
		}
		else  // If it's any other actor, set the owner to nullptr
		{
			owner = nullptr;
		}
		*/
	//}
    // Check if the other actor is the player and if the player can pick up the ball
	AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);
	if (Player)
	{
		Player->AttemptPickup(this);
		// You can destroy the ball or set it to invisible after it's picked up
		this->Destroy();
	}
}

