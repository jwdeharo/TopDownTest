#pragma once

#include "CoreMinimal.h"
#include "../Base/BaseAIController.h"
#include "SpiderAIController.generated.h"

/**
 * Spider AI Controller.
 */
UCLASS()
class TOPDOWNTEST_API ASpiderAIController : public ABaseAIController
{
	GENERATED_BODY()
	
public:

	/**
	* Sets the default vars.
	*/
	ASpiderAIController();

protected:

	/** 
	* Function called when the pawn has been possessed.
	*/
	void OnPossess(APawn* InPawn) override;

private:

	/**
	* Function called once the pawn possesed by this controller dies.
	*/
	void OnDeath();
};
