// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "River.generated.h"

UCLASS()
class FROGGER_API ARiver : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* RiverMesh;	
	
public:	
	// Sets default values for this actor's properties
	ARiver();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:

	virtual void BeginPlay() override;

};
