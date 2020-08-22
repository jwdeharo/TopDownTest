#include "BTTask_Death.h"
#include "../../../../BaseEnemy.h"
#include "../../../BaseAIController.h"

UBTTask_Death::UBTTask_Death(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Play Death";
}

void UBTTask_Death::OnMontageEnded()
{
	ABaseAIController* AIController = Cast<ABaseAIController>(MyOwnerComp->GetAIOwner());
	if (AIController != nullptr)
	{
		ABaseEnemy* Enemy = Cast<ABaseEnemy>(AIController->GetPawn());
		if (Enemy != nullptr)
		{
			Enemy->Destroy();
		}
	}
}
