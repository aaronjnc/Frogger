// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingObstacle.h"
#include "TurtleObstacle.generated.h"

/**
 * 
 */
UCLASS()
class FROGGER_API ATurtleObstacle : public AMovingObstacle
{
	GENERATED_BODY()

private:	

	bool bDives;

	bool bDiving;

	bool bRising;

	UPROPERTY(EditAnywhere, Category = "Diving")
	float DiveTime;

	float ZMoveDir;

	float BaseZ;

	FTimerHandle DiveHandle;

public:

	virtual void Tick(float DeltaSeconds) override;

protected:

	virtual void BeginPlay() override;

	void Dive();

	void Rise();
	
};
