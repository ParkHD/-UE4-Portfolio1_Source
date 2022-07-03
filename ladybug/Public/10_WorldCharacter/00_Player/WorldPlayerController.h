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
	// ��Ʈ�ѷ��� �÷����� ĳ���� Ŭ������ ���ǵǾ����� ȣ��
	virtual void OnPossess(APawn* aPawn) override;
	virtual void PlayerTick(float DeltaTime) override;

protected:
	UPROPERTY()
		class AWorldPlayerCharacter* ownerPlayer;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMainWidget> mainWidgetClass;		// �������Ʈ Ŭ������ �޾ƿ� ����
	UPROPERTY(BlueprintReadOnly)
		class UMainWidget* mainWidget;
public:
	void OpenInventoryWidget();		// �κ��丮 ����
	void OpenArmyManagerWidget();	// �δ����â ����
	void OpenBattleWidget(class AWorldMonsterCharacter* target);	// �������� â ����
	void OpenVillageWidget(class AVillageWorldActor* village);		// �������� â ����
};
