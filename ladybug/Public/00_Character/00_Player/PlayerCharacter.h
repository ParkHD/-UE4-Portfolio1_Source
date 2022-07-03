// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"


// Player's BattleCharacter
UCLASS()
class LADYBUG_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform)override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class UCameraComponent* Camera;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Camera)
		class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = InventoryComp)
		class UInventoryComponent* InventoryComponent;	// 인벤토리 컴포넌트
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = InventoryComp)
		class UEquipmentComponent* EquipmentComponent;	// 장비 컴포넌트
public:
	class UCameraComponent* GetCameraComponent() { return Camera; }
	class UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }
	class UEquipmentComponent* GetEquipmentComponent() { return EquipmentComponent; }

	// 캐릭터 외형
#pragma region SkeletalMesh
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* HeadMeshComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* HelmetMeshComponent1;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* UpperBodyMeshComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* ArmorMeshComponent1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* ArmorMeshComponent2;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* ArmorMeshComponent3;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* CapeMeshComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* ShoulderMeshComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* HandMeshComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* GloveMeshComponent1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* GloveMeshComponent2;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* GloveMeshComponent3;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* LowerBodyMeshComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* PantsMeshComponent1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* PantsMeshComponent2;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* PantsMeshComponent3;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* FootMeshComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* ShoesMeshComponent1;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Pawn)
		class USkeletalMeshComponent* ShoesMeshComponent2;
public:
	class USkeletalMeshComponent* GetHelmetMesh() { return HelmetMeshComponent1; }
	class USkeletalMeshComponent* GetClothMesh() { return ArmorMeshComponent1; }
	class USkeletalMeshComponent* GetCapeMesh() { return CapeMeshComponent; }

#pragma endregion

	
protected:
	float moveDirection;				// 캐릭터 이동방향
	
public:
	bool bInputComboAttack = false;		// 공격이 콤보로 입력 되었는가
	bool isAttackPressed = false;		// 공격키가 눌렸는지
	bool isBlockPressed = false;		// 방어키가 눌렸는지
	bool isAimming = false;				// 현재 활로 조준하고 있는지
	bool isInteract = false;			// 현재 Target과 상호작용하고 있는지

	// 방향키 입력 여부 // 대시방향 구하기 위해서
	bool bLeftKey = false;
	bool bRightKey = false;
	bool bUpKey = false;
	bool bDownKey = false;
protected:
	// 원래의 SpringArm의 정보 : 카메라 이동 후 다시 원래대로 돌아오기 위함 
	UPROPERTY(EditAnywhere)
		FVector originSpringArmTargetOffset = FVector(0, 0, 100);
	UPROPERTY(EditAnywhere)
		float originArmlength = 500.f;

	// 카메라 이동 스피드
	UPROPERTY(EditAnywhere)
		float interpSpeed;
	
public:
	// <삭제> 사용안하는중 !!!
	UPROPERTY(VisibleAnywhere)
		TArray<class AItemActor*> pickUpAbleItems;

	// 상호작용 할 타겟
	UPROPERTY(VisibleAnywhere)
		class AActor* interactAbleTarget;

	// 회피(닷지) 몽타주 변수
	UPROPERTY(EditAnywhere, Category = Animation)
		class UAnimMontage* ForwardDodgeMontage;
	UPROPERTY(EditAnywhere, Category = Animation)
		class UAnimMontage* BackDodgeMontage;
	UPROPERTY(EditAnywhere, Category = Animation)
		class UAnimMontage* LeftDodgeMontage;
	UPROPERTY(EditAnywhere, Category = Animation)
		class UAnimMontage* RightDodgeMontage;
private:
	void MoveForward(float newAxisValue);	// 앞 뒤 이동
	void MoveRight(float newAxisValue);		// 좌 우 이동

	void LookUp(float newAxisValue);		// 시야 위 아래
	void Turn(float newAxisValue);			// 시야 좌 우

	virtual void Jump() override;			// 점프

	// 달리기
	void PressRun();
	void ReleaseRun();

	// 방어
	void PressBlock();
	void ReleaseBlock();

	// 아이템 줍기
	void PickUp();

	// 공격
	void PressAttack();
	void ReleaseAttack();

	// 스킬 사용
	void PressSkill1();
	void PressSkill2();

	// 상호작용
	void PressInteract();

	// 마을 나가기
	void PressOption();

	// 무기 스왑
	void SawpWeapon(float newAxisValue);

	// 회피 방향 설정
	void PressUpKey();
	void ReleaseUpKey();
	void PressDownKey();
	void ReleaseDownKey();
	void PressLeftKey();
	void ReleaseLeftKey();
	void PressRightKey();
	void ReleaseRightKey();

	// 회피
	void PressDodge();
public:
	// 캐릭터 이동방향 구하기
	float GetMoveDirection();

	void SetAttackMontage(class UAnimMontage* montage);	// 무기에 따른 공격 몽타주 설정
	void SetHitMontage(class UAnimMontage* montage);	// 무기에 따른 피격 몽타주 설정

	void SetInteract(bool binteract) { isInteract = binteract; }	// 외부에서 상호작용 종료

	void SetCharacter(class AWorldBaseCharacter* WorldCharacter);	// 캐릭터 데이터 덮어쓰기
};
