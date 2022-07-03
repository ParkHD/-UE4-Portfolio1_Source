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
	// ��Ʈ�ѷ��� �÷����� ĳ���� Ŭ������ ���ǵǾ����� ȣ��
	virtual void OnPossess(APawn* aPawn) override;
	virtual void PlayerTick(float DeltaTime) override;

protected:
	UPROPERTY()
		class AWorldPlayerCharacter* ownerPlayer;
	// �������Ʈ Ŭ������ �޾ƿ� ����
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMainWidget> mainWidgetClass;
	UPROPERTY(BlueprintReadOnly)
		class UMainWidget* mainWidget;
public:
	// �κ��丮 visibility Ű�� �Լ�
	void OpenInventoryWidget();
	void OpenArmyManagerWidget();
	void OpenBattleWidget(class AWorldMonsterCharacter* target);
	void OpenVillageWidget(class AVillageWorldActor* village);
};
