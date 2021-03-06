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

	/**
	* Updates every frame.
	* @param DeltaTime: time of the game.
	*/
	void Tick(float DeltaTime) override;

	/**
	* Returns the actor once the melee attack is done.
	* @param Origin: init for the sphere trace.
	* @param End: end for the sphere trace.
	* @return Actor hitted.
	*/
	AActor* const MeleeAttack(const FVector& Origin, const FVector& End) const override;

private:
	/**
	* Given the names of the sockets that control the sphere trace, it gets if the enemy has hit an enemy.
	* @param Socket1: First socket name.
	* @param Socket2: Second socket name.
	*/
	AActor* const GetDamagedActor(const FString& Socket1, const FString& Socket2) const;

};
