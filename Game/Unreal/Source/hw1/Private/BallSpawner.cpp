// Fill out your copyright notice in the Description page of Project Settings.


#include "BallSpawner.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h"
#include "BallClass.h"

#include "PhysicalMaterials/PhysicalMaterial.h"


//manually hoisting 
static void RetrieveChuteLocation(FVector& ChuteLocation, UWorld* World);

// Sets default values for this component's properties
UBallSpawner::UBallSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UPhysicalMaterial> PhysicalMaterialObj(TEXT("PhysicalMaterial'/Game/StarterContent/Materials/Ballbounciness.Ballbounciness'"));

	if (PhysicalMaterialObj.Succeeded())
	{
		PhysicalMaterial = PhysicalMaterialObj.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Physical material not found!"));
	}
}




// Called when the game starts
void UBallSpawner::BeginPlay()
{
	Super::BeginPlay();
	// ...
	RetrieveChuteLocation(ChuteLocation, GetWorld());
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &UBallSpawner::SpawnBall, SpawnInterval, true);
}

// Wrapper for getting ChuteLocation from the Game World
static void RetrieveChuteLocation(FVector& ChuteLocation, UWorld* World)
{
	FString DesiredActorLabel = TEXT("chute");
	AStaticMeshActor* FoundActor = nullptr;

	for (TActorIterator<AStaticMeshActor> ActorIter(World); ActorIter; ++ActorIter)
	{
		if (ActorIter->GetActorLabel() == DesiredActorLabel)
		{
			FoundActor = *ActorIter;
			break;
		}
	}

	if (FoundActor)
	{
		ChuteLocation = FoundActor->GetActorLocation();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Chute actor not found by label!"));
	}
}



void UBallSpawner::SpawnBall()
{
	//Spawn Ball
	ABallClass* newBall = NewObject<ABallClass>();
	FVector SpawnLocation = ChuteLocation;  
	SpawnLocation.Z += 5.0f;
	FRotator SpawnRotation = FRotator(0.f);     

	AStaticMeshActor* SphereActor = GetWorld()->SpawnActor<AStaticMeshActor>(SpawnLocation, SpawnRotation);
	if (SphereActor)
	{
		UStaticMeshComponent* MeshComp = SphereActor->GetStaticMeshComponent();
		MeshComp->SetMobility(EComponentMobility::Movable);
		MeshComp->SetStaticMesh(newBall->SphereMesh);
		MeshComp->SetSimulatePhysics(true);
		MeshComp->SetPhysMaterialOverride(PhysicalMaterial);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn the ball!"));
	}
	
	// Increment the counter each time the timer function is called.
	RepetitionCounter++;
	if (RepetitionCounter >= MaxRepetitions)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	}
	SpawnedActors.Add(newBall);
}


// Called every frame
void UBallSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

