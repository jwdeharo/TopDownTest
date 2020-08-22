#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownTestPlayerController.generated.h"

/**
* Controller that handles the inputs of the player.
*/
UCLASS()
class ATopDownTestPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/**
	* Default constructor of the class.
	*/
	ATopDownTestPlayerController();

protected:
	/**
	* Function called at the begining of the game.
	*/
	void BeginPlay() override;

	/**
	* Updates the player every frame.
	* @param DeltaTime: time of the game.
	*/
	void PlayerTick(float DeltaTime) override;

	/**
	* Setups the input that the controller will handle.
	*/
	void SetupInputComponent() override;

	void SetAttack();
	void SetNotAttack();

private:

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
	* Changes if the player can rotate to a location.
	*/
	void ChangeCanRotateLocation();

	/**
	* Rotates the player to the touch position.
	*/
	void ChangePlayerRotation();

	bool bCanRotateToLocation; //!< Indicates that the character can look at the location.
};


