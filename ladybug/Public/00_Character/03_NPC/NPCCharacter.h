// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "09_Interface/InteractionInterface.h"
#include "NPCCharacter.generated.h"


USTRUCT(BlueprintType)
struct FNPCInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag npc_Tag;
	UPROPERTY(EditAnywhere)
		FString npc_Name;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UNPCDialogueWidget> npc_UMG_DialogueWidget;
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UObject>> npc_shopList;
};
USTRUCT(BlueprintType)
struct FUnitNPCInfo : public FNPCInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UMonster>> npc_unitShopList;
};
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
		FGameplayTag npcTag;
	UPROPERTY(VisibleAnywhere)
		FString npcName;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UNPCDialogueWidget> UMG_DialogueWidget;
	UPROPERTY(EditAnywhere)
		TArray<class UObject*> shopList;

	UPROPERTY()
		class UNPCDialogueWidget* dialogueWidget;
	UPROPERTY()
		class APlayerCharacter* npcCaller;

	float interpSpeed = 3.f;
	FRotator originRotator;
	bool isInteract = false;
public:
	FGameplayTag GetNPCTag() { return npcTag; }
	class APlayerCharacter* GetCaller() { return npcCaller; }
	TArray<class UObject*>& GetShopList() { return shopList; }

	void SetUp(FNPCInfo NPCInfo);
public:
	// Interface ÇÔ¼ö
	virtual const FText GetName() override;
	virtual void InterAction(class APlayerCharacter* caller) override;
};
