// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GCC_TOPVIEW_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* buttonRestart;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* buttonQuit;
	
	
protected:
	// 위젯 초기화 함수
	virtual void NativeConstruct() override;
	
private:
	// 재시작 기능
	UFUNCTION()
	void Restart();
	
	// 종료 기능
	UFUNCTION()
	void Quit();
};