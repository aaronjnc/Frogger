// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FrogController.generated.h"

class UInputMappingContext;
class UInputAction;
class AFrogCharacter;

/**
 * 
 */
UCLASS()
class FROGGER_API AFrogController : public APlayerController
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	TWeakObjectPtr<AFrogCharacter> PlayerCharacter;

protected:

	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
	
};
