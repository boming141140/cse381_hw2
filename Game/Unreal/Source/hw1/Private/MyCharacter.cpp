// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "BallClass.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyHUD.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Adjust the capsule component properties if necessary
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 88.0f); 
	// Create a static mesh component
	UStaticMeshComponent* CharacterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->SetupAttachment(RootComponent); // Attach the mesh to the root component (CapsuleComponent)
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

	// Instantiating your class Components

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	// Attaching your class Components to the default character's Skeletal Mesh Component.

	CameraComp->SetupAttachment(RootComponent);


	//Setting class variables of the Character movement component

	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	GetCharacterMovement()->bIgnoreBaseRotation = true;

	// A ball holder

	hasBall = false;
	ActualBall = nullptr;
	HealthPoints = 10;

	//Set meshComponent for ball holder
	MeshComponentForCharacter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponentForCharacter"));
	MeshComponentForCharacter->SetupAttachment(RootComponent);

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	CurrentHealth = 5;
	MaxHealth = 5;
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
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		// Set the mouse position to the center of the screen.
		/*FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		PC->SetMouseLocation(ViewportSize.X / 2, ViewportSize.Y / 2);
		*/
	}
	CheckDead();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Bind movement functions
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::PitchInput);
	// Bind jump functions
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Shoot Ball
	PlayerInputComponent->BindAction("ShootBall", IE_Pressed, this, &AMyCharacter::HandleShootBall);
}

void AMyCharacter::PitchInput(float val) 
{
	if (CameraComp)
	{
		FRotator NewRotation = CameraComp->GetRelativeRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch - val, -80.0f, 80.0f);  // Clamping to avoid full rotation
		CameraComp->SetRelativeRotation(NewRotation);
	}
}

void AMyCharacter::HandleShootBall()
{
	UE_LOG(LogTemp, Warning, TEXT("shooted"));
	if (hasBall && ActualBall)
	{
		FVector ThrowPosition = this->GetActorLocation() + (CameraComp->GetForwardVector() * 100);
		ActualBall->SetActorLocation(ThrowPosition);
		ActualBall->SetActorHiddenInGame(false);
		ActualBall->SetActorEnableCollision(true);
		ActualBall->MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MeshComponentForCharacter->SetStaticMesh(nullptr);
		// Call your shooting function
		ShootBallInScreenCenterDirection(ActualBall->MeshComponent);
		hasBall = false; // Assuming the ball is "used up" after shooting
		ActualBall = nullptr;
	}
}

void AMyCharacter::GetBall(ABallClass* ball)
{
	hasBall = true;
	ActualBall = ball;
	MeshComponentForCharacter->SetStaticMesh(ball->MeshComponent->GetStaticMesh());
	OriginalScale = ball->MeshComponent->GetComponentScale();
	MeshComponentForCharacter->SetRelativeScale3D(FVector(0.2f));
	MeshComponentForCharacter->SetRelativeLocation(FVector(30, 20, -10));
	ActualBall->SetActorHiddenInGame(true);
	ActualBall->SetActorEnableCollision(false);
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

void AMyCharacter::ShootBallInScreenCenterDirection(UStaticMeshComponent* Ball)
{
	if (!Ball)
		return;
		// Now you can access functions or variables inside MyPC
		FVector Direction = GetScreenToWorldDirection();

		Direction.Normalize();
		UE_LOG(LogTemp, Warning, TEXT("MyVector: %s"), *Direction.ToString());
		if (Ball->IsSimulatingPhysics())
		{
			float ForceMagnitudeX = 200000.0f; // adjust as needed
			float ForceMagnitudeY = 100000.0f;
			float ForceMagnitudeZ = 500000.0f;
			UE_LOG(LogTemp, Warning, TEXT("Direction Before Multiply: %s"), *Direction.ToString());
			Direction.X *= ForceMagnitudeX;
			Direction.Y *= ForceMagnitudeY;
			Direction.Z *= ForceMagnitudeZ;
			Ball->AddImpulse(Direction);
			UE_LOG(LogTemp, Warning, TEXT("ResultantForce: %s"), *Direction.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("no physics find"));
		}
	
	
}

FVector AMyCharacter::GetScreenToWorldDirection()
{
	// Get yaw from the character's rotation
	float Yaw = GetActorRotation().Yaw;

	// Get pitch from the camera's relative rotation
	float Pitch = CameraComp->GetRelativeRotation().Pitch;

	// Create a combined rotation
	FRotator CombinedRotation = FRotator(Pitch, Yaw, 0.0f);

	// Convert the rotation to a direction vector
	FVector AimDirection = CombinedRotation.Vector();

	return AimDirection;
}

float AMyCharacter::GetHealthPercent()
{
	return CurrentHealth / MaxHealth;
}

void AMyCharacter::CheckDead()
{
	if (CurrentHealth <= 0)
	{
		AMyHUD* MyHUDInstance = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (MyHUDInstance)
		{
			MyHUDInstance->SetGameOver(true);
		}
	}
}
