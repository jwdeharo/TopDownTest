#include "SpiderController.h"
#include "SpiderAIController.h"

ASpiderController::ASpiderController()
{
	AIControllerClass = ASpiderAIController::StaticClass();
}