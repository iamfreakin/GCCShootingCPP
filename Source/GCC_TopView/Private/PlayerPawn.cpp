// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "IEditableSkeleton.h"
#include "Components/BoxComponent.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 박스 콜리전 컴포넌트 생성
	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	// 생성한 박스 콜리전 컴포넌트를 최상단 컴포넌트로 설정
	SetRootComponent(boxComponent);
	// 스태틱메시 컴포넌트 생성
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh Component"));
	// 스태틱메시를 박스콜리전의 자식으로 설정
	meshComponent->SetupAttachment(boxComponent);
	
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

