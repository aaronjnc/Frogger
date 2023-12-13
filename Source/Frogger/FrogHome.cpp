// Fill out your copyright notice in the Description page of Project Settings.


#include "FrogHome.h"
#include "FrogCharacter.h"

// Sets default values
AFrogHome::AFrogHome()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HomeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Home Mesh"));
	RootComponent = HomeMesh;

	FrogMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Frog Mesh"));
	FrogMesh->SetupAttachment(RootComponent);
	FrogMesh->SetHiddenInGame(true);
}

void AFrogHome::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA<AFrogCharacter>())
	{
		Cast<AFrogCharacter>(OtherActor)->GetHome();
		FrogMesh->SetHiddenInGame(false);
	}
}

// Called when the game starts or when spawned
void AFrogHome::BeginPlay()
{
	Super::BeginPlay();
	HomeMesh->OnComponentHit.AddDynamic(this, &AFrogHome::OnHit);
}