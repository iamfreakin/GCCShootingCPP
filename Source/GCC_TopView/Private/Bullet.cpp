// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "EnemyActor.h"
#include "ShootingGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 박스 콜리전 컴포넌트 생성
	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	// 생성한 박스 콜리전 컴포넌트를 최상단 컴포넌트로 설정
	SetRootComponent(boxComponent);
	FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
	boxComponent->SetBoxExtent(boxSize);
	// 스케일 조절 - 총알 형태에 가깝도록 SetWorldScale3D 조절
	boxComponent->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f));
	
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh Component"));
	meshComponent->SetupAttachment(boxComponent);
	
	//아래와 같이 에디터에서 생성할 프리셋 이름을 세팅
	boxComponent->SetCollisionProfileName(TEXT("Bullet"));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	// OnComponentBeginOverlap 델리게이트에 OnBulletOverlap 함수를 등록
	// "Overlap" 발생하면 OnBulletOverlap() 호출해 라고 엔진에 등록 설정
	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// 총알 이동
	FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime;
	SetActorLocation(newLocation);
}

void ABullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// 충돌한 상대 액터를 AEnemyActor 클래스로 변환
	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	if (enemy != nullptr)
	{
		// 충돌 위치에 폭발 파티클 이펙트를 스폰
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorTransform());
		// Enemy 제거
		OtherActor->Destroy();
		
		AGameModeBase* currentGameMode = GetWorld()->GetAuthGameMode();
		AShootingGameModeBase* currentGameModeBase = Cast<AShootingGameModeBase>(currentGameMode);

		if (currentGameModeBase != nullptr)
		{
			// 점수 1점 추가 함수 호출
			currentGameModeBase->AddScore(1);
		}
	}
	// 총알 자신도 제거
	Destroy();
}