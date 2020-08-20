#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * AIController Interface that will have the behavior tree and the blackboard.
 */
UCLASS()
class TOPDOWNTEST_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
	class UBehaviorTree* BehaviourTree;

	UPROPERTY()
	class UBlackboardData* BlackboardData;

	UPROPERTY()
	class UBlackboardComponent* BlackboardComponent;

};
