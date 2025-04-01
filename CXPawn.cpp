// CXPawn.cpp


#include "CXPawn.h"
#include "ChatX.h"


void ACXPawn::BeginPlay()
{
	Super::BeginPlay();

	FString NetModeString = ChatXFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::BeginPlay() %s [%s]"), *ChatXFunctionLibrary::GetNetModeString(this), *NetModeString);
	ChatXFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}

void ACXPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetModeString = ChatXFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::PossessedBy() %s [%s]"), *ChatXFunctionLibrary::GetNetModeString(this), *NetModeString);
	ChatXFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}
