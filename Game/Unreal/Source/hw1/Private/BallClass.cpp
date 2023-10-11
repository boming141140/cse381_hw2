// Fill out your copyright notice in the Description page of Project Settings.


#include "BallClass.h"
#include "Components/StaticMeshComponent.h"


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

	owner = nullptr;
}

// Called when the game starts or when spawned
void ABallClass::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetNotifyRigidBodyCollision(true);
	MeshComponent->OnComponentHit.AddDynamic(this, &ABallClass::OnHit);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly); 
	MeshComponent->SetGenerateOverlapEvents(true);
	MeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ABallClass::OnOverlapBegin);

	RootComponent = MeshComponent;
}

// Called every frame
void ABallClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABallClass::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Check if the other actor is the player and if the player can pick up the ball
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Your log message here"));
	}
	AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("OnHit called."));
	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player exists."));
		Player->AttemptPickup(this);
		// You can destroy the ball or set it to invisible after it's picked up
		this->Destroy();
	}
}

void ABallClass::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the other actor is the player
	AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);
	if (Player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ball overlapped with player!"));
	}
}

