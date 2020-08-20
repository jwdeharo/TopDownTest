#include "EnemySpawnerController.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Spider/SpiderController.h"

constexpr float EXTRA_ORIGIN = 1000.f;
constexpr float EXTRA_END = 15000.f;

AEnemySpawnerController::AEnemySpawnerController()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision Component"));
	BoxCollisionComponent->SetCollisionProfileName("NoCollision");
	BoxCollisionComponent->SetBoxExtent(FVector(200.f, 600.f, 200.f));
	RootComponent = BoxCollisionComponent;
}

void AEnemySpawnerController::BeginPlay()
{
	Super::BeginPlay();
	StartTimer();
}

void AEnemySpawnerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawnerController::StartTimer()
{
	float TimeToSpawn = FMath::RandRange(MinSpawnTime, MaxSpawnTime);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawnerController::OnSpawnTimerFinished, TimeToSpawn, true);
}

void AEnemySpawnerController::OnSpawnTimerFinished()
{
	if (CurrentEnemiesNumber < MaxSpawnableEnemies)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		GetWorld()->SpawnActor<ASpiderController>(EnemyToSpawn, CalculateSpawnedEnemyTransform(), SpawnParameters);
		StartTimer();
		++CurrentEnemiesNumber;
	}
}

FTransform AEnemySpawnerController::CalculateSpawnedEnemyTransform() const
{
	FVector Origin, BoxExtent;
	float SphereRadius;

	UKismetSystemLibrary::GetComponentBounds(BoxCollisionComponent, Origin, BoxExtent, SphereRadius);

	FVector SpawnPosition = UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);
	FRotator Rotation = FRotator(0.f, FMath::Rand(), 0.f);

	SpawnPosition = GetFloorPoint(SpawnPosition);

	return UKismetMathLibrary::MakeTransform(SpawnPosition, Rotation, FVector(1.f));
}

FVector AEnemySpawnerController::GetFloorPoint(const FVector& InitPosition) const
{
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjects;
	FVector Origin = InitPosition;
	FVector EndLineTrace = GetActorUpVector() * -1.f;
	FHitResult HitResult;

	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

	Origin.Z += EXTRA_ORIGIN;
	EndLineTrace *= EXTRA_END;
	EndLineTrace += Origin;

	if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Origin, EndLineTrace, TraceObjects, false, TArray<AActor*>(), EDrawDebugTrace::None, HitResult, true))
	{
		Origin = HitResult.ImpactPoint;
	}

	return Origin;
}