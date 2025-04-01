// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatX/Player/CXPlayerController.h"
#include "UI/CXChatInput.h" // 위젯함수 사용하기 위해 

#include "Kismet/KismetSystemLibrary.h"

#include "ChatX.h"

#include "EngineUtils.h"

#include "Kismet/GameplayStatics.h"
#include "Game/CXGameModeBase.h"

/*

정리: 전체 흐름
클라이언트: UI(채팅창) -> 컨트롤러로 메시지 전달.
클라이언트 -> 서버: RPC를 통해 서버의 컨트롤러로 메시지 전송.
서버: 메시지를 관리하고 처리.
서버 -> 다른 클라이언트: Multicast RPC 또는 Replication으로 다른 플레이어들에게 메시지 전달.
*/




void ACXPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);

}

void ACXPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{

	/*for (TActorIterator<ACXPlayerController> It(GetWorld()); It; ++It)
	{
		ACXPlayerController* CXPlayerController = *It;
		if (IsValid(CXPlayerController) == true)
		{
			CXPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
		}
	}*/

	// 게임모드 프린트 챗스트링 
	// 서버에만 있는 게임모드 어떻게 가져오는가? 이건 서버RPC이니깐
	// 호출은 Client이지만...
	// 로직은 서버 컴퓨터에서 돌고 있다. 이것이 RPC 
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		ACXGameModeBase* CXGM = Cast<ACXGameModeBase>(GM);
		if (IsValid(CXGM) == true)
		{
			CXGM->PrintChatMessageString(this, InChatMessageString);
		}
	}
}

void ACXPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//0. 위젯 자체는 다른 플레이어들에게서 보일 필요가없는 UI임 자기전용클라에서만 보이게 해야함!
	//Owning Client를 판별하기 위해서 IsLocalController() 함수를 호출
	if (IsLocalController() == false)
	{
		return;
	}


	// 1. UI 전용 입력 모드로 전환 (마우스 사용 가능하게)
	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	// 2. 블루프린트에서 설정한 위젯 클래스가 유효한지 확인
	if (IsValid(ChatInputWidgetClass))
	{
		// 3. 위젯 클래스 인스턴스 생성 (메모리에 올림)
		ChatInputWidgetInstance = CreateWidget<UCXChatInput>(this, ChatInputWidgetClass);

		// 4. 인스턴스가 유효하다면 화면에 띄움
		if (IsValid(ChatInputWidgetInstance))
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}

}

// 클라에서.. 
void ACXPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString; // 일단 복사해서 가져옴

	// 채팅창에 받아온 메세지 출력
	//PrintChatMessageString(ChatMessageString);
	if (IsLocalController() == true)
	{
		ServerRPCPrintChatMessageString(InChatMessageString);
	}
}

void ACXPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	// 컨트롤러에서 가지고 있는 메세지 값을 프린트 한다. 화면에 
	//UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Red, 5.0f);


	// ;새롭게 Chat 객체생성 안하고 static 

	// 디버깅 로그 
	/*FString NetModeString = ChatXFunctionLibrary::GetNetModeString(this);
	FString CombinedMessageString = FString::Printf(TEXT("%s: %s"), *NetModeString, *InChatMessageString);
	ChatXFunctionLibrary::MyPrintString(this, CombinedMessageString, 10.f);*/

	ChatXFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);

}


//void ACXPlayerController::ClientRPCPrintChatMessageString(const FString& InChatMessageString)
//{
//	PrintChatMessageString(InChatMessageString);
//}
//
//void ACXPlayerController::ServerRPCPrintChatMessageString(const FString& InChatMessageString)
//{
//	for (TActorIterator<ACXPlayerController> It(GetWorld()); It; ++It)
//	{
//		ACXPlayerController* CXPlayerController = *It;
//		if (IsValid(CXPlayerController) == true)
//		{
//			CXPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
//		}
//	}
//}