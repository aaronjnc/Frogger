// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FrogCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;
class UCapsuleComponent;
class UPlayerHUD;

DECLARE_MULTICAST_DELEGATE_OneParam(FChangeHealth, const int&);

UCLASS()
class FROGGER_API AFrogCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	FChangeHealth ChangeHealthDelegate;

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> PlayerHUDClass;
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> GameOverHUDClass;
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> EndGameHUDClass;

	TObjectPtr<UUserWidget> GameOverHUD;

	TObjectPtr<UUserWidget> EndGameHUD;

	TObjectPtr<UCapsuleComponent> CapsuleCollider;

	UPrimitiveComponent* ActorBody;

	TWeakObjectPtr<UCharacterMovementComponent> MovementComponent;

	float StartHopTick;
	bool bIsJumping = false;
	float CharacterMass;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxHopForce;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxHopTime;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveForce;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveAngle;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float StrafeForce;

	FVector SpawnPoint;
	FRotator SpawnRotation;

	UPROPERTY(EditAnywhere, Category = "Health")
	int Lives;

	int HomesRemaining;

public:
	// Sets default values for this character's properties
	AFrogCharacter();

	UFUNCTION()
	void BeginHop();

	UFUNCTION()
	void Hop();

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	void Kill();

	void GetHome();

	void Respawn();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsGrounded() const;

};
