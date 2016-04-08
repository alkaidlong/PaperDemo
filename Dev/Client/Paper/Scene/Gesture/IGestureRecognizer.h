#pragma once

#include "Scene/Event/IInputHandler.h"
#include "Core/Pattern/Event.h"
#include "Core/Collection/List.h"
#include "Scene/Event/Touch.h"
#include "Scene/Event/EventArg/TouchEventArg.h"
#include "Core/Pattern/FlagsPattern.h"
#include "Core/IO/FileIdStorage.h"

USING_MEDUSA;
class INode;

enum class GestureState
{
	None,
	Begin,
	Recognizing,
	Valid,
	End,
	Failed,
	Disabled
};

enum class GestureDirection
{
	Horizontal,
	Vertical
};

STRONG_FLAGS_2(GestureFlags,SuppressTouchBegan,SuppressAudio);

typedef Pattern::Delegate<void(GestureState,GestureState)> GestureStateChangedHandler;

class IGestureRecognizer:public IInputHandler
{
public:
	Pattern::Event<void(GestureState,GestureState)> StateChangedEvent;
public:
	IGestureRecognizer(INode* node,GestureFlags flags=GestureFlags::None,const FileId& audioEffect=FileId::Empty);
	virtual ~IGestureRecognizer(void);

	virtual InputType GetInputType()const=0;

	
	virtual bool Update(float dt){return true;}

	GestureState GetState() const { return mState; }
	void SetState(GestureState state);

	GestureFlags GetFlags() const { return mFlags; }
	void SetFlags(GestureFlags val) { mFlags = val; }

	bool HasTouch()const{return mTouchEventArg.IsValid();}

	void SetIsDisabled(bool val);
	virtual bool IsValid()const=0;
	virtual bool IsFocus()const{return mState==GestureState::Valid;}

	void CancelOtherRecognizers();

	FileId GetAudioEffect() const { return mAudioEffect.ToFileId(); }
	void SetAudioEffect(const FileId& val) { mAudioEffect = val; }
protected:
	bool IsValidTouch(const Touch& touch)const;
	bool HasValidTouch(const List<Touch>& touches)const;

	Touch TransformToNodeSpace(const Touch& touch)const;
	bool TryTransformToNodeSpace(const Touch& touch,Touch& outTouch)const;
protected:
	INode* mNode;
	GestureState mState;
	GestureFlags mFlags;
	
	TouchEventArg mTouchEventArg;

	FileIdStorage mAudioEffect;
	
};



