// Fill out your copyright notice in the Description page of Project Settings.

#include "WolfieGuard.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "GuardAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimSequence.h"
#include "MyCharacter.h"

// Sets default values
AWolfieGuard::AWolfieGuard()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    // Local attribute
    health = 1;
    GetCharacterMovement()->MaxWalkSpeed = 450.f;
    // Create default components
    
    GetCapsuleComponent()->InitCapsuleSize(40.f, 90.f);
    GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
    GetCapsuleComponent()->SetSimulatePhysics(true);
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetCapsuleComponent()->BodyInstance.bEnableGravity = true;
    GetCapsuleComponent()->BodyInstance.bLockXRotation = true;
    GetCapsuleComponent()->BodyInstance.bLockYRotation = true;
    GetCapsuleComponent()->BodyInstance.bLockZRotation = true;

    // Create and set up the skeletal mesh component

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);  // Set to no collision as we want the capsule to handle it
    GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);

    CurrentHealth = 3;
    MaxHealth = 3;
    IsAlive = true;
    /*
    // Create and set up the capsule component for physics interactions
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule_Guard1"));
    RootComponent = CapsuleComponent;
    CapsuleComponent->InitCapsuleSize(40.f, 90.f);  // Adjust this based on the size of your character
    CapsuleComponent->SetCollisionProfileName(TEXT("Pawn"));
    CapsuleComponent->SetSimulatePhysics(true);
    CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CapsuleComponent->BodyInstance.bEnableGravity = true;
    CapsuleComponent->BodyInstance.bLockXRotation = true;
    CapsuleComponent->BodyInstance.bLockYRotation = true;
    CapsuleComponent->BodyInstance.bLockZRotation = true;

    // Create and set up the skeletal mesh component
    GuardMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent_Guard1"));
    GuardMeshComponent->SetupAttachment(RootComponent); // Attach skeletal mesh to capsule
    GuardMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);  // Set to no collision as we want the capsule to handle it
    GuardMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, 95));

    // Set the animation mode to use single animation node
    GuardMeshComponent->SetAnimationMode(EAnimationMode::AnimationSingleNode);

    // Assign the skeletal mesh asset
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(TEXT("/Game/StarterContent/model/teamq/team_q1.team_q1"));
    if (MeshFinder.Succeeded())
    {
        GuardMeshComponent->SetSkeletalMesh(MeshFinder.Object);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("FAILED TO LOAD MESH"));
    }

    // Load the animation sequence
    static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationFinder(TEXT("/Game/StarterContent/model/teamq/team_q1_Anim.team_q1_Anim"));
    if (AnimationFinder.Succeeded())
    {
        UE_LOG(LogTemp, Warning, TEXT("ANIMATION FOUND"));
        GuardAnimation = AnimationFinder.Object;

        if (GuardAnimation)
        {
            UE_LOG(LogTemp, Warning, TEXT("Setting Animation to Mesh Component"));
            GuardMeshComponent->SetAnimation(GuardAnimation);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("GuardAnimation is NULL"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ANIMATION NOT FOUND"));
    }
    */
}

// Called when the game starts or when spawned
void AWolfieGuard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWolfieGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    DetectEnemy(GetWorld());
}

void AWolfieGuard::SetupGuardMesh(const FString& MeshPath)
{
    //UE_LOG(LogTemp, Warning, TEXT("TRYING TO SETUP GUARD MESH"));

    TSoftObjectPtr<USkeletalMesh> MeshSoftReference = TSoftObjectPtr<USkeletalMesh>(FSoftObjectPath(MeshPath));
    if (USkeletalMesh* Meshes = MeshSoftReference.LoadSynchronous())
    {
        GetMesh()->SetSkeletalMesh(Meshes);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("FAILED TO LOAD MESH"));
    }
}

void AWolfieGuard::SetupGuardAnimation(const FString& AnimationPath)
{
    //UE_LOG(LogTemp, Warning, TEXT("TRYING TO SETUP GUARD ANIMATION"));

    TSoftObjectPtr<UAnimSequence> AnimationSoftReference = TSoftObjectPtr<UAnimSequence>(FSoftObjectPath(AnimationPath));
    if (UAnimSequence* LoadedAnimation = AnimationSoftReference.LoadSynchronous())
    {
        GetMesh()->SetAnimation(LoadedAnimation);
        GetMesh()->Play(true);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ANIMATION NOT FOUND"));
    }
}

void AWolfieGuard::DetectEnemy(UWorld* world)
{

    FVector MyLocation = GetActorLocation();
    TArray<FOverlapResult> OverlapResults;
    int32 DetectionRange = 900;
    // Get all actors overlapping the sphere
    // Create a collision query for only pawns (change if your enemy isn't derived from APawn)
    FCollisionObjectQueryParams ObjectQueryParams(ECollisionChannel::ECC_Pawn);

    // Perform the overlap
    world->OverlapMultiByObjectType(
        OverlapResults,
        MyLocation,
        FQuat::Identity,
        ObjectQueryParams,
        FCollisionShape::MakeSphere(DetectionRange)
    );

    AMyCharacter* ClosestEnemy = nullptr;
    float ClosestDistance = DetectionRange;

    for (const FOverlapResult& Result : OverlapResults)
    {
        AMyCharacter* PotentialEnemy = Cast<AMyCharacter>(Result.GetActor());
        if (PotentialEnemy)
        {
            float Distance = (PotentialEnemy->GetActorLocation() - MyLocation).Size();
            if (Distance < ClosestDistance)
            {
                ClosestDistance = Distance;
                ClosestEnemy = PotentialEnemy;
            }
        }
    }
    AGuardAIController* AIController = Cast<AGuardAIController>(GetController());
    if (AIController) {
        AIController->SetTarget(ClosestEnemy);
    }
}

void  AWolfieGuard::CheckDeath()
{
    if (health <= 0) {
        // Make sure it doesn't interact with anything
        SetActorEnableCollision(false);

        // Hide it from the game view
        SetActorHiddenInGame(true);

        // Optionally, you can deactivate any ticking to save performance
        SetActorTickEnabled(false);

    }
}
float AWolfieGuard::GetHealthPercent()
{
    return (CurrentHealth / MaxHealth);
}

