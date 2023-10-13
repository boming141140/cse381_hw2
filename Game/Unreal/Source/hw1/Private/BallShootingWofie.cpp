// Fill out your copyright notice in the Description page of Project Settings.


#include "BallShootingWofie.h"
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"
#include "EngineUtils.h"
#include "MyAIController.h"
#include "MyCharacter.h"
#include "Components/PrimitiveComponent.h"
#include "Animation/AnimSequence.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimInstance.h"
#include "BallClass.h"


// Sets default values
ABallShootingWofie::ABallShootingWofie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    // Load the mesh from the given directory
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/model/ourmodel/cse381hw1__1_.cse381hw1__1_'"));

    if (MeshAsset.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(MeshAsset.Object);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load mesh."));
    }
    static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationAsset(TEXT("AnimSequence'/Game/StarterContent/model/ourmodel/cse381hw1__1__Anim.cse381hw1__1__Anim'"));
    if (AnimationAsset.Succeeded())
    {
        ShootingAnimation = AnimationAsset.Object;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load animation."));
    }

    GetCapsuleComponent()->SetCapsuleHalfHeight(70);  // Half of 200
    GetCapsuleComponent()->SetCapsuleRadius(45);
    //GetCapsuleComponent()->SetRelativeLocation(FVector(0.0f, 0.0f, -32.0f));
    GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -100.0f));
    GetCharacterMovement()->MaxWalkSpeed = 300.f;
    health = 3;
    hasBall = false;
    ActualBall = nullptr;
    IsAlive = true;
}

// Called when the game starts or when spawned
void ABallShootingWofie::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABallShootingWofie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    FindTheClosetBall(GetWorld());
    DetectEnemy(GetWorld());
    CombatCheck();
    CheckDeath();
}

// Called to bind functionality to input
void ABallShootingWofie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABallShootingWofie::StartShootingAnimation()
{
    
    if (ShootingAnimation)
    {
        UE_LOG(LogTemp, Warning, TEXT("animation played"));
        GetMesh()->PlayAnimation(ShootingAnimation, false);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("no animation find"));
    }
}

void ABallShootingWofie::FindTheClosetBall(UWorld* world)
{
    ABallClass* ClosestBall = nullptr;
    float ClosestDistanceSquared = FLT_MAX;

    for (TActorIterator<ABallClass> It(GetWorld()); It; ++It)
    {
        float DistanceSquared = FVector::DistSquared(this->GetActorLocation(), It->GetActorLocation());
        if (DistanceSquared < ClosestDistanceSquared)
        {
            ClosestDistanceSquared = DistanceSquared;
            ClosestBall = *It;
        }
    }

    // If we found a ball, set it as the target for our AIController
    if (ClosestBall)
    {
        AMyAIController* AIController = Cast<AMyAIController>(GetController());
        if (AIController)
        {
            AIController->SetTarget(ClosestBall);
        }
    }
}

void ABallShootingWofie::DetectEnemy(UWorld* world)
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
    AMyAIController* AIController = Cast<AMyAIController>(GetController());
    if (AIController)
    {
        AIController->SetEnemy(ClosestEnemy);
    }
}

void ABallShootingWofie::CombatCheck() 
{
    AMyAIController* MyAI = Cast<AMyAIController>(GetController());
    if (MyAI)
    {
        // Access the variable
        AActor* enemy = MyAI->Enemy;
        
        // Do something with the variable
        if (enemy && hasBall && ActualBall)
        {
            // Stop moving (assuming you have AI movement)
            GetController()->StopMovement();
            FVector DirectionToEnemy = enemy->GetActorLocation() - GetActorLocation();
            FRotator FaceEnemyRotation = DirectionToEnemy.Rotation();
            SetActorRotation(FaceEnemyRotation);
            ShotBall(DirectionToEnemy);
            hasBall = false;
            ActualBall = nullptr;
            MyAI->hasBall = false;
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No AI controller associated with this character!"));
    }
    
}

void ABallShootingWofie::GetBall(ABallClass* ball)
{
    hasBall = true;
    AMyAIController* MyAI = Cast<AMyAIController>(GetController());
    if (MyAI)
    {
        MyAI->hasBall = true;
    }
    ActualBall = ball;
    ActualBall->SetActorHiddenInGame(true);
    ActualBall->SetActorEnableCollision(false);
}

void ABallShootingWofie::ShotBall(FVector Direction)
{
    Direction.Normalize();
    FVector ThrowPosition = this->GetActorLocation() + (Direction * 200);
    if (ActualBall)
    {
        ActualBall->SetActorLocation(ThrowPosition);
        ActualBall->SetActorHiddenInGame(false);
        ActualBall->SetActorEnableCollision(true);
        ActualBall->MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        if (ActualBall->MeshComponent->IsSimulatingPhysics())
        {
            float ForceMagnitudeX = 200000.0f; // adjust as needed
            float ForceMagnitudeY = 200000.0f;
            float ForceMagnitudeZ = 300000.0f;
            //UE_LOG(LogTemp, Warning, TEXT("Direction Before Multiply: %s"), *Direction.ToString());
            Direction.X *= ForceMagnitudeX;
            Direction.Y *= ForceMagnitudeY;
            Direction.Z *= ForceMagnitudeZ;
            StartShootingAnimation();
            ActualBall->MeshComponent->AddImpulse(Direction);
            //UE_LOG(LogTemp, Warning, TEXT("ResultantForce: %s"), *Direction.ToString());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("no physics find"));
        }
    }
}

void ABallShootingWofie::CheckDeath()
{
    if (health <= 0) {
        // Make sure it doesn't interact with anything
        SetActorEnableCollision(false);

        // Hide it from the game view
        SetActorHiddenInGame(true);

        // Optionally, you can deactivate any ticking to save performance
        SetActorTickEnabled(false);

        // Reset any related flags or pointers
        hasBall = false;
        ActualBall = nullptr;
        IsAlive = false;

    }   
}

float ABallShootingWofie::GetHealthPercent()
{
    return health / MaxHealth;
}


