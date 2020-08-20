#include "BaseProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABaseProjectile::ABaseProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComponent->InitSphereRadius(10.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	RootComponent = CollisionComponent;

	ConstructorHelpers::FObjectFinder<UParticleSystem> IceProjectile(TEXT("/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Elemental/ICE/P_Elemental_Ice_Proj"));
	IceShotParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Ice Shot Particle System"));
	IceShotParticleComponent->Template = IceProjectile.Object;
	IceShotParticleComponent->bAutoActivate = true;
	IceShotParticleComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	IceShotParticleComponent->SetRelativeLocation(FVector::ZeroVector);

	ConstructorHelpers::FObjectFinder<UParticleSystem> IceExplosion(TEXT("/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Elemental/ICE/P_Elemental_Proj_Impact_Ice"));
	IceExplosionParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Ice Explosion Particle System"));
	IceExplosionParticleComponent->Template = IceExplosion.Object;
	IceExplosionParticleComponent->bAutoActivate = false;
	IceExplosionParticleComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	IceExplosionParticleComponent->SetRelativeLocation(FVector::ZeroVector);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bAutoActivate = true;
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 1000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 3.f;
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
}

void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseProjectile::StartProjectile(const FVector& Direction)
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	IceExplosionParticleComponent->OnSystemFinished.AddDynamic(this, &ABaseProjectile::OnParticleSystemFinished);
	IceShotParticleComponent->SetVisibility(false, true);
	IceShotParticleComponent->Deactivate();
	ProjectileMovementComponent->Deactivate();
	IceExplosionParticleComponent->Activate();
}

void ABaseProjectile::OnParticleSystemFinished(UParticleSystemComponent* PSystem)
{
	if (PSystem == IceExplosionParticleComponent)
	{
		Destroy();
	}
}