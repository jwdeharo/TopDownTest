#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

/**
* Base class for the projectiles.
*/
UCLASS(Blueprintable)
class TOPDOWNTEST_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	/**
	* Sets default values for this actor's properties.
	*/
	ABaseProjectile();

	/**
	* Called every frame.
	* @param DeltaTime: game's time.
	*/
	virtual void Tick(float DeltaTime) override;

	/**
	* Starts the projectiles movement in a given direction.
	* @param Direction: direction followed by the projectile.
	*/
	void StartProjectile(const FVector& Direction);

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	class UParticleSystemComponent* IceShotParticleComponent; //!< Particle system component.

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	UParticleSystemComponent* IceExplosionParticleComponent; //!< Explosion once the shot hits something.

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	class USphereComponent* CollisionComponent; //!< Collision component, using a sphere.

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	class UProjectileMovementComponent* ProjectileMovementComponent; //!< Projectile movement component.

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float AttackPotency; //!< Potency of the attack.

protected:

	/**
	* Called when the game starts or when spawned
	*/
	virtual void BeginPlay() override;

private:

	/**
	* Function called every time the projectiles hits an actor.
	* @param HitComponent: Primitive component.
	* @param OtherActor: Actor the primitive has hitted with.
	* @param OtherComp: Other actor's primitive component.
	* @param NormalImpulse: Impulse.
	* @param Hit: Hit results.
	*/
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/**
	* Function called when a particle system is finished.
	* @param PSystem: Particle that has finished.
	*/
	UFUNCTION()
	void OnParticleSystemFinished(UParticleSystemComponent* PSystem);

	TArray<AActor*> DamageActors; //!< Container with the damaged actors.
};
