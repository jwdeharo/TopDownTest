#include "SpiderAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../BaseEnemy.h"
#include "Kismet/GameplayStatics.h"

ASpiderAIController::ASpiderAIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void ASpiderAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ABaseEnemy* Enemy = Cast<ABaseEnemy>(InPawn);

	if (Enemy != nullptr && Enemy->BehaviourTree != nullptr)
	{
		BlackboardComponent->InitializeBlackboard(*Enemy->BehaviourTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*Enemy->BehaviourTree);
		BlackboardComponent->SetValueAsObject("Player", UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
		BlackboardComponent->SetValueAsBool("HasToDie", false);
		Enemy->OnDeath.AddUObject(this, &ASpiderAIController::OnDeath);
	}
}

void ASpiderAIController::OnDeath()
{
	BlackboardComponent->SetValueAsBool("HasToDie", true);
	StopMovement();
}