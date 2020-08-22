#pragma once

#include "CoreMinimal.h"
#include "BTTask_PlayRandomMontage.h"
#include "BTTask_Death.generated.h"

/**
 * Destroys the pawn after the montage.
 */
UCLASS()
class TOPDOWNTEST_API UBTTask_Death : public UBTTask_PlayRandomMontage
{
	GENERATED_UCLASS_BODY()

	/**
	* Function called once the montage ends.
	*/
	virtual void OnMontageEnded();
	
};
