// Fill out your copyright notice in the Description page of Project Settings.


#include "FrogCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AFrogCharacter::AFrogCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent);

}


// Called when the game starts or when spawned
void AFrogCharacter::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollider = Cast<UCapsuleComponent>(GetCapsuleComponent());
	ActorBody = Cast<UPrimitiveComponent>(GetRootComponent());
	MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
}

bool AFrogCharacter::IsGrounded() const
{
	FHitResult HitResult;
	const FVector StartLoc = CapsuleCollider->GetComponentLocation();
	const FVector EndLoc = StartLoc - GetActorUpVector() * CapsuleCollider->GetUnscaledCapsuleHalfHeight() - .1;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	return GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility, QueryParams);;
}

// Called every frame
void AFrogCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	if (bIsJumping)
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
		CameraForwardVector.Z = 0;
		CameraForwardVector *= MoveDir.Y;
		FVector CameraRightVector = UKismetMathLibrary::GetRightVector(GetControlRotation());
		CameraRightVector.Z = 0;
		CameraRightVector *= MoveDir.X;
		FVector FinalMoveDir = CameraForwardVector + CameraRightVector;
		FinalMoveDir.Z = FMath::Cos(MoveAngle);
		FinalMoveDir.Normalize();
		ActorBody->AddForceAtLocation(FinalMoveDir * MoveForce, CapsuleCollider->GetComponentLocation());
	}
}

void AFrogCharacter::Kill()
{
	
}
