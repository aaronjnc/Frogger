// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

class UBoxComponent;
class AMovingObstacle;

UCLASS()
class FROGGER_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* DespawnCollider;

	UPROPERTY(EditAnywhere, Category = "Spawn Params")
	TSubclassOf<AMovingObstacle> ObstacleClass;

	UPROPERTY(EditAnywhere, Category = "Spawn Params")
	float SpawnTime;

	TArray<TObjectPtr<AMovingObstacle>> SpawnedObstacles;

	TArray<TObjectPtr<AMovingObstacle>> DespawnedObstacles;

	FTimerHandle SpawnTimerHandle;

	FVector MoveDir;
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnObstacle();

	UFUNCTION()
	void OnDespawnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
