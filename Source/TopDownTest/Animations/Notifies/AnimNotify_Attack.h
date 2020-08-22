#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Containers/Array.h"
#include "../../Enemies/Base/Common/CommonData.h"
#include "AnimNotify_Attack.generated.h"

/**
 * Once notified, it throws a trace to know if the player can be attacked.
 */
UCLASS()
class TOPDOWNTEST_API UAnimNotify_Attack : public UAnimNotify
{
	GENERATED_BODY()
	
	/**
	* Notifies the exact frame of the animation montage.
	* @param MeshComp: Skeletal mesh component.
	* @param Animation: Current animation.
	*/
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere, Category = "AnimNotify")
	TEnumAsByte<EPartAttack::Type> PartAttack; //!< Indicates the part of the body that is attacking.

};
