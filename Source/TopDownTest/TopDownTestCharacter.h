#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownTestCharacter.generated.h"

class ABaseWeapon;

UCLASS(Blueprintable)
class ATopDownTestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATopDownTestCharacter();

	/**
	* Function called at the begining of the game.
	*/
	void BeginPlay() override;

	// Called every frame.
	void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	/**
	* Moves the player in his forward direction.
	* @param AxisValue: Value of the axis input.
	*/
	void MoveForward(float AxisValue);

	/**
	* Moves the player in his right direction.
	* @param AxisValue: Value of the axis input.
	*/
	void MoveRight(float AxisValue);

	/**
	* Given a location, the function rotates the player to look at that location.
	* @param: Location: touch location.
	*/
	void RotateToLocation(const FVector& Location);

	/**
	* Attacks using the main weapon.
	*/
	void Attack();

	/**
	* Sets if the character can or can't attack.
	* @param CanAttack: true if the character can attack.
	*/
	void SetCanAttack(bool CanAttack);

	/**
	* Receive damage with some potency.
	* @param Potency: potency of the damage.
	*/
	void ReceiveDamage(float Potency);

	/**
	* Returns the current health.
	* @return Current health.
	*/
	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	/**
	* Returns the max health.
	* @return Max Health.
	*/
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UPROPERTY(EditDefaultsOnly, Category = "Character Controller")
	TSubclassOf<ABaseWeapon> MainWeaponType; //!< Main weapon of the character.

	UPROPERTY(EditDefaultsOnly, Category = "Character Controller")
	float MaxHealth; //!< Max health of the character.

private:

	/**
	* Given an axis value and an axis type, this function moves the player.
	* @param AxisValue: Value of the axis input.
	* @param AxisType: Enum value that indicates the axis.
	*/
	void Move(float AxisValue, EAxis::Type AxisType);

	/**
	* Attach an object to a socket.
	* @param SocketToAttach: socket to attach the object.
	* @param ObjectToAttach: object type to attach.
	*/
	template<typename T, typename V>
	T* AttachBlueprint(const FName& SocketToAttach, TSubclassOf<V> ObjectToAttach)
	{
		T* SpawnedActor = GetWorld()->SpawnActor<T>(ObjectToAttach);
		SpawnedActor->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketToAttach);
		return SpawnedActor;
	}

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	UPROPERTY()
	ABaseWeapon* MainWeapon; //!< Main weapon of the character.

	UPROPERTY(transient)
	float CurrentHealth;	//!< Current health of the character.

	bool bCanAttack; //!< Indicates that the player can attack.
};

