#pragma once

#include "CoreMinimal.h"
#include "BTTask_PlayRandomMontage.h"
#include "BTTask_Attack.generated.h"

/**
 * Plays the attack montage and hits the player if he is in range.
 */
UCLASS()
class TOPDOWNTEST_API UBTTask_Attack : public UBTTask_PlayRandomMontage
{
	GENERATED_UCLASS_BODY()

	/**
	* Function called once the montage ends.
	*/
	virtual void OnMontageEnded();
};
