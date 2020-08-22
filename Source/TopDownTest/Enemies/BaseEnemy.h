#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Base/Common/CommonData.h"
#include "BaseEnemy.generated.h"

UCLASS()
class TOPDOWNTEST_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	/**
	* Sets default values for this character's properties
	*/ 
	ABaseEnemy();

	/**
	* Function called at the begining of the game.
	*/
	virtual	void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "AI Controller")
	class UBehaviorTree* BehaviourTree; //!< Behavior Tree.

	UPROPERTY(EditAnywhere, Category = "Enemy Controller")
	float AttackPotency; //!< Melee attack potency.

	UPROPERTY(EditAnywhere, Category = "Enemy Controller")
	float MaxHealth;	//!< Max health of the enemy.

	UPROPERTY(transient)
	float CurrentHealth;	//!< Current health of the enemy.

	/**
	* Given two points, the function uses a Sphere Trace to detect the player and attack him.
	* @param PartAttack: where the attack comes from.
	*/
	virtual void NotifyAttack(EPartAttack::Type PartAttack);
	
	/**
	* Returns the actor once the melee attack is done.
	* @param Origin: init for the sphere trace.
	* @param End: end for the sphere trace.
	* @return Actor hitted.
	*/
	virtual AActor* const MeleeAttack(const FVector& Origin, const FVector& End) const;

	/**
	* Adds an actor to the container of damage actors.
	* @param DamagedActor: actor that has been damaged.
	*/
	void DamageActor(AActor* const DamagedActor);

	/**
	* Cleans the damage actors' container.
	*/
	void CleanDamageActors();

	/**
	* Stops the attack.
	*/
	void StopAttack();

	/**
	* Indicates if an actor has already been damaged.
	* @param Actor: actor to check.
	* @return True if the actor has already been damaged.
	*/
	bool IsActorDamaged(AActor* const Actor) const;

	/**
	* Gets the current health.
	* @return Current health.
	*/
	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	/**
	* Gets the max health.
	* @return max health.
	*/
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	/**
	* Receive damage.
	* @param potency: potency of the damage.
	*/
	void ReceiveDamage(float Potency);

protected:
	bool IsAttacking;											//!< Indicates if we can attack.
	EPartAttack::Type CurrentAttackPart;	//!< Indicates where the attack comes from.
	TArray<AActor*> AlreadyDamagedActors;	//!< Container with the damaged actors.

};
