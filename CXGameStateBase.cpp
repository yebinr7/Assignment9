// CXGameStateBase.cpp


#include "CXGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Player/CXPlayerController.h"

void ACXGameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (HasAuthority() == false)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0); // 0�� �ε��� 
		if (IsValid(PC) == true)
		{
			ACXPlayerController* CXPC = Cast<ACXPlayerController>(PC);
			if (IsValid(CXPC) == true)
			{
				FString NotificationString = InNameString + TEXT(" has joined the game.");
				CXPC->PrintChatMessageString(NotificationString);
			}
		}
	}
}