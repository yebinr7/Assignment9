// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CXGameModeBase.generated.h"

class ACXPlayerController;

/**
 * 
 */
UCLASS()
class CHATX_API ACXGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void OnPostLogin(AController* NewPlayer) override;
	
	virtual void BeginPlay() override;

	void PrintChatMessageString(ACXPlayerController* InChattingPlayerController, const FString& InChatMessageString);

	
	// 3�ڸ�
	FString GenerateSecretNumber();


	bool IsGuessNumberString(const FString& InNumberString);

	FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);

protected:
	FString SecretNumberString;

	// ;��� Ŭ�� �������ִ´���?
	TArray<TObjectPtr<ACXPlayerController>> AllPlayerControllers;

};
