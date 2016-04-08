#pragma once
#include "Core/Message/IMessage.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/FlagsPattern.h"
#include "Core/Message/MessageEventArg.h"
#include "Proto/Server/Logic/HireType.pb.h"
#include "Core/Collection/Dictionary.h"
#include "Message/IMessageCenter.h"

USING_MEDUSA;


class MockMessageCenter:public Pattern::Singleton<MockMessageCenter>,public IMessageCenter
{
	friend class Pattern::Singleton<MockMessageCenter>;
	MockMessageCenter(void);
	virtual ~MockMessageCenter(void);
public:
	virtual void Update(float dt);
public:
	virtual bool ProcessConnectError(IMessage* message,MessageErrorReportSuppress errorReportSuppress);
	virtual bool ProcessAuthError(IMessage* message,MessageErrorReportSuppress errorReportSuppress);
	virtual bool ProcessFailedError(IMessage* message,MessageErrorReportSuppress errorReportSuppress);

protected:
	virtual void ShowActivityIndicator();
	virtual void HideActivityIndicator();
	virtual void UpdateCurrentScene();

};

