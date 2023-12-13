// Fill out your copyright notice in the Description page of Project Settings.


#include "TurtleObstacle.h"

void ATurtleObstacle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bDives && ZMoveDir != 0)
	{
		SetActorLocation(GetActorLocation() + GetActorUpVector() * Speed * DeltaSeconds * ZMoveDir);
		if (GetActorLocation().Z >= BaseZ)
		{
			FVector Loc = GetActorLocation();
			Loc.Z = BaseZ;
			SetActorLocation(Loc);
			ZMoveDir = 0;
			GetWorld()->GetTimerManager().SetTimer(DiveHandle, this, &ATurtleObstacle::Dive, DiveTime, false);
		}
	}
}

void ATurtleObstacle::BeginPlay()
{
	Super::BeginPlay();
	bDives = FMath::RandRange(0, 5) >= 4 ? true : false;
	GetWorld()->GetTimerManager().SetTimer(DiveHandle, this, &ATurtleObstacle::Dive, DiveTime, false);
}

void ATurtleObstacle::Dive()
{
	ZMoveDir = -1;
	GetWorld()->GetTimerManager().SetTimer(DiveHandle, this, &ATurtleObstacle::Rise, DiveTime, false);
}

void ATurtleObstacle::Rise()
{
	ZMoveDir = 1;
}
