#include "SpiderAIController.h"
#include "BehaviorTree/BehaviorTree.h"

ASpiderAIController::ASpiderAIController()
{
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObject(TEXT("/Game/TopDownCPP/Blueprints/Enemies/Spider/SpiderBehaviorTree"));
	BehaviourTree = BehaviorTreeObject.Object;
}

void ASpiderAIController::BeginPlay()
{
	Super::BeginPlay();
}