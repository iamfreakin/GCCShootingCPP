// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone.h"

#include "Components/BoxComponent.h"


AKillZone::AKillZone()
{
	// Tick이 필요 없는 액터에는 항상 false로 설정
	PrimaryActorTick.bCanEverTick = false;

	// 박스 콜라이더 컴포넌트의 자식 컴포넌트로 설정
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Kill Zone Box"));
	SetRootComponent(boxComp);

	// 박스 모빌리티를 고정(Static)으로 설정
	boxComp->SetMobility(EComponentMobility::Static);

	// 박스 콜라이더 크기를 50x2000x50으로 설정
	FVector boxSize = FVector(50.0f, 2000.f, 50.f);
	boxComp->SetBoxExtent(boxSize);

	// 에디터에서 만든 충돌 프리셋 적용
	boxComp->SetCollisionProfileName(TEXT("KillZone"));
}

void AKillZone::BeginPlay()
{
	Super::BeginPlay();

	// 델리게이트로 충돌 오버랩 시 동작할 함수를 지정
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AKillZone::OnKillZoneOverlap);
}

void AKillZone::OnKillZoneOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 충돌 오버랩 발생한 액터 제거
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}
