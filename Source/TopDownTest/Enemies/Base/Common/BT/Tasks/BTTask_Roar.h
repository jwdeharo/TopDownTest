#pragma once

#include "CoreMinimal.h"
#include "BTTask_PlayRandomMontage.h"
#include "BTTask_Roar.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNTEST_API UBTTask_Roar : public UBTTask_PlayRandomMontage
{
	GENERATED_UCLASS_BODY()

	/**
	* Executes the task.
	* @param OwnerComp: Behavior Tree Component of the character.
	* @param NodeMemory: Memory to store information.
	* @return EBTNodeResult::Type: Succeeded once the task has finished.
	*/
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
