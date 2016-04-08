
#include "Scene/Event/InputDispatcher.h"
#include "Core/Log/Log.h"
#include "Scene/Event/EventArg/TouchEventArg.h"
#include "Scene/Event/EventArg/KeyDownEventArg.h"
#include "Scene/Event/EventArg/KeyUpEventArg.h"
#include "Scene/Event/EventArg/ScrollEventArg.h"
#include "Scene/Event/EventArg/CharInputEventArg.h"
#include "Config/PaperConfig.h"



InputDispatcher::InputDispatcher(INode* node)
{
	mNode=node;
}

InputDispatcher::~InputDispatcher()
{
	SAFE_DELETE_DICTIONARY_VALUE(mHandlers);
}


IInputHandler* InputDispatcher::FindFocusHandler() const
{
	FOR_EACH_COLLECTION(i,mHandlers)
	{
		IInputHandler* handler=(*i).Value;
		if (handler->IsFocus())
		{
			return handler;
		}
	}
	return NULL;
}

void InputDispatcher::TouchesBegan( TouchEventArg& e )
{
	RETURN_IF_EMPTY(mHandlers);
	IInputHandler* focusHandler=FindFocusHandler();
	if (focusHandler!=NULL)
	{
		focusHandler->TouchesBegan(e);
		return;
	}


	FOR_EACH_COLLECTION(i,mHandlers)
	{
		IInputHandler* handler=(*i).Value;
		handler->TouchesBegan(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

void InputDispatcher::TouchesMoved( TouchEventArg& e )
{
	RETURN_IF_EMPTY(mHandlers);
	IInputHandler* focusHandler=FindFocusHandler();
	if (focusHandler!=NULL)
	{
		focusHandler->TouchesMoved(e);
		return;
	}

	FOR_EACH_COLLECTION(i,mHandlers)
	{
		IInputHandler* handler=(*i).Value;
		handler->TouchesMoved(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

void InputDispatcher::TouchesEnded( TouchEventArg& e )
{
	RETURN_IF_EMPTY(mHandlers);
	IInputHandler* focusHandler=FindFocusHandler();
	if (focusHandler!=NULL)
	{
		focusHandler->TouchesEnded(e);
		return;
	}

	FOR_EACH_COLLECTION(i,mHandlers)
	{
		IInputHandler* handler=(*i).Value;
		handler->TouchesEnded(e);
		RETURN_IF_TRUE(e.Handled);
	}
}


void InputDispatcher::TryFireEvent( TouchEventArg& e )
{
	FOR_EACH_COLLECTION(i,mHandlers)
	{
		IInputHandler* handler=(*i).Value;
		handler->TryFireEvent(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

void InputDispatcher::TouchesCancelled( TouchEventArg& e )
{
	FOR_EACH_COLLECTION(i,mHandlers)
	{
		IInputHandler* handler=(*i).Value;
		handler->TouchesCancelled(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

bool InputDispatcher::Update( float dt )
{
	FOR_EACH_COLLECTION(i,mHandlers)
	{
		IInputHandler* handler=(*i).Value;
		RETURN_FALSE_IF_FALSE(handler->Update(dt));
	}

	return true;

}


void InputDispatcher::KeyDown( KeyDownEventArg& e )
{
	FOR_EACH_COLLECTION(i,mHandlers)
	{
		IInputHandler* handler=(*i).Value;
		handler->KeyDown(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

void InputDispatcher::KeyUp( KeyUpEventArg& e )
{
	FOR_EACH_COLLECTION(i,mHandlers)
	{
		IInputHandler* handler=(*i).Value;
		handler->KeyUp(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

void InputDispatcher::CharInput( CharInputEventArg& e )
{
	FOR_EACH_COLLECTION(i,mHandlers)
	{
		IInputHandler* handler=(*i).Value;
		handler->CharInput(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

void InputDispatcher::Scroll( ScrollEventArg& e )
{
	FOR_EACH_COLLECTION(i,mHandlers)
	{
		IInputHandler* handler=(*i).Value;
		handler->Scroll(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

void InputDispatcher::Reset()
{
	FOR_EACH_COLLECTION(i,mHandlers)
	{
		IInputHandler* hander=(*i).Value;
		hander->Reset();
	}
}

void InputDispatcher::CancelOtherRecognizers(IGestureRecognizer* self)
{
	FOR_EACH_COLLECTION(i,mHandlers)
	{
		IInputHandler* hander=(*i).Value;
		if (hander!=self)
		{
			hander->Reset();
		}
	}
}


TapGestureRecognizer* InputDispatcher::AddTapGestureRecognizer(const FileId& audioEffect/*=FileId::Empty*/,GestureFlags flags/*=GestureFlags::None*/)
{
	TapGestureRecognizer* recognizer=(TapGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::Tap,NULL);
	if (recognizer==NULL)
	{
		if (audioEffect.IsValid())
		{
			recognizer=new TapGestureRecognizer(mNode,flags,audioEffect);
		}
		else
		{
			std::string commonEffect=PaperConfig::Instance().CommonClickEffect();
			FileId defaultEffect(commonEffect.c_str());
			recognizer=new TapGestureRecognizer(mNode,flags,defaultEffect);
		}

		mHandlers.Add(InputType::Tap,recognizer);
		return recognizer;
	}
	else
	{
		if (audioEffect.IsValid())
		{
			recognizer->SetAudioEffect(audioEffect);
		}
		recognizer->SetFlags(flags);
		return recognizer;
	}
}


SwipeGestureRecognizer* InputDispatcher::AddSwipeGestureRecognizer(GestureDirection direction,float minMoveDuration, float minMovement,float minVelocity,GestureFlags flags/*=GestureFlags::None*/)
{
	SwipeGestureRecognizer* recognizer=(SwipeGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::Swipe,NULL);
	if (recognizer==NULL)
	{
		recognizer=new SwipeGestureRecognizer(mNode,direction,minMoveDuration,minMovement,minVelocity,flags);
		mHandlers.Add(InputType::Swipe,recognizer);
		return recognizer;
	}
	else
	{
		recognizer->SetFlags(flags);
		return recognizer;
	}
}



PanGestureRecognizer* InputDispatcher::AddPanGestureRecognizer( float minDistance ,GestureFlags flags/*=GestureFlags::None*/)
{
	PanGestureRecognizer* recognizer=(PanGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::Pan,NULL);
	if (recognizer==NULL)
	{
		recognizer=new PanGestureRecognizer(mNode,minDistance,flags);
		mHandlers.Add(InputType::Pan,recognizer);
		return recognizer;
	}
	else
	{
		recognizer->SetFlags(flags);
		return recognizer;
	}
}


PinchGestureRecognizer* InputDispatcher::AddPinchGestureRecognizer(GestureFlags flags/*=GestureFlags::None*/)
{
	PinchGestureRecognizer* recognizer=(PinchGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::Pinch,NULL);
	if (recognizer==NULL)
	{
		recognizer=new PinchGestureRecognizer(mNode,flags);
		mHandlers.Add(InputType::Pinch,recognizer);
		return recognizer;
	}
	else
	{
		recognizer->SetFlags(flags);
		return recognizer;
	}
}

bool InputDispatcher::AddTapGestureHandler( TapEventHandler handler ,const FileId& audioEffect/*=FileId::Empty*/,GestureFlags flags/*=GestureFlags::None*/)
{
	TapGestureRecognizer* recognizer=AddTapGestureRecognizer(audioEffect,flags);
	if(recognizer->OnTap.Contains(handler))
	{
		Log::LogError("Duplicate add gesture handler");
		return false;
	}
	recognizer->OnTap+=handler;
	return !recognizer->OnTap.IsEmpty();
}

bool InputDispatcher::RemoveTapGestureHandler( TapEventHandler handler )
{
	TapGestureRecognizer* recognizer=(TapGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::Tap,NULL);
	if (recognizer==NULL)
	{
		Log::LogError("Cannot find handler");
		return false;
	}
	recognizer->OnTap-=handler;
	return true;

}

bool InputDispatcher::RemoveAllTapGestureHandler()
{
	TapGestureRecognizer* recognizer=(TapGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::Tap,NULL);
	mHandlers.RemoveKey(InputType::Tap);
	SAFE_DELETE(recognizer);
	return true;
}

bool InputDispatcher::AddSwipeGestureHandler( SwipeEventHandler handler,GestureDirection direction,float minMoveDuration, float minMovement,float minVelocity ,GestureFlags flags/*=GestureFlags::None*/)
{
	SwipeGestureRecognizer* recognizer=AddSwipeGestureRecognizer(direction,minMoveDuration,minMovement,minVelocity,flags);
	if(recognizer->OnSwipe.Contains(handler))
	{
		Log::LogError("Duplicate add gesture handler");
		return false;
	}
	recognizer->OnSwipe+=handler;
	return !recognizer->OnSwipe.IsEmpty();
}

bool InputDispatcher::RemoveSwipeGestureHandler( SwipeEventHandler handler )
{
	SwipeGestureRecognizer* recognizer=(SwipeGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::Swipe,NULL);
	if (recognizer==NULL)
	{
		Log::LogError("Cannot find handler");
		return false;
	}
	recognizer->OnSwipe-=handler;
	return true;
}

bool InputDispatcher::RemoveAllSwipeGestureHandler()
{
	SwipeGestureRecognizer* recognizer=(SwipeGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::Swipe,NULL);
	mHandlers.RemoveKey(InputType::Swipe);
	SAFE_DELETE(recognizer);
	return true;
}



bool InputDispatcher::AddPanGestureHandler( PanEventHandler handler,PanBeginEventHandler beginHandler,PanEndEventHandler endHandler,float minDistance ,GestureFlags flags/*=GestureFlags::None*/)
{
	PanGestureRecognizer* recognizer=AddPanGestureRecognizer(minDistance,flags);
	if(recognizer->OnPan.Contains(handler)||recognizer->OnBegin.Contains(beginHandler)||recognizer->OnEnd.Contains(endHandler))
	{
		Log::LogError("Duplicate add gesture handler");
		return false;
	}
	recognizer->OnPan+=handler;
	recognizer->OnBegin+=beginHandler;
	recognizer->OnEnd+=endHandler;

	return !recognizer->OnPan.IsEmpty()&&!recognizer->OnBegin.IsEmpty()&&!recognizer->OnEnd.IsEmpty();
}

bool InputDispatcher::RemovePanGestureHandler( PanEventHandler handler,PanBeginEventHandler beginHandler,PanEndEventHandler endHandler )
{
	PanGestureRecognizer* recognizer=(PanGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::Pan,NULL);
	if (recognizer==NULL)
	{
		Log::LogError("Cannot find handler");
		return false;
	}
	recognizer->OnPan-=handler;
	recognizer->OnBegin-=beginHandler;
	recognizer->OnEnd-=endHandler;

	return true;
}

bool InputDispatcher::RemoveAllPanGestureHandler()
{
	PanGestureRecognizer* recognizer=(PanGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::Pan,NULL);
	mHandlers.RemoveKey(InputType::Pan);
	SAFE_DELETE(recognizer);
	return true;
}

bool InputDispatcher::AddPinchGestureHandler( PinchEventHandler handler ,GestureFlags flags/*=GestureFlags::None*/)
{
	PinchGestureRecognizer* recognizer=AddPinchGestureRecognizer(flags);
	if(recognizer->OnPinch.Contains(handler))
	{
		Log::LogError("Duplicate add gesture handler");
		return false;
	}
	recognizer->OnPinch+=handler;
	return !recognizer->OnPinch.IsEmpty();
}

bool InputDispatcher::RemovePinchGestureHandler( PinchEventHandler handler )
{
	PinchGestureRecognizer* recognizer=(PinchGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::Pinch,NULL);
	if (recognizer==NULL)
	{
		Log::LogError("Cannot find handler");
		return false;
	}
	recognizer->OnPinch-=handler;
	return true;
}

bool InputDispatcher::RemoveAllPinchGestureHandler()
{
	PinchGestureRecognizer* recognizer=(PinchGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::Pinch,NULL);
	mHandlers.RemoveKey(InputType::Pinch);
	SAFE_DELETE(recognizer);
	return true;
}


DoubleTapGestureRecognizer* InputDispatcher::AddDoubleTapGestureRecognizer(float maxDuration,GestureFlags flags/*=GestureFlags::None*/)
{
	DoubleTapGestureRecognizer* recognizer=(DoubleTapGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::DoubleTap,NULL);
	if (recognizer==NULL)
	{
		recognizer=new DoubleTapGestureRecognizer(mNode,maxDuration,flags);
		mHandlers.Add(InputType::DoubleTap,recognizer);
		return recognizer;
	}
	else
	{
		recognizer->SetFlags(flags);
		return recognizer;
	}
}


bool InputDispatcher::AddDoubleTapGestureHandler(TapEventHandler tapHandler,DoubleTapEventHandler doubleTapHandler,float maxDuration,GestureFlags flags/*=GestureFlags::None*/)
{
	DoubleTapGestureRecognizer* recognizer=AddDoubleTapGestureRecognizer(maxDuration,flags);
	if(recognizer->OnTap.Contains(tapHandler)||recognizer->OnDoubleTap.Contains(doubleTapHandler))
	{
		Log::LogError("Duplicate add gesture handler");
		return false;
	}
	recognizer->OnTap+=tapHandler;
	recognizer->OnDoubleTap+=doubleTapHandler;

	return !recognizer->OnTap.IsEmpty()&&!recognizer->OnDoubleTap.IsEmpty();
}


bool InputDispatcher::RemoveDoubleTapGestureHandler(TapEventHandler tapHandler,DoubleTapEventHandler doubleTapHandler)
{
	DoubleTapGestureRecognizer* recognizer=(DoubleTapGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::DoubleTap,NULL);
	if (recognizer==NULL)
	{
		Log::LogError("Cannot find handler");
		return false;
	}
	recognizer->OnTap-=tapHandler;
	recognizer->OnDoubleTap-=doubleTapHandler;

	return true;
}

bool InputDispatcher::RemoveAllDoubleTapGestureHandler()
{
	DoubleTapGestureRecognizer* recognizer=(DoubleTapGestureRecognizer*)mHandlers.TryGetValueWithFailed(InputType::DoubleTap,NULL);
	mHandlers.RemoveKey(InputType::DoubleTap);
	SAFE_DELETE(recognizer);
	return true;
}

