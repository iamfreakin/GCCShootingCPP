// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class GCC_TOPVIEW_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;
	
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* imcPlayerInput;
	UPROPERTY(EditAnywhere)
	class UInputAction* iaHorizontal;
	UPROPERTY(EditAnywhere)
	class UInputAction* iaVertical;
	
	
private:
	float h;
	float w;
	
	void OnInputHorizontal(const struct FInputActionValue& value);
	void OnInputVertical(const struct FInputActionValue& value);
};
