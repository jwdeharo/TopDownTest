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
				FVector Origin = GetMesh()->GetSocketLocation("LeftAttackPoint1");
				FVector End = GetMesh()->GetSocketLocation("LeftAttackPoint2");
				DamagedActor = MeleeAttack(Origin, End);
			}
			break;
			case EPartAttack::RightArm:
			{
				FVector Origin = GetMesh()->GetSocketLocation("RightAttackPoint1");
				FVector End = GetMesh()->GetSocketLocation("RightAttackPoint2");
				DamagedActor = MeleeAttack(Origin, End);
			}
			break;
			case EPartAttack::BothArms:
			{
				FVector Origin = GetMesh()->GetSocketLocation("RightAttackPoint1");
				FVector End = GetMesh()->GetSocketLocation("RightAttackPoint2");
				DamagedActor = MeleeAttack(Origin, End);

				if (DamagedActor == nullptr)
				{
					Origin = GetMesh()->GetSocketLocation("LeftAttackPoint1");
					End = GetMesh()->GetSocketLocation("LeftAttackPoint2");
					DamagedActor = MeleeAttack(Origin, End);
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
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Origin, End, 5.f, TraceObject, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, Result, true);

	return Result.Actor.Get();
}