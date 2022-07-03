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
	// ��Ʈ�ѷ��� �÷����� ĳ���� Ŭ������ ���ǵǾ����� ȣ��
	virtual void OnPossess(APawn* aPawn) override;

protected:
	UPROPERTY()
		class APlayerCharacter* ownerPlayer;
	// �������Ʈ Ŭ������ �޾ƿ� ����
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UBattleMainWidget> mainWidgetClass;
	UPROPERTY(BlueprintReadOnly)
		class UBattleMainWidget* mainWidget;
public:
	void TurnOnInteractKey(bool bTurn);		// ��ȣ�ۿ� ���� Ű��
	void SetUpTargetName(FText target);		// ��ȣ�ۿ� ������ Target�̸� ���� 

	void TurnOnAimWidget(bool bTurn);		// zoom�� Aim ���� Ű��
	FVector2D GetAimWidgetSize();			// Aim ���� ũ��
	void SetUpAimSize(FVector2D size2D);	// Aim ���� ũ�� ����

	void OpenBattleResult();				// ���� ��� ���� Ű��
	// ����ǰ ���� ���� Ű��
	void OpenItemManger(TArray<class UItem*> targetItemList);
	void OpenVillageExitWidget();			// ���� ������ ���� Ű��
};
