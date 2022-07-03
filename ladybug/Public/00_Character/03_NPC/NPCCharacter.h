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
		FGameplayTag npc_Tag;	// NPC 태그
	UPROPERTY(EditAnywhere)
		FString npc_Name;		// NPC 이름
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UNPCDialogueWidget> npc_UMG_DialogueWidget;	// 대화창 위젯
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UObject>> npc_shopList;				// 판매하는 물품 목록
};
USTRUCT(BlueprintType)
struct FUnitNPCInfo : public FNPCInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UMonster>> npc_unitShopList;	// NPC의 판매 목록
};

// NPC캐릭터
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
		FGameplayTag npcTag;			// NPC태그
	UPROPERTY(VisibleAnywhere)
		FString npcName;				// NPC이름
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UNPCDialogueWidget> UMG_DialogueWidget;	// 대화창 BP위젯
	UPROPERTY(EditAnywhere)
		TArray<class UObject*> shopList;			// 판매목록

	UPROPERTY()
		class UNPCDialogueWidget* dialogueWidget;	// 대화창 위젯
	UPROPERTY()
		class APlayerCharacter* npcCaller;			// NPC와 상호작용 하고있는 대상

	float interpSpeed = 3.f;	// 회전 속도
	FRotator originRotator;		// 원래의 NPC 회전 값
	bool isInteract = false;	// 상호작용 하고 있는 지
public:
	FGameplayTag GetNPCTag() { return npcTag; }
	class APlayerCharacter* GetCaller() { return npcCaller; }	
	TArray<class UObject*>& GetShopList() { return shopList; }

	void SetUp(FNPCInfo NPCInfo);				// NPC Data 설정
public:
	// Interface 함수
	virtual const FText GetName() override;								// NPC이름
	virtual void InterAction(class APlayerCharacter* caller) override;	// 상호작용
};
