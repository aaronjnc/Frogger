// Fill out your copyright notice in the Description page of Project Settings.


#include "FrogCharacter.h"

// Sets default values
AFrogCharacter::AFrogCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void AFrogCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFrogCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFrogCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

