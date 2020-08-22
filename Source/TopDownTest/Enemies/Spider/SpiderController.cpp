#include "SpiderController.h"
#include "SpiderAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../../TopDownTestCharacter.h"

ASpiderController::ASpiderController()
{
	GetCharacterMovement()->MaxWalkSpeed = 260.f;
}

void ASpiderController::Tick(float DeltaTime)
{
	if (IsAttacking)
	{
		AActor* DamagedActor = nullptr;
		switch (CurrentAttackPart)
		{
			case EPartAttack::LeftArm:
			{
				DamagedActor = GetDamagedActor("LeftAttackPoint1", "LeftAttackPoint2");
			}
			break;
			case EPartAttack::RightArm:
			{
				DamagedActor = GetDamagedActor("RightAttackPoint1", "RightAttackPoint2");
			}
			break;
			case EPartAttack::BothArms:
			{
				DamagedActor = GetDamagedActor("RightAttackPoint1", "RightAttackPoint2");

				if (DamagedActor == nullptr)
				{
					DamagedActor = GetDamagedActor("LeftAttackPoint1", "LeftAttackPoint2");
				}
			}
			break;
		}

		if (DamagedActor != nullptr && !IsActorDamaged(DamagedActor))
		{
			ATopDownTestCharacter* CharacterController = Cast<ATopDownTestCharacter>(DamagedActor);
			if (CharacterController != nullptr)
			{
				CharacterController->ReceiveDamage(AttackPotency);
				DamageActor(DamagedActor);
			}
		}
	}
}

AActor* const ASpiderController::MeleeAttack(const FVector& Origin, const FVector& End) const
{
	FHitResult Result;
	TArray<AActor*> ActorsToIgnore;
	ETraceTypeQuery TraceObject = UEngineTypes::ConvertToTraceType(ECC_Pawn);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseEnemy::StaticClass(), ActorsToIgnore);
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Origin, End, 5.f, TraceObject, false, ActorsToIgnore, EDrawDebugTrace::None, Result, true);

	return Result.Actor.Get();
}

AActor* const ASpiderController::GetDamagedActor(const FString& Socket1, const FString& Socket2) const
{
	AActor* const DamagedActor = nullptr;
	FVector Origin = GetMesh()->GetSocketLocation(*Socket1);
	FVector End = GetMesh()->GetSocketLocation(*Socket2);

	return MeleeAttack(Origin, End);
}