// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class GCC_TOPVIEW_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// 충졸테 콜리전 박스 포인터 변수 선언
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* boxComponent;
	
	// 충돌체 메시 포인터 변수 선언
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* meshComponent;
};
