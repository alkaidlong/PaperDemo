#pragma once
#include "Core/Message/IMessage.h"
#include "Proto/Server/Common/LoginToken.pb.h"
class Player;

USING_MEDUSA;

class GameMessageFactory
{
private:
	static Player* mPlayer;
	
public:
	static const ServerProto::LoginToken& GetLoginToken();
	static Player* GetPlayer() { return mPlayer; }
	static void SetPlayer(Player* val) { mPlayer = val; }

	static void SetTimeout(IMessage* message);  

#pragma region SendMessage
	template<typename T>
	static T* SendMessage(uint handlerId,IMessage::MessageEventHandler handler)
	{
		T* message=new T();
		SetTimeout(message);
		message->SetPlayer(mPlayer);
		message->FillLoginToken(GetLoginToken());
		message->SetHandlerId(handlerId);
		message->Initialize();
		message->Send(handler);
		return message;
	}

	template<typename T,typename T1>
	static T* SendMessage(T1 p1,uint handlerId,IMessage::MessageEventHandler handler)
	{
		T* message=new T();
		SetTimeout(message);
		message->SetPlayer(mPlayer);
		message->FillLoginToken(GetLoginToken());
		message->SetHandlerId(handlerId);
		message->Initialize(p1);
		message->Send(handler);
		return message;

	}

	template<typename T,typename T1,typename T2>
	static T* SendMessage(T1 p1,T2 p2,uint handlerId,IMessage::MessageEventHandler handler)
	{
		T* message=new T();
		SetTimeout(message);
		message->SetPlayer(mPlayer);
		message->FillLoginToken(GetLoginToken());
		message->SetHandlerId(handlerId);
		message->Initialize(p1,p2);
		message->Send(handler);
		return message;

	}

	template<typename T,typename T1,typename T2,typename T3>
	static T* SendMessage(T1 p1,T2 p2,T3 p3,uint handlerId,IMessage::MessageEventHandler handler)
	{
		T* message=new T();
		SetTimeout(message);
		message->SetPlayer(mPlayer);
		message->FillLoginToken(GetLoginToken());
		message->SetHandlerId(handlerId);
		message->Initialize(p1,p2,p3);
		message->Send(handler);
		return message;

	}

	template<typename T,typename T1,typename T2,typename T3,typename T4>
	static T* SendMessage(T1 p1,T2 p2,T3 p3,T4 p4,uint handlerId,IMessage::MessageEventHandler handler)
	{
		T* message=new T();
		SetTimeout(message);
		message->SetPlayer(mPlayer);
		message->FillLoginToken(GetLoginToken());
		message->SetHandlerId(handlerId);
		message->Initialize(p1,p2,p3,p4);
		message->Send(handler);
		return message;

	}

	template<typename T,typename T1,typename T2,typename T3,typename T4,typename T5>
	static T* SendMessage(T1 p1,T2 p2,T3 p3,T4 p4,T5 p5,uint handlerId,IMessage::MessageEventHandler handler)
	{
		T* message=new T();
		SetTimeout(message);
		message->SetPlayer(mPlayer);
		message->FillLoginToken(GetLoginToken());
		message->SetHandlerId(handlerId);
		message->Initialize(p1,p2,p3,p4,p5);
		message->Send(handler);
		return message;

	}

	template<typename T,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
	static T* SendMessage(T1 p1,T2 p2,T3 p3,T4 p4,T5 p5,T6 p6,uint handlerId,IMessage::MessageEventHandler handler)
	{
		T* message=new T();
		SetTimeout(message);
		message->SetPlayer(mPlayer);
		message->FillLoginToken(GetLoginToken());
		message->SetHandlerId(handlerId);
		message->Initialize(p1,p2,p3,p4,p5,p6);
		message->Send(handler);
		return message;

	}

	template<typename T,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
	static T* SendMessage(T1 p1,T2 p2,T3 p3,T4 p4,T5 p5,T6 p6,T7 p7,uint handlerId,IMessage::MessageEventHandler handler)
	{
		T* message=new T();
		SetTimeout(message);
		message->SetPlayer(mPlayer);
		message->FillLoginToken(GetLoginToken());
		message->SetHandlerId(handlerId);
		message->Initialize(p1,p2,p3,p4,p5,p6,p7);
		message->Send(handler);
		return message;

	}

	template<typename T,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
	static T* SendMessage(T1 p1,T2 p2,T3 p3,T4 p4,T5 p5,T6 p6,T7 p7,T8 p8,uint handlerId,IMessage::MessageEventHandler handler)
	{
		T* message=new T();
		SetTimeout(message);
		message->SetPlayer(mPlayer);
		message->FillLoginToken(GetLoginToken());
		message->SetHandlerId(handlerId);
		message->Initialize(p1,p2,p3,p4,p5,p6,p7,p8);
		message->Send(handler);
		return message;

	}
#pragma endregion SendMessage

};


