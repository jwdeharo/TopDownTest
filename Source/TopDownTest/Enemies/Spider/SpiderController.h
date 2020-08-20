#pragma once

#include "CoreMinimal.h"
#include "../BaseEnemy.h"
#include "SpiderController.generated.h"

/**
 * Spider controller.
 */
UCLASS()
class TOPDOWNTEST_API ASpiderController : public ABaseEnemy
{
	GENERATED_BODY()

public:
	/**
	* Sets the defaults vars.
	*/
	ASpiderController();

};
