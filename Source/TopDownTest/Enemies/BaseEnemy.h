// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

	UPROPERTY(EditAnywhere, Category = "AI Controller")
	class UBehaviorTree* BehaviourTree; //!< Behavior Tree.

};
