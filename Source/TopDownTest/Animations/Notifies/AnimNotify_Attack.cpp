#include "AnimNotify_Attack.h"
#include "../../Enemies/BaseEnemy.h"

void UAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABaseEnemy* const Enemy = Cast<ABaseEnemy>(MeshComp->GetOwner());

	if (Enemy != nullptr)
	{
		Enemy->NotifyAttack(PartAttack);
	}
}