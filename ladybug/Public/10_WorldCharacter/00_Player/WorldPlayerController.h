// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WorldPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API AWorldPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	// 컨트롤러가 플레이할 캐릭터 클래스에 빙의되었을때 호출
	virtual void OnPossess(APawn* aPawn) override;
	virtual void PlayerTick(float DeltaTime) override;

protected:
	UPROPERTY()
		class AWorldPlayerCharacter* ownerPlayer;
	// 블루프린트 클래스를 받아올 변수
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMainWidget> mainWidgetClass;
	UPROPERTY(BlueprintReadOnly)
		class UMainWidget* mainWidget;
public:
	// 인벤토리 visibility 키는 함수
	void OpenInventoryWidget();
	void OpenArmyManagerWidget();
	void OpenBattleWidget(class AWorldMonsterCharacter* target);
	void OpenVillageWidget(class AVillageWorldActor* village);
};
