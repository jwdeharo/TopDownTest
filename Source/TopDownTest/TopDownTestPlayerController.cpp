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
		ATopDownTestCharacter* MyPawn = Cast<ATopDownTestCharacter>(GetPawn());
		if (MyPawn != nullptr)
		{
			MyPawn->Attack();
		}
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
	ATopDownTestCharacter* MyPawn = Cast<ATopDownTestCharacter>(GetPawn());
	if (MyPawn != nullptr)
	{
		MyPawn->MoveForward(AxisValue);
	}
}

void ATopDownTestPlayerController::MoveRight(float AxisValue)
{
	ATopDownTestCharacter* MyPawn = Cast<ATopDownTestCharacter>(GetPawn());
	if (MyPawn != nullptr)
	{
		MyPawn->MoveRight(AxisValue);
	}
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
				MyPawn->RotateToLocation(MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		ATopDownTestCharacter* MyPawn = Cast<ATopDownTestCharacter>(GetPawn());
		if (MyPawn != nullptr)
		{
			FHitResult Hit;
			GetHitResultUnderCursor(ECC_Visibility, false, Hit);

			if (Hit.bBlockingHit)
			{
				MyPawn->RotateToLocation(Hit.ImpactPoint);
			}
		}
	}
}