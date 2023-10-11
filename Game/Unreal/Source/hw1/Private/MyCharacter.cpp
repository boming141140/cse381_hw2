// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PickupComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BallClass.h"
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a static mesh component
	UStaticMeshComponent* CharacterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->SetRelativeLocation(FVector(0, 0, -88));

	// Load a mesh. Note: Replace 'PathToYourMesh' with the actual path to your mesh.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	if (MeshAsset.Succeeded())
	{
		CharacterMesh->SetStaticMesh(MeshAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("mesh not found"));
	}
	CharacterMesh->SetupAttachment(RootComponent); // Attach the mesh to the root component (CapsuleComponent)

	// Instantiating your class Components
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	//Set the location and rotation of the Character Mesh Transform
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));

	// Attaching your class Components to the default character's Skeletal Mesh Component.
	CameraComp->SetupAttachment(RootComponent);

	// Setup the collision for the character's capsule component
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);

	// Assuming that your CharacterMesh is meant to also interact with objects, set its collision as well
	CharacterMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CharacterMesh->SetNotifyRigidBodyCollision(true);

	// Optional: If you want more detailed control over what the capsule and mesh collide with,
	// you can set the collision profiles here. E.g.,
	// GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	// CharacterMesh->SetCollisionProfileName(TEXT("Pawn"));

	//Initialize PickupComponent
	//PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("PickupComponent"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnPlayerOverlapBegin);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Bind movement functions
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	// Bind jump functions
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

}

void AMyCharacter::MoveForward(float AxisValue)
{
	if ((Controller != nullptr) && (AxisValue != 0.0f))
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);
	}
}

void AMyCharacter::MoveRight(float AxisValue)
{
	if ((Controller != nullptr) && (AxisValue != 0.0f))
	{
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement in that direction
		AddMovementInput(Direction, AxisValue);
	}
}

void AMyCharacter::AttemptPickup(AActor* BallToPickup)
{
	// Log that we entered the function
	UE_LOG(LogTemp, Warning, TEXT("AttemptPickup called."));

	// Check if the player is already holding a ball
	if (HeldBall)
	{
		// Log that the player is already holding a ball
		UE_LOG(LogTemp, Warning, TEXT("Player is already holding a ball."));
		return;
	}
    HeldBall = Cast<ABallClass>(BallToPickup);

    // Optional: Make the ball a child of the character so it moves with the character
    BallToPickup->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

    // Optional: Set the ball invisible or change its position to indicate it's being held
    // For example, if it's a static mesh:
    UStaticMeshComponent* BallMesh = BallToPickup->FindComponentByClass<UStaticMeshComponent>();
    if (BallMesh)
    {
        BallMesh->SetVisibility(false);
    }
}

void AMyCharacter::OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the other actor is a ball
	ABallClass* Ball = Cast<ABallClass>(OtherActor);
	if (Ball)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Player overlapped with ball!"));
	}
}
