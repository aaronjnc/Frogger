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
	UE_LOG(LogTemp, Warning, TEXT("Max Hop Time: %f"), MaxHopTime);
	UE_LOG(LogTemp, Warning, TEXT("Max Hop Force: %f"), MaxHopForce);
	const float HopForce = FMath::Max((EndHopTick - StartHopTick) / MaxHopTime, 1.0f) * MaxHopForce;
	UE_LOG(LogTemp, Warning, TEXT("Hop Force: %f"), HopForce);
	const FVector HalfVector = (GetActorUpVector() + UKismetMathLibrary::GetForwardVector(GetControlRotation())) / 2;
	UE_LOG(LogTemp, Warning, TEXT("Half Vector: %s"), *HalfVector.ToString());
	const FVector HopForceVector = HalfVector.GetUnsafeNormal() * HopForce;
	//CapsuleCollider->AddForce(HopForceVector);
	//GetMesh()->AddForce(HopForceVector);
	ActorBody->AddForceAtLocation(HopForceVector, CapsuleCollider->GetComponentLocation());
	UE_LOG(LogTemp, Warning, TEXT("Hop Force: %s"), *HopForceVector.ToString());
	//UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	//MovementComponent->IsMovingO
}

void AFrogCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}