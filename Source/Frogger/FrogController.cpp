// Fill out your copyright notice in the Description page of Project Settings.


#include "FrogController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FrogCharacter.h"

void AFrogController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	PlayerCharacter = Cast<AFrogCharacter>(GetPawn());
	SetupInputComponent();
}

void AFrogController::SetupInputComponent()
{
	if (!PlayerCharacter.IsValid())
	{
		return;
	}

	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, PlayerCharacter.Get(), &AFrogCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, PlayerCharacter.Get(), &AFrogCharacter::BeginHop);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Canceled, PlayerCharacter.Get(), &AFrogCharacter::Hop);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, PlayerCharacter.Get(), &AFrogCharacter::Hop);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, PlayerCharacter.Get(), &AFrogCharacter::Move);
	}
}
