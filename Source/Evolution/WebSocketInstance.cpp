// Fill out your copyright notice in the Description page of Project Settings.


#include "WebSocketInstance.h"
#include "WebSocketsModule.h"

void UWebSocketInstance::Init()
{
	Super::Init();

	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}

	//Testing Server: ws://localhost:8080
	webSocket = FWebSocketsModule::Get().CreateWebSocket("wss://hometask.eg1236.com/game1/");

	//Confirmation
	webSocket->OnConnected().AddLambda([]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, "Successfully Connected");
	});

	//Error
	webSocket->OnConnectionError().AddLambda([](const FString& Error)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, Error);
	});

	//Connection Close Message
	webSocket->OnClosed().AddLambda([](int32 Status, const FString& Reason, bool Clean)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, Clean ? FColor::Green : FColor::Red, "Close By " + Reason);
	});

	//Personal Message To Client
	webSocket->OnMessage().AddLambda([](const FString& Message)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, "Message: " + Message);
	});

	webSocket->Connect();
}


void UWebSocketInstance::Shutdown()
{
	if (webSocket->IsConnected())
	{
		webSocket->Close();
	}

	Super::Shutdown();
}
