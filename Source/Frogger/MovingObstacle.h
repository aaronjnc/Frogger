// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovingObstacle.generated.h"

class UProjectileMovementComponent;

UCLASS()
class FROGGER_API AMovingObstacle : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ObstacleMesh;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;

	UPrimitiveComponent* ActorBody;

	UPROPERTY(EditAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectilePawnMovement;

public:
	// Sets default values for this pawn's properties
	AMovingObstacle();

	void SetMoveDirection(FVector Direction);
	
protected:

	virtual void BeginPlay() override;
	
};
