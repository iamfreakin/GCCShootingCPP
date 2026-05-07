// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "Bullet.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "IEditableSkeleton.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


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
	
	FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
	boxComponent->SetBoxExtent(boxSize);
	
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire Position"));
	firePosition->SetupAttachment(boxComponent);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (pc != nullptr)
	{
		// 플레이어 컨트롤러부터 입력서브시스템 정보 가져오기
		UEnhancedInputLocalPlayerSubsystem* subsys =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subsys != nullptr)
		{
			subsys->AddMappingContext(imcPlayerInput, 0);
		}
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector dir = FVector(0, h, v);
	dir.Normalize();
	FVector newLocation = GetActorLocation() + dir * moveSpeed * DeltaTime;
	SetActorLocation(newLocation);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* eic = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (eic != nullptr)
	{
		eic->BindAction(iaHorizontal, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputHorizontal);
		eic->BindAction(iaHorizontal, ETriggerEvent::Completed, this, &APlayerPawn::OnInputHorizontal);
		eic->BindAction(iaVertical, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputVertical);
		eic->BindAction(iaVertical, ETriggerEvent::Completed, this, &APlayerPawn::OnInputVertical);
		// 발사 추가
		eic->BindAction(ia_fire, ETriggerEvent::Started, this, &APlayerPawn::Fire);
	}
}

void APlayerPawn::OnInputHorizontal(const struct FInputActionValue& value)
{
	h = value.Get<float>();
}

void APlayerPawn::OnInputVertical(const struct FInputActionValue& value)
{
	v = value.Get<float>();
}

void APlayerPawn::Fire()
{
	//if (!GetWorld()) return;
	//FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100;
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>
		(bulletFactory, firePosition->GetComponentLocation(),
			firePosition->GetComponentRotation());

	UGameplayStatics::PlaySound2D(GetWorld(),fireSound);
}

