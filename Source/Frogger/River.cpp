// Fill out your copyright notice in the Description page of Project Settings.


#include "River.h"
#include "FrogCharacter.h"

// Sets default values
ARiver::ARiver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RiverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("River Mesh"));
	RootComponent = RiverMesh;
}

void ARiver::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA<AFrogCharacter>())
	{
		Cast<AFrogCharacter>(OtherActor)->Kill();
	}
}

// Called when the game starts or when spawned
void ARiver::BeginPlay()
{
	Super::BeginPlay();

	RiverMesh->OnComponentHit.AddDynamic(this, &ARiver::OnHit);
}

