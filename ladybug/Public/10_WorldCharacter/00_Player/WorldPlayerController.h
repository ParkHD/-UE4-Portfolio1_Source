// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WorldPlayerController.generated.h"

/**
 * Players's WorldCharacter's Controller
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
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMainWidget> mainWidgetClass;		// 블루프린트 클래스를 받아올 변수
	UPROPERTY(BlueprintReadOnly)
		class UMainWidget* mainWidget;
public:
	void OpenInventoryWidget();		// 인벤토리 열기
	void OpenArmyManagerWidget();	// 부대관리창 열기
	void OpenBattleWidget(class AWorldMonsterCharacter* target);	// 전투진입 창 열기
	void OpenVillageWidget(class AVillageWorldActor* village);		// 마을진입 창 열기
};
