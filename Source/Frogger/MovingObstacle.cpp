// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingObstacle.h"

#include "FrogCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMovingObstacle::AMovingObstacle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obstacle Mesh"));
	RootComponent = ObstacleMesh;
}

void AMovingObstacle::SetMoveDirection(FVector Direction)
{
	MoveDir = Direction;
}

void AMovingObstacle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetActorLocation(GetActorLocation() + MoveDir * Speed * DeltaSeconds);
}

void AMovingObstacle::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA<AFrogCharacter>())
	{
		Cast<AFrogCharacter>(OtherActor)->Kill();
	}
}

void AMovingObstacle::BeginPlay()
{
	Super::BeginPlay();
	ObstacleMesh->OnComponentHit.AddDynamic(this, &AMovingObstacle::OnHit);
}
