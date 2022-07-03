// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "97_SaveGame/SaveVariable.h"
#include "ArmyComponent.generated.h"

// 부대관리 컴포넌트
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LADYBUG_API UArmyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArmyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	UPROPERTY(VisibleAnywhere)
		TArray<class UMonster*> ArmyList;	// 부대 리스트
public:
	const TArray<class UMonster*>& GetArmyList() { return ArmyList; }

	bool IsHaveArmy() { return ArmyList.Num() > 0; }	// 부대가 비었는가?
	void AddArmy(class UMonster* army);					// 부대원 추가

	// 데이터 덮어쓰기
	void SetArmyComponentData(FArmyComponentSave Data);	
};
