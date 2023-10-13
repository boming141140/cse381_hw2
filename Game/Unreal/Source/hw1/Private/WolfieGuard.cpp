// Fill out your copyright notice in the Description page of Project Settings.

#include "WolfieGuard.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimSequence.h"

// Sets default values
AWolfieGuard::AWolfieGuard()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create default components
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule_Guard"));
    GuardMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent_Guard"));
    CapsuleComponent->InitCapsuleSize(40.f, 90.f);
    CapsuleComponent->SetCollisionProfileName(TEXT("Pawn"));
    CapsuleComponent->SetSimulatePhysics(true);
    CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CapsuleComponent->BodyInstance.bEnableGravity = true;
    CapsuleComponent->BodyInstance.bLockXRotation = true;
    CapsuleComponent->BodyInstance.bLockYRotation = true;
    CapsuleComponent->BodyInstance.bLockZRotation = true;
    RootComponent = CapsuleComponent;

    // Create and set up the skeletal mesh component

    GuardMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent_Guard1"));
    GuardMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);  // Set to no collision as we want the capsule to handle it
    GuardMeshComponent->SetAnimationMode(EAnimationMode::AnimationSingleNode);
    GuardMeshComponent->SetupAttachment(RootComponent); // Attach skeletal mesh to capsule

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

}

void AWolfieGuard::SetupGuardMesh(const FString& MeshPath)
{
    //UE_LOG(LogTemp, Warning, TEXT("TRYING TO SETUP GUARD MESH"));

    TSoftObjectPtr<USkeletalMesh> MeshSoftReference = TSoftObjectPtr<USkeletalMesh>(FSoftObjectPath(MeshPath));
    if (USkeletalMesh* Mesh = MeshSoftReference.LoadSynchronous())
    {
        GuardMeshComponent->SetSkeletalMesh(Mesh);
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
        GuardMeshComponent->SetAnimation(LoadedAnimation);
        GuardMeshComponent->Play(true);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ANIMATION NOT FOUND"));
    }
}

