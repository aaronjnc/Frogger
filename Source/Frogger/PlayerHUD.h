// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UImage;
class UHorizontalBox;
class AFrogCharacter;

/**
 * 
 */
UCLASS()
class FROGGER_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HealthParent;

	TArray<UImage*> ActiveHealthImages;

	TArray<UImage*> InactiveHealthImages;

	UPROPERTY(EditAnywhere, Category = "Images")
	UTexture2D* HealthTexture;

	UPROPERTY(EditAnywhere, Category = "Images")
	UTexture2D* EmptyHealthTexture;

public:

	void SetupLives(const int& Lives, AFrogCharacter* FrogCharacter);

	void UpdateLives(const int& Lives);
	
};
