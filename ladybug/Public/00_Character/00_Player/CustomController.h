// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomController.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API ACustomController : public APlayerController
{
	GENERATED_BODY()

protected:
	// ��Ʈ�ѷ��� �÷����� ĳ���� Ŭ������ ���ǵǾ����� ȣ��
	virtual void OnPossess(APawn* aPawn) override;
	virtual void PlayerTick(float DeltaTime) override;

protected:
	UPROPERTY()
		class APlayerCharacter* ownerPlayer;
	// �������Ʈ Ŭ������ �޾ƿ� ����
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UBattleMainWidget> mainWidgetClass;
	UPROPERTY(BlueprintReadOnly)
		class UBattleMainWidget* mainWidget;
public:
	void TurnOnInteractKey(bool bTurn);

	void TurnOnAimWidget(bool bTurn);
	FVector2D GetAimWidgetSize();
	void SetUpAimSize(FVector2D size2D);

	void SetUpTargetName(FText target);
	void OpenBattleResult();
	void OpenItemManger(TArray<class UItem*> targetItemList);
	void OpenVillageExitWidget();

};
