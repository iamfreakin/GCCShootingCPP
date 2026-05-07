// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class GCC_TOPVIEW_API AEnemyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyActor();
	
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;
	// 이동 속도
	UPROPERTY(EditAnywhere)
	float moveSpeed = 600.f;
	// 플레이어 추적 확률 (0~100)
	UPROPERTY(EditAnywhere)
	int32 traceRate = 50;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	// 방향
	FVector dir;
};
