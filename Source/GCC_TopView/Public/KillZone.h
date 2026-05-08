// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillZone.generated.h"

UCLASS()
class GCC_TOPVIEW_API AKillZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKillZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// 박스 충돌체 컴포넌트
	// 형태가 나타날 필요가 없으니 메시 컴포넌트는 불필요
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	UFUNCTION()
	void OnKillZoneOverlap(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);
};
