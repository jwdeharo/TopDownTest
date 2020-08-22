#include "BTTask_PlayRandomMontage.h"
#include "../../../BaseAIController.h"
#include "GameFramework/Character.h"

UBTTask_PlayRandomMontage::UBTTask_PlayRandomMontage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Play Random Montage";
	bCreateNodeInstance = true;

	TimerDelegate = FTimerDelegate::CreateUObject(this, &UBTTask_PlayRandomMontage::OnMontageEnded);
}

EBTNodeResult::Type UBTTask_PlayRandomMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseAIController* AIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	if (AIController != nullptr)
	{
		TimerHandle.Invalidate();
		MyOwnerComp = &OwnerComp;

		ACharacter* const MyCharacter = Cast<ACharacter>(AIController->GetPawn());
		if (MyCharacter != nullptr)
		{
			UAnimMontage* RandomMontageToPlay = AnimationMontagesToPlay[FMath::RandRange(0, AnimationMontagesToPlay.Num() - 1)];
			MyCharacter->PlayAnimMontage(RandomMontageToPlay);
			float FinishDelay = RandomMontageToPlay->GetMaxCurrentTime();
			if (FinishDelay > 0.f)
			{
				MyCharacter->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, FinishDelay, false);
				Result = EBTNodeResult::InProgress;
			}
			else
			{
				Result = EBTNodeResult::Succeeded;
			}
		}
	}

	return Result;
}

void UBTTask_PlayRandomMontage::OnMontageEnded()
{
	if (MyOwnerComp != nullptr)
	{
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
	}
}

