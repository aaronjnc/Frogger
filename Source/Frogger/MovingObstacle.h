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

protected:
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ObstacleMesh;

	FVector MoveDir;

	UPROPERTY(EditAnywhere, Category = "Movement")
	bool bIsDeadly;

public:
	// Sets default values for this pawn's properties
	AMovingObstacle();

	void SetMoveDirection(FVector Direction);

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:

	virtual void BeginPlay() override;
	
};
