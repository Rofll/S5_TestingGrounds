// Fill out your copyright notice in the Description page of Project Settings.


#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimInstance.h"
#include "../Weapons/Gun.h"
#include "Components/InputComponent.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	firstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	firstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	firstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f);
	firstPersonCameraComponent->bUsePawnControlRotation = true;

	mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	mesh1P->SetOnlyOwnerSee(true);
	mesh1P->SetupAttachment(firstPersonCameraComponent);
	mesh1P->bCastDynamicShadow = false;
	mesh1P->CastShadow = false;
	mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
	mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);

}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();

	if (gunBlueprint == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gun blueprint missing"));
		return;
	}

	gun = GetWorld()->SpawnActor<AGun>(gunBlueprint);
	gun->AttachToComponent(mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	gun->AnimInstance = GetMesh()->GetAnimInstance();

	if (InputComponent != NULL)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	}
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMannequin::PullTrigger()
{
	gun->OnFire();
}

