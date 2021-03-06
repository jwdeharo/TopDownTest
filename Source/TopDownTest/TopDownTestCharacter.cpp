#include "TopDownTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapons/BaseWeapon.h"
#include "Weapons/GunWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Enemies/BaseEnemy.h"
#include "Enemies/EnemySpawnerController.h"

ATopDownTestCharacter::ATopDownTestCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATopDownTestCharacter::BeginPlay()
{
	Super::BeginPlay();
	MainWeapon = AttachBlueprint<AGunWeapon, ABaseWeapon>("GunSocket", MainWeaponType);
	bCanAttack = false;
	CurrentHealth = MaxHealth;
}

void ATopDownTestCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}

	if (bCanAttack)
	{
		Attack();
	}
}

void ATopDownTestCharacter::MoveForward(float AxisValue)
{
	Move(AxisValue, EAxis::X);
}

void ATopDownTestCharacter::MoveRight(float AxisValue)
{
	Move(AxisValue, EAxis::Y);
}

void ATopDownTestCharacter::Move(float AxisValue, EAxis::Type AxisType)
{
	FRotator Rotation = GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(AxisType);
	AddMovementInput(Direction, AxisValue);
}

void ATopDownTestCharacter::RotateToLocation(const FVector& Location)
{
	const FRotator& FindLookAt = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location);
	FRotator LookAtRotation = FRotator(0.f, FindLookAt.Yaw, 0.f);
	SetActorRotation(LookAtRotation);
}

void ATopDownTestCharacter::Attack()
{
	if (MainWeapon != nullptr)
	{
		MainWeapon->Attack();
	}
}

void ATopDownTestCharacter::SetCanAttack(bool CanAttack)
{
	bCanAttack = CanAttack;
}

void ATopDownTestCharacter::ReceiveDamage(float Potency)
{
	if ((CurrentHealth - Potency) > 0.f)
	{
		CurrentHealth -= Potency;
	}
	else
	{
		TArray<AActor*> Spawners, ToDelete;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnerController::StaticClass(), Spawners);
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseEnemy::StaticClass(), ToDelete);

		for (AActor* Spawner : Spawners)
		{
			Cast<AEnemySpawnerController>(Spawner)->StopTimer();
			Spawner->Destroy();
		}

		for (AActor* ActorToDelete : ToDelete)
		{
			ActorToDelete->Destroy();
		}
		MainWeapon->Destroy();
		CurrentHealth = 0.f;
	}
}

float ATopDownTestCharacter::GetCurrentHealth() const
{
	return CurrentHealth;
}

float ATopDownTestCharacter::GetMaxHealth() const
{
	return MaxHealth;
}