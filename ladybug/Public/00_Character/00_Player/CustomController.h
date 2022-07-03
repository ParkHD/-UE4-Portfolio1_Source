// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomController.generated.h"


// BattleCharacter Controller
UCLASS()
class LADYBUG_API ACustomController : public APlayerController
{
	GENERATED_BODY()

protected:
	// 컨트롤러가 플레이할 캐릭터 클래스에 빙의되었을때 호출
	virtual void OnPossess(APawn* aPawn) override;

protected:
	UPROPERTY()
		class APlayerCharacter* ownerPlayer;
	// 블루프린트 클래스를 받아올 변수
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UBattleMainWidget> mainWidgetClass;
	UPROPERTY(BlueprintReadOnly)
		class UBattleMainWidget* mainWidget;
public:
	void TurnOnInteractKey(bool bTurn);		// 상호작용 위젯 키기
	void SetUpTargetName(FText target);		// 상호작용 위젯의 Target이름 설정 

	void TurnOnAimWidget(bool bTurn);		// zoom시 Aim 위젯 키기
	FVector2D GetAimWidgetSize();			// Aim 위젯 크기
	void SetUpAimSize(FVector2D size2D);	// Aim 위젯 크기 설정

	void OpenBattleResult();				// 전투 결과 위젯 키기
	// 전리품 관리 위젯 키기
	void OpenItemManger(TArray<class UItem*> targetItemList);
	void OpenVillageExitWidget();			// 마을 나가기 위젯 키기
};
