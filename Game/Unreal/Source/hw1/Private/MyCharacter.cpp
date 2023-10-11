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

	//Setting class variables of the Character movement component

	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	GetCharacterMovement()->bIgnoreBaseRotation = true;

	//Initialize PickupComponent
	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("PickupComponent"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

void AMyCharacter::AttemptPickup(ABallClass* BallToPickup)
{
	if (PickupComponent && BallToPickup)
	{
		PickupComponent->PickupBall(BallToPickup);
		// You can implement further logic here, e.g. add points to the player
	}
}
