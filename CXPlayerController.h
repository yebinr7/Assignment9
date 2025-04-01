// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CXPlayerController.generated.h"

class UCXChatInput;
/**
 *
 */
UCLASS()
class CHATX_API ACXPlayerController : public APlayerController
{
	GENERATED_BODY()
	/** ================= 1. UPROPERTY (���÷��� �ý��� ����) ================= **/
protected:

	/*
	TSubclassOf
	C++ �ڵ忡�� �����س���
	�������Ʈ Ŭ�������� �ش� ������ �������Ʈ ������
	�������� ��������� ��
	*/
	UPROPERTY(EditDefaultsOnly) // ������� ���� ������ ������ ������ �� �������Ʈ �����Ϳ�����..
		TSubclassOf<UCXChatInput> ChatInputWidgetClass;

	UPROPERTY()
	TObjectPtr<UCXChatInput> ChatInputWidgetInstance;

	/** ================= 2. UFUNCTION (���÷��� �ý��� �Լ�) ================= **/
public:
	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);
	/** ================= 3. ������ �� �ʼ� �������̵� �Լ� ================= **/
public:
	// ���� �÷��� ������ ���۵� �ֵ� �־�� �Լ�
	virtual void BeginPlay() override;
	/** ================= 4. �Ϲ� �޼��� (���÷����� �ʿ� ���� �Լ�) ================= **/
public:
	// ���ڿ� ������ �� �Լ��� ����ؼ� �����ȴ�.
	void SetChatMessageString(const FString& InChatMessageString);

	// ä��â�� �޼��� ���
	void PrintChatMessageString(const FString& InChatMessageString);
	/** ================= 5. �Ϲ� ��� ���� (���÷����� �ʿ� ���� ����) ================= **/

protected:
	FString ChatMessageString; // �� ��Ʈ�ѷ��� ������ FString 
};
