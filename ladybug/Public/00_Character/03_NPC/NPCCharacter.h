// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "09_Interface/InteractionInterface.h"
#include "NPCCharacter.generated.h"


// NPC Data
USTRUCT(BlueprintType)
struct FNPCInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag npc_Tag;	// NPC �±�
	UPROPERTY(EditAnywhere)
		FString npc_Name;		// NPC �̸�
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UNPCDialogueWidget> npc_UMG_DialogueWidget;	// ��ȭâ ����
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UObject>> npc_shopList;				// �Ǹ��ϴ� ��ǰ ���
};
USTRUCT(BlueprintType)
struct FUnitNPCInfo : public FNPCInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UMonster>> npc_unitShopList;	// NPC�� �Ǹ� ���
};

// NPCĳ����
UCLASS()
class LADYBUG_API ANPCCharacter : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCCharacter();
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* clothMeshComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* pantMeshComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag npcTag;			// NPC�±�
	UPROPERTY(VisibleAnywhere)
		FString npcName;				// NPC�̸�
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UNPCDialogueWidget> UMG_DialogueWidget;	// ��ȭâ BP����
	UPROPERTY(EditAnywhere)
		TArray<class UObject*> shopList;			// �ǸŸ��

	UPROPERTY()
		class UNPCDialogueWidget* dialogueWidget;	// ��ȭâ ����
	UPROPERTY()
		class APlayerCharacter* npcCaller;			// NPC�� ��ȣ�ۿ� �ϰ��ִ� ���

	float interpSpeed = 3.f;	// ȸ�� �ӵ�
	FRotator originRotator;		// ������ NPC ȸ�� ��
	bool isInteract = false;	// ��ȣ�ۿ� �ϰ� �ִ� ��
public:
	FGameplayTag GetNPCTag() { return npcTag; }
	class APlayerCharacter* GetCaller() { return npcCaller; }	
	TArray<class UObject*>& GetShopList() { return shopList; }

	void SetUp(FNPCInfo NPCInfo);				// NPC Data ����
public:
	// Interface �Լ�
	virtual const FText GetName() override;								// NPC�̸�
	virtual void InterAction(class APlayerCharacter* caller) override;	// ��ȣ�ۿ�
};
