#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PlayRandomMontage.generated.h"

/**
 * Plays a random montage.
 */
UCLASS()
class TOPDOWNTEST_API UBTTask_PlayRandomMontage : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

protected:

	/**
	* Executes the task.
	* @param OwnerComp: Behavior Tree Component of the character.
	* @param NodeMemory: Memory to store information.
	* @return EBTNodeResult::Type: Succeeded once the task has finished.
	*/
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/**
	* Function called once the montage ends.
	*/
	virtual void OnMontageEnded();

	UPROPERTY(Category = Node, EditAnywhere)
	TArray<UAnimMontage*> AnimationMontagesToPlay; //!< Montages to play.

	UPROPERTY()
	UBehaviorTreeComponent* MyOwnerComp;	//!< Behavior tree component.

	FTimerDelegate TimerDelegate; //!< Delegate that contains the function which will be called.
	FTimerHandle TimerHandle;		//!< Timer set to the montage duration.
	
};
