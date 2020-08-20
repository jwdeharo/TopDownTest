#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownTestCharacter.generated.h"

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
	*/
	template <typename T>
	T* AttachBlueprint(const FName& SocketToAttach)
	{
		T* SpawnedActor = GetWorld()->SpawnActor<T>(T::StaticClass());
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
	class ABaseWeapon* MainWeapon; //!< Main weapon of the character.
};

