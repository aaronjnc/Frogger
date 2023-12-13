// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FrogHome.generated.h"

UCLASS()
class FROGGER_API AFrogHome : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* HomeMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* FrogMesh;
	
public:	
	// Sets default values for this actor's properties
	AFrogHome();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
