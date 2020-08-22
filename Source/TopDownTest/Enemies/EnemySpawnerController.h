#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnerController.generated.h"

class ABaseEnemy;	//!< Forward declaration of the ABaseEnemy.
class UBoxComponent; //!< Forward declaration of the UBoxComponent.

/**
* Class that spawns the specific enemy set by the user.
*/
UCLASS(Blueprintable)
class TOPDOWNTEST_API AEnemySpawnerController : public AActor
{
	GENERATED_BODY()
	
public:	
	/**
	* Sets default values for this actor's properties.
	*/
	AEnemySpawnerController();

	/** 
	* Called every frame.
	* @float DeltaTime: Time of the game.
	*/
	void Tick(float DeltaTime) override;

	/**
	* Stops the timer.
	*/
	void StopTimer();

	UPROPERTY(EditDefaultsOnly, Category = "Enemy Spawner")
	TSubclassOf<ABaseEnemy> EnemyToSpawn;	//!< Type of enemy that the spawner will spawn.

	UPROPERTY(EditAnywhere, Category = "Enemy Spawner")
	UBoxComponent* BoxCollisionComponent; //!< Box collision component.

	UPROPERTY(EditDefaultsOnly, Category = "Enemy Spawner")
	int32 MaxSpawnableEnemies;						//!< Max number of enemies in game.

	UPROPERTY(EditDefaultsOnly, Category = "Enemy Spawner")
	float MinSpawnTime;						//!< Minimum time to spawn an enemy

	UPROPERTY(EditDefaultsOnly, Category = "Enemy Spawner")
	float MaxSpawnTime;						//!< Max time to spawn an enemy.

protected:
	/**
	* Called when the game starts or when spawned.
	*/
	void BeginPlay() override;

private:

	/**
	* Given a minimum and maximum time by the user, it starts the timer to spawn enemies.
	*/
	void StartTimer();

	/**
	* Function called every time the spawn timer finishes. It spawns an enemy and restart the timer.
	*/
	UFUNCTION()
	void OnSpawnTimerFinished();

	/**
	* Function called when a pawn dies.
	*/
	void OnDeath();

	/**
	* Calculates the spawn transform in the bound collision area.
	* @return FTransform: transform of the spawned enemy.
	*/
	FTransform CalculateSpawnedEnemyTransform() const;

	/**
	* Gets a point on the floor given an InitPosition.
	* @param InitPosition: Random position.
	* @return FVector: position on the floor.
	*/
	FVector GetFloorPoint(const FVector& InitPosition) const;

	FTimerHandle	SpawnTimer;						//!< Controls when an enemy can spawn.
	int32					CurrentEnemiesNumber;	//!< Current number of enemies in game.
};
