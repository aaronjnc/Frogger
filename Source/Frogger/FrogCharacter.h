// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FrogCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;
class UCapsuleComponent;

UCLASS()
class FROGGER_API AFrogCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;

	TObjectPtr<UCapsuleComponent> CapsuleCollider;

	UPrimitiveComponent* ActorBody;

	float StartHopTick;
	bool bIsJumping = false;
	float CharacterMass;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxHopForce;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxHopTime;

public:
	// Sets default values for this character's properties
	AFrogCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BeginHop();

	UFUNCTION()
	void Hop();

	UFUNCTION()
	void Look(const FInputActionValue& Value);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
