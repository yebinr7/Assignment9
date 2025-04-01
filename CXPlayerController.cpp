// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatX/Player/CXPlayerController.h"
#include "UI/CXChatInput.h" // �����Լ� ����ϱ� ���� 

#include "Kismet/KismetSystemLibrary.h"

#include "ChatX.h"

#include "EngineUtils.h"

#include "Kismet/GameplayStatics.h"
#include "Game/CXGameModeBase.h"

/*

����: ��ü �帧
Ŭ���̾�Ʈ: UI(ä��â) -> ��Ʈ�ѷ��� �޽��� ����.
Ŭ���̾�Ʈ -> ����: RPC�� ���� ������ ��Ʈ�ѷ��� �޽��� ����.
����: �޽����� �����ϰ� ó��.
���� -> �ٸ� Ŭ���̾�Ʈ: Multicast RPC �Ǵ� Replication���� �ٸ� �÷��̾�鿡�� �޽��� ����.
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

	// ���Ӹ�� ����Ʈ ê��Ʈ�� 
	// �������� �ִ� ���Ӹ�� ��� �������°�? �̰� ����RPC�̴ϱ�
	// ȣ���� Client������...
	// ������ ���� ��ǻ�Ϳ��� ���� �ִ�. �̰��� RPC 
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

	//0. ���� ��ü�� �ٸ� �÷��̾�鿡�Լ� ���� �ʿ䰡���� UI�� �ڱ�����Ŭ�󿡼��� ���̰� �ؾ���!
	//Owning Client�� �Ǻ��ϱ� ���ؼ� IsLocalController() �Լ��� ȣ��
	if (IsLocalController() == false)
	{
		return;
	}


	// 1. UI ���� �Է� ���� ��ȯ (���콺 ��� �����ϰ�)
	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	// 2. �������Ʈ���� ������ ���� Ŭ������ ��ȿ���� Ȯ��
	if (IsValid(ChatInputWidgetClass))
	{
		// 3. ���� Ŭ���� �ν��Ͻ� ���� (�޸𸮿� �ø�)
		ChatInputWidgetInstance = CreateWidget<UCXChatInput>(this, ChatInputWidgetClass);

		// 4. �ν��Ͻ��� ��ȿ�ϴٸ� ȭ�鿡 ���
		if (IsValid(ChatInputWidgetInstance))
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}

}

// Ŭ�󿡼�.. 
void ACXPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString; // �ϴ� �����ؼ� ������

	// ä��â�� �޾ƿ� �޼��� ���
	//PrintChatMessageString(ChatMessageString);
	if (IsLocalController() == true)
	{
		ServerRPCPrintChatMessageString(InChatMessageString);
	}
}

void ACXPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	// ��Ʈ�ѷ����� ������ �ִ� �޼��� ���� ����Ʈ �Ѵ�. ȭ�鿡 
	//UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Red, 5.0f);


	// ;���Ӱ� Chat ��ü���� ���ϰ� static 

	// ����� �α� 
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