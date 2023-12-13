// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Spacer.h"
#include "FrogCharacter.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBox.h"
#include "Components/SizeBoxSlot.h"


void UPlayerHUD::SetupLives(const int& Lives, AFrogCharacter* FrogCharacter)
{
	for (int i = 0; i < Lives; i++)
	{
		const FName SizeBoxName = FName(FString::Printf(TEXT("Size Box %d"), i));
		USizeBox* SizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass(), SizeBoxName);
		HealthParent->AddChildToHorizontalBox(SizeBox);
		SizeBox->SetWidthOverride(96);
		const FName LifeName = FName(FString::Printf(TEXT("Life %d"), i));
		ActiveHealthImages.Add(WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), LifeName));
		ActiveHealthImages[i]->SetBrushFromTexture(HealthTexture);
		SizeBox->AddChild(ActiveHealthImages[i]);
	}
	FrogCharacter->ChangeHealthDelegate.AddUObject(this, &UPlayerHUD::UpdateLives);
}

void UPlayerHUD::UpdateLives(const int& Lives)
{
	if (Lives < ActiveHealthImages.Num())
	{
		for (int i = ActiveHealthImages.Num() - 1; i >= Lives && i >= 0; i--)
		{
			ActiveHealthImages[i]->SetBrushFromTexture(EmptyHealthTexture);
			InactiveHealthImages.Add(ActiveHealthImages[i]);
			ActiveHealthImages.RemoveAt(i);
		}
	}
	else if (Lives > ActiveHealthImages.Num())
	{
		FSlateChildSize ChildSize;
		ChildSize.SizeRule = ESlateSizeRule::Fill;
		for (int i = ActiveHealthImages.Num(); i < Lives; i++)
		{
			if (InactiveHealthImages.Num() > 0)
			{
				InactiveHealthImages[0]->SetBrushFromTexture(HealthTexture);
				ActiveHealthImages.Add(InactiveHealthImages[0]);
				InactiveHealthImages.RemoveAt(0);
			}
			else
			{
				const FName SizeBoxName = FName(FString::Printf(TEXT("Size Box %d"), i));
				USizeBox* SizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass(), SizeBoxName);
				HealthParent->AddChildToHorizontalBox(SizeBox);
				SizeBox->SetWidthOverride(96);
				const FName LifeName = FName(FString::Printf(TEXT("Life %d"), i));
				ActiveHealthImages.Add(WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), LifeName));
				ActiveHealthImages[i]->SetBrushFromTexture(HealthTexture);
				SizeBox->AddChild(ActiveHealthImages[i]);
			}
		}
	}
}
