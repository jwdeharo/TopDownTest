#include "BTTask_Roar.h"

UBTTask_Roar::UBTTask_Roar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Play Roar";
}

EBTNodeResult::Type UBTTask_Roar::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = EBTNodeResult::Type::Succeeded;

	float RandomNumber = FMath::RandRange(1, 100);
	if (RandomNumber <= 80)
	{
		Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	}

	return Result;
}