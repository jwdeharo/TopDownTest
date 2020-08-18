#include "TopDownTestPlayerController.h"
#include "TopDownTestCharacter.h"
#include "Engine/World.h"

ATopDownTestPlayerController::ATopDownTestPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATopDownTestPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ATopDownTestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATopDownTestPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATopDownTestPlayerController::MoveRight);
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