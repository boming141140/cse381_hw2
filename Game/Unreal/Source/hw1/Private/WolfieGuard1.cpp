// Fill out your copyright notice in the Description page of Project Settings.


#include "WolfieGuard1.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequence.h"

// Sets default values
AWolfieGuard1::AWolfieGuard1()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and set up the skeletal mesh component
    GuardMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GuardMeshComponent"));
    RootComponent = GuardMeshComponent;

    // Assign the skeletal mesh asset
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(TEXT("SkeletalMesh'/Game/StarterContent/model/teamq/team_q1.team_q1'"));
    if (MeshFinder.Succeeded())
    {
        GuardMeshComponent->SetSkeletalMesh(MeshFinder.Object);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("FAILED TO LOAD MESH"));
    }

    // Load the animation sequence
    static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationFinder(TEXT("AnimSequence'/Game/StarterContent/model/teamq/team_q1_Anim.team_q1_Anim'"));
    if (AnimationFinder.Succeeded())
    {
        GuardAnimation = AnimationFinder.Object;
        GuardMeshComponent->PlayAnimation(GuardAnimation, true);
    }

}

// Called when the game starts or when spawned
void AWolfieGuard1::BeginPlay()
{
    Super::BeginPlay();
    PlayGuardAnimation();
}

// Called every frame
void AWolfieGuard1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWolfieGuard1::PlayGuardAnimation()
{
    if (GuardMeshComponent && GuardAnimation)
    {
        GuardMeshComponent->PlayAnimation(GuardAnimation, true);
    }
}

