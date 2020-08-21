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
	class UBlackboardComponent* BlackboardComponent; //!< Blackboard component.

	UPROPERTY()
	class UBehaviorTreeComponent* BehaviorTreeComponent; //!< Behavior tree component.

};
