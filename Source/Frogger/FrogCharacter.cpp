// Fill out your copyright notice in the Description page of Project Settings.


#include "FrogCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InputActionValue.h"
#include "PlayerHUD.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "FrogHome.h"

// Sets default values
AFrogCharacter::AFrogCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	Lives = 4;
}


// Called when the game starts or when spawned
void AFrogCharacter::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollider = Cast<UCapsuleComponent>(GetCapsuleComponent());
	ActorBody = Cast<UPrimitiveComponent>(GetRootComponent());
	MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	SpawnPoint = GetActorLocation();
	SpawnRotation = GetActorRotation();

	APlayerController* PlayerController = GetController<APlayerController>();

	UPlayerHUD* PlayerHUD = CreateWidget<UPlayerHUD>(PlayerController, PlayerHUDClass);
	PlayerHUD->AddToViewport();
	PlayerHUD->SetupLives(Lives, this);

	GameOverHUD = CreateWidget<UUserWidget>(PlayerController, GameOverHUDClass);
	GameOverHUD->AddToViewport();
	GameOverHUD->SetVisibility(ESlateVisibility::Hidden);

	EndGameHUD = CreateWidget<UUserWidget>(PlayerController, EndGameHUDClass);
	EndGameHUD->AddToViewport();
	EndGameHUD->SetVisibility(ESlateVisibility::Hidden);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFrogHome::StaticClass(), FoundActors);
	HomesRemaining = FoundActors.Num();
}

bool AFrogCharacter::IsGrounded() const
{
	FHitResult HitResult;
	const FVector StartLoc = CapsuleCollider->GetComponentLocation();
	const FVector EndLoc = StartLoc - GetActorUpVector() * CapsuleCollider->GetUnscaledCapsuleHalfHeight() - .1;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	return GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Pawn, QueryParams);;
}

void AFrogCharacter::BeginHop()
{
	if (IsGrounded())
	{
		StartHopTick = UGameplayStatics::GetRealTimeSeconds(GetWorld());
		bIsJumping = true;
	}
}

void AFrogCharacter::Hop()
{
	if (bIsJumping && IsGrounded())
	{
		const float EndHopTick = UGameplayStatics::GetRealTimeSeconds(GetWorld());
		const float HopForce = FMath::Max((EndHopTick - StartHopTick) / MaxHopTime, 1.0f) * MaxHopForce;
		FVector CameraForwardVector = UKismetMathLibrary::GetForwardVector(GetControlRotation());
		CameraForwardVector.Z = FMath::Max(0, CameraForwardVector.Z);
		const FVector HalfVector = (GetActorUpVector() + CameraForwardVector) / 2;
		const FVector HopForceVector = HalfVector.GetUnsafeNormal() * HopForce;
		ActorBody->AddForceAtLocation(HopForceVector, CapsuleCollider->GetComponentLocation());
		bIsJumping = false;
	}
}

void AFrogCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(-LookVector.Y);
}

void AFrogCharacter::Move(const FInputActionValue& Value)
{
	if (IsGrounded())
	{
		const FVector2D MoveDir = Value.Get<FVector2D>();
		FVector CameraForwardVector = UKismetMathLibrary::GetForwardVector(GetControlRotation());
		CameraForwardVector.Z = FMath::Cos(MoveAngle);
		CameraForwardVector *= MoveDir.Y;
		CameraForwardVector.Normalize();
		ActorBody->AddForceAtLocation(CameraForwardVector * MoveForce, CapsuleCollider->GetComponentLocation());
		FVector SideMoveVector = UKismetMathLibrary::GetRightVector(GetControlRotation());
		SideMoveVector.Z = 0;
		SideMoveVector.Normalize();
		SideMoveVector *= MoveDir.X;
		ActorBody->AddForceAtLocation(SideMoveVector * StrafeForce, CapsuleCollider->GetComponentLocation());
	}
}

void AFrogCharacter::Kill()
{
	Lives--;
	ChangeHealthDelegate.Broadcast(Lives);
	if (Lives != 0)
	{
		Respawn();
	}
	else
	{
		APlayerController* PlayerController = GetController<APlayerController>();
		PlayerController->SetPause(true);
		PlayerController->SetShowMouseCursor(true);
		GameOverHUD->SetVisibility(ESlateVisibility::Visible);
	}
}

void AFrogCharacter::GetHome()
{
	HomesRemaining--;
	if (HomesRemaining == 0)
	{
		APlayerController* PlayerController = GetController<APlayerController>();
		PlayerController->SetPause(true);
		PlayerController->SetShowMouseCursor(true);
		EndGameHUD->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Respawn();
	}
}

void AFrogCharacter::Respawn()
{
	SetActorLocation(SpawnPoint);
	SetActorRotation(SpawnRotation);
	ActorBody->SetPhysicsLinearVelocity(FVector::Zero());
}
