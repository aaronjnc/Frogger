// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"
#include "Components/BoxComponent.h"
#include "MovingObstacle.h"

// Sets default values
AObstacleSpawner::AObstacleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(RootComponent);

	DespawnCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Despawn Collider"));
	DespawnCollider->SetupAttachment(RootComponent);
	DespawnCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	DespawnCollider->SetGenerateOverlapEvents(true);
}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AObstacleSpawner::SpawnObstacle, SpawnTime, true);

	MoveDir = DespawnCollider->GetComponentLocation() - SpawnPoint->GetComponentLocation();
	MoveDir.Normalize();
	UE_LOG(LogTemp, Warning, TEXT("Move Dir: %s"), *MoveDir.ToString());

	SpawnObstacle();
	DespawnCollider->OnComponentBeginOverlap.AddDynamic(this, &AObstacleSpawner::OnDespawnOverlap);
}

void AObstacleSpawner::SpawnObstacle()
{
	AMovingObstacle* SpawnActor;
	if (DespawnedObstacles.Num() > 0)
	{
		SpawnActor = DespawnedObstacles[0];
		DespawnedObstacles.RemoveAt(0);
	}
	else
	{
		const FActorSpawnParameters SpawnParameters;
		const FRotator SpawnRotation = MoveDir.Rotation();
		SpawnActor = GetWorld()->SpawnActor<AMovingObstacle>(ObstacleClass, SpawnPoint->GetComponentLocation(), SpawnRotation, SpawnParameters);
	}
	SpawnActor->SetActorLocation(SpawnPoint->GetComponentLocation());
	SpawnActor->SetActorHiddenInGame(false);
	SpawnActor->SetMoveDirection(MoveDir);
}

void AObstacleSpawner::OnDespawnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AMovingObstacle>())
	{
		OtherActor->SetActorHiddenInGame(true);
		DespawnedObstacles.Add(Cast<AMovingObstacle>(OtherActor));
	}
}
