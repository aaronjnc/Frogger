// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingObstacle.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMovingObstacle::AMovingObstacle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obstacle Mesh"));
	RootComponent = ObstacleMesh;

	ProjectilePawnMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Pawn Movement"));
}

void AMovingObstacle::SetMoveDirection(FVector Direction)
{
	ProjectilePawnMovement->Velocity = Direction;
	ProjectilePawnMovement->InitialSpeed = Speed;
}

void AMovingObstacle::BeginPlay()
{
	Super::BeginPlay();

	ActorBody = Cast<UPrimitiveComponent>(GetRootComponent());
}
