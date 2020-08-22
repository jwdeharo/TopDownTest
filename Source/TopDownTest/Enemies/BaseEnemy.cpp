#include "BaseEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/CapsuleComponent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void ABaseEnemy::NotifyAttack(EPartAttack::Type PartAttack)
{
	IsAttacking = true;
	CurrentAttackPart = PartAttack;
}

AActor* const ABaseEnemy::MeleeAttack(const FVector& Origin, const FVector& End) const
{
	return nullptr;
}

void ABaseEnemy::DamageActor(AActor* const DamagedActor)
{
	AlreadyDamagedActors.AddUnique(DamagedActor);
}

void ABaseEnemy::CleanDamageActors()
{
	AlreadyDamagedActors.Empty();
}

void ABaseEnemy::StopAttack()
{
	IsAttacking = false;
}

float ABaseEnemy::GetCurrentHealth() const
{
	return CurrentHealth;
}

float ABaseEnemy::GetMaxHealth() const
{
	return MaxHealth;
}

void ABaseEnemy::ReceiveDamage(float Potency)
{
	if (CurrentHealth - Potency > 0.f)
	{
		CurrentHealth -= Potency;
	}
	else
	{
		CurrentHealth = 0.f;
		SetActorEnableCollision(false);
		OnDeath.Broadcast();
	}
}

bool ABaseEnemy::IsActorDamaged(AActor* const Actor) const
{
	return AlreadyDamagedActors.Contains(Actor);
}