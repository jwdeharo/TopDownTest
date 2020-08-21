#include "SpiderController.h"
#include "SpiderAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASpiderController::ASpiderController()
{
	GetCharacterMovement()->MaxWalkSpeed = 260.f;
}