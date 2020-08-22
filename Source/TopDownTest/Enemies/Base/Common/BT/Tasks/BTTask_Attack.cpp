#include "BTTask_Attack.h"
#include "../../../../BaseEnemy.h"
#include "../../../BaseAIController.h"

UBTTask_Attack::UBTTask_Attack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UBTTask_Attack::OnMontageEnded()
{
	ABaseAIController* AIController = Cast<ABaseAIController>(MyOwnerComp->GetAIOwner());
	if (AIController != nullptr)
	{
		ABaseEnemy* Enemy = Cast<ABaseEnemy>(AIController->GetPawn());
		if (Enemy != nullptr)
		{
			Enemy->StopAttack();
			Enemy->CleanDamageActors();
		}
	}

	Super::OnMontageEnded();
}