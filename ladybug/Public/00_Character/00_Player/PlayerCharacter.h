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
		class UInventoryComponent* InventoryComponent;	// �κ��丮 ������Ʈ
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = InventoryComp)
		class UEquipmentComponent* EquipmentComponent;	// ��� ������Ʈ
public:
	class UCameraComponent* GetCameraComponent() { return Camera; }
	class UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }
	class UEquipmentComponent* GetEquipmentComponent() { return EquipmentComponent; }

	// ĳ���� ����
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
	float moveDirection;				// ĳ���� �̵�����
	
public:
	bool bInputComboAttack = false;		// ������ �޺��� �Է� �Ǿ��°�
	bool isAttackPressed = false;		// ����Ű�� ���ȴ���
	bool isBlockPressed = false;		// ���Ű�� ���ȴ���
	bool isAimming = false;				// ���� Ȱ�� �����ϰ� �ִ���
	bool isInteract = false;			// ���� Target�� ��ȣ�ۿ��ϰ� �ִ���

	// ����Ű �Է� ���� // ��ù��� ���ϱ� ���ؼ�
	bool bLeftKey = false;
	bool bRightKey = false;
	bool bUpKey = false;
	bool bDownKey = false;
protected:
	// ������ SpringArm�� ���� : ī�޶� �̵� �� �ٽ� ������� ���ƿ��� ���� 
	UPROPERTY(EditAnywhere)
		FVector originSpringArmTargetOffset = FVector(0, 0, 100);
	UPROPERTY(EditAnywhere)
		float originArmlength = 500.f;

	// ī�޶� �̵� ���ǵ�
	UPROPERTY(EditAnywhere)
		float interpSpeed;
	
public:
	// <����> �����ϴ��� !!!
	UPROPERTY(VisibleAnywhere)
		TArray<class AItemActor*> pickUpAbleItems;

	// ��ȣ�ۿ� �� Ÿ��
	UPROPERTY(VisibleAnywhere)
		class AActor* interactAbleTarget;

	// ȸ��(����) ��Ÿ�� ����
	UPROPERTY(EditAnywhere, Category = Animation)
		class UAnimMontage* ForwardDodgeMontage;
	UPROPERTY(EditAnywhere, Category = Animation)
		class UAnimMontage* BackDodgeMontage;
	UPROPERTY(EditAnywhere, Category = Animation)
		class UAnimMontage* LeftDodgeMontage;
	UPROPERTY(EditAnywhere, Category = Animation)
		class UAnimMontage* RightDodgeMontage;
private:
	void MoveForward(float newAxisValue);	// �� �� �̵�
	void MoveRight(float newAxisValue);		// �� �� �̵�

	void LookUp(float newAxisValue);		// �þ� �� �Ʒ�
	void Turn(float newAxisValue);			// �þ� �� ��

	virtual void Jump() override;			// ����

	// �޸���
	void PressRun();
	void ReleaseRun();

	// ���
	void PressBlock();
	void ReleaseBlock();

	// ������ �ݱ�
	void PickUp();

	// ����
	void PressAttack();
	void ReleaseAttack();

	// ��ų ���
	void PressSkill1();
	void PressSkill2();

	// ��ȣ�ۿ�
	void PressInteract();

	// ���� ������
	void PressOption();

	// ���� ����
	void SawpWeapon(float newAxisValue);

	// ȸ�� ���� ����
	void PressUpKey();
	void ReleaseUpKey();
	void PressDownKey();
	void ReleaseDownKey();
	void PressLeftKey();
	void ReleaseLeftKey();
	void PressRightKey();
	void ReleaseRightKey();

	// ȸ��
	void PressDodge();
public:
	// ĳ���� �̵����� ���ϱ�
	float GetMoveDirection();

	void SetAttackMontage(class UAnimMontage* montage);	// ���⿡ ���� ���� ��Ÿ�� ����
	void SetHitMontage(class UAnimMontage* montage);	// ���⿡ ���� �ǰ� ��Ÿ�� ����

	void SetInteract(bool binteract) { isInteract = binteract; }	// �ܺο��� ��ȣ�ۿ� ����

	void SetCharacter(class AWorldBaseCharacter* WorldCharacter);	// ĳ���� ������ �����
};
