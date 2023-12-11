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
}

// Called every frame
void AFrogCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFrogCharacter::BeginHop()
{
	StartHopTick = UGameplayStatics::GetRealTimeSeconds(GetWorld());
}

void AFrogCharacter::Hop()
{
	const float EndHopTick = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	const float HopForce = FMath::Max((EndHopTick - StartHopTick) / MaxHopTime, 1.0f) * MaxHopForce;
	FVector CameraForwardVector = UKismetMathLibrary::GetForwardVector(GetControlRotation());
	CameraForwardVector.Z = FMath::Max(0, CameraForwardVector.Z);
	const FVector HalfVector = (GetActorUpVector() + CameraForwardVector) / 2;
	const FVector HopForceVector = HalfVector.GetUnsafeNormal() * HopForce;
	ActorBody->AddForceAtLocation(HopForceVector, CapsuleCollider->GetComponentLocation());
}

void AFrogCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(-LookVector.Y);
}