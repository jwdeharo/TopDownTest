#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

/**
* Abstract class that all weapons will implement.
*/
UCLASS()
class TOPDOWNTEST_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:

	/** 
	* Sets default values for this actor's properties
	*/
	ABaseWeapon();

	/**
	* Called every frame.
	* @param DeltaTime: time of the game.
	*/
	virtual void Tick(float DeltaTime) override;

	/**
	* Function that attacks depending on the weapon the character is carrying.
	*/
	virtual void Attack();

protected:

	/**
	* Called when the game starts or when spawned
	*/
	virtual void BeginPlay() override;
};
