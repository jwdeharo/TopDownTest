#include "TopDownTestPlayerController.h"
#include "TopDownTestCharacter.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"

ATopDownTestPlayerController::ATopDownTestPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATopDownTestPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bCanRotateToLocation = false;
}

void ATopDownTestPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bCanRotateToLocation)
	{
		ChangePlayerRotation();
	}
}

void ATopDownTestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATopDownTestPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATopDownTestPlayerController::MoveRight);

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ATopDownTestPlayerController::ChangeCanRotateLocation);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ATopDownTestPlayerController::ChangeCanRotateLocation);
}

void ATopDownTestPlayerController::MoveForward(float AxisValue)
{
	Move(AxisValue, EAxis::X);
}

void ATopDownTestPlayerController::MoveRight(float AxisValue)
{
	Move(AxisValue, EAxis::Y);
}

void ATopDownTestPlayerController::Move(float AxisValue, EAxis::Type AxisType)
{
	ATopDownTestCharacter* MyPawn = Cast<ATopDownTestCharacter>(GetPawn());
	FRotator Rotation = MyPawn->GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(AxisType);
	MyPawn->AddMovementInput(Direction, AxisValue);
}

void ATopDownTestPlayerController::ChangeCanRotateLocation()
{
	bCanRotateToLocation = !bCanRotateToLocation;
}

void ATopDownTestPlayerController::ChangePlayerRotation()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		ATopDownTestCharacter* MyPawn = Cast<ATopDownTestCharacter>(GetPawn());

		if (MyPawn != nullptr)
		{
			if (MyPawn->GetCursorToWorld())
			{
				RotateToLocation(MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			RotateToLocation(Hit.ImpactPoint);
		}
	}
}

void ATopDownTestPlayerController::RotateToLocation(const FVector& Location)
{
	const FRotator& FindLookAt = UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), Location);
	FRotator LookAtRotation = FRotator(0.f, FindLookAt.Yaw, 0.f);
	GetPawn()->SetActorRotation(LookAtRotation);
}