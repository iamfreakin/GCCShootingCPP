// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include "EngineUtils.h"
#include "PlayerPawn.h"
#include "Components/BoxComponent.h"


// Sets default values
AEnemyActor::AEnemyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 박스 콜리전 컴포넌트 생성
	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	// 생성한 박스 콜리전 컴포넌트를 최상단 컴포넌트로 설정
	SetRootComponent(boxComponent);
	// 스태틱메시 컴포넌트 생성
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh Component"));
	// 스태틱메시를 박스콜리전의 자식으로 설정
	meshComponent->SetupAttachment(boxComponent);
	
	FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
	boxComponent->SetBoxExtent(boxSize);
	
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	int32 drawResult = FMath::RandRange(1, 100);

	if (drawResult <= traceRate)
	{
		for (TActorIterator<APlayerPawn> player(GetWorld()); player; ++player)
		{
			if (player->GetName().Contains(TEXT("BP_PlayerPawn")))
			{
				dir = player->GetActorLocation() - GetActorLocation();
				dir.Normalize();
			}
		}
	}
	else
	{
		dir = GetActorForwardVector();
	}
}


// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

