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

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	USkeletalMeshComponent* SkeletalMeshComponent; //!< Skeletal mesh component.
};
