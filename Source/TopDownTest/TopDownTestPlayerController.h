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
	* Updates the player every frame.
	* @param DeltaTime: time of the game.
	*/
	void PlayerTick(float DeltaTime) override;

	/**
	* Setups the input that the controller will handle.
	*/
	virtual void SetupInputComponent() override;

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
	* Given an axis value and an axis type, this function moves the player.
	* @param AxisValue: Value of the axis input.
	* @param AxisType: Enum value that indicates the axis.
	*/
	void Move(float AxisValue, EAxis::Type AxisType);
};


