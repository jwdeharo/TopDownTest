#include "GunWeapon.h"
#include "BaseProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

AGunWeapon::AGunWeapon()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> GunMesh(TEXT("/Game/Demo/FPWeapon/Mesh/SK_FPGun"));
	SkeletalMeshComponent->SetSkeletalMesh(GunMesh.Object);
}

void AGunWeapon::BeginPlay()
{
	Super::BeginPlay();
	CanAttack = true;
}

void AGunWeapon::Attack()
{
	if (CanAttack)
	{
		auto const BaseProj = GetWorld()->SpawnActor<ABaseProjectile>(ABaseProjectile::StaticClass(), SkeletalMeshComponent->GetSocketTransform("Muzzle"));
		BaseProj->StartProjectile(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorForwardVector());
		GetWorld()->GetTimerManager().SetTimer(AttackTimerController, this, &AGunWeapon::OnAttackTimerEnded, 0.3f, true);
		StopAttack();
	}
}


void AGunWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGunWeapon::StopAttack()
{
	CanAttack = false;
}

void AGunWeapon::OnAttackTimerEnded()
{
	CanAttack = true;
}
