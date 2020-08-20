#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "GunWeapon.generated.h"

/**
 * Gun weapon that will throw ice projectiles. 
 */
UCLASS(Blueprintable)
class TOPDOWNTEST_API AGunWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	
public:

	/**
	* Sets default values for this actor's properties
	*/
	AGunWeapon();

	/**
	* Called when the game starts or when spawned
	*/
	void BeginPlay() override;

	/**
	* Shoot ice projectiles.
	*/
	void Attack() override;

	/**
	* Updates every frame.
	* @param DeltaTime: time of the game.
	*/
	void Tick(float DeltaTime) override;

	/**
	* Stops the attack.
	*/
	void StopAttack();

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	USkeletalMeshComponent* SkeletalMeshComponent; //!< Skeletal mesh component.


private:

	/**
	* Function called when it is possible to attack again.
	*/
	UFUNCTION()
	void OnAttackTimerEnded();

	FTimerHandle	AttackTimerController; //!< Timer that controls when the gun can be shoot.
	bool CanAttack; //!< Indicates if the gun can shoot.

};
