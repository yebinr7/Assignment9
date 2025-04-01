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
	/** ================= 1. UPROPERTY (리플렉션 시스템 변수) ================= **/
protected:

	/*
	TSubclassOf
	C++ 코드에서 선언해놓고
	블루프린트 클래스에서 해당 변수에 블루프린트 위젯을
	수동으로 지정해줘야 해
	*/
	UPROPERTY(EditDefaultsOnly) // 편집기능 범위 지정자 월드의 에디터 와 블루프린트 에디터에서의..
		TSubclassOf<UCXChatInput> ChatInputWidgetClass;

	UPROPERTY()
	TObjectPtr<UCXChatInput> ChatInputWidgetInstance;

	/** ================= 2. UFUNCTION (리플렉션 시스템 함수) ================= **/
public:
	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);
	/** ================= 3. 생성자 및 필수 오버라이드 함수 ================= **/
public:
	// 게임 플레이 됐을때 시작될 애들 넣어논 함수
	virtual void BeginPlay() override;
	/** ================= 4. 일반 메서드 (리플렉션이 필요 없는 함수) ================= **/
public:
	// 문자열 받으면 이 함수를 통과해서 관리된다.
	void SetChatMessageString(const FString& InChatMessageString);

	// 채팅창에 메세지 출력
	void PrintChatMessageString(const FString& InChatMessageString);
	/** ================= 5. 일반 멤버 변수 (리플렉션이 필요 없는 변수) ================= **/

protected:
	FString ChatMessageString; // 이 컨트롤러가 가지는 FString 
};
