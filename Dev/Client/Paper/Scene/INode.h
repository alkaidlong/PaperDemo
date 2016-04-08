#pragma once

#include "Core/Collection/SortedList.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Geometry/Cube.h"
#include "Core/String/HeapString.h"
#include "Core/Proto/Client/LayerEditor.pb.h"
#include "Scene/Event/EventArg/Gesture/TapGestureEventArg.h"
#include "Scene/Event/EventArg/Gesture/SwipeGestureEventArg.h"
#include "Scene/Event/EventArg/Gesture/PanGestureEventArg.h"
#include "Scene/Event/EventArg/Gesture/PanBeginGestureEventArg.h"
#include "Scene/Event/EventArg/Gesture/PanEndGestureEventArg.h"
#include "Scene/Event/EventArg/Gesture/PinchGestureEventArg.h"
#include "Scene/Event/EventArg/Gesture/DoubleTapGestureEventArg.h"
#include "Core/IO/FileId.h"


#include "Core/Pattern/IClone.h"
#include "PaperHeader.h"
USING_MEDUSA;
class InputDispatcher;

enum class ElementType
{
	Node = 0,
	Layer = 1,
	Sprite = 2,
	Button = 3,
	ProgressBar = 4,
	Frame = 5,
	Label = 6,
	EditBox = 7,
	List = 8,
	BMPLabel = 9,
};

typedef SortedList<INode*,DefaultCompare<INode*>,DefaultCompareForPointer<INode> > NodeList;

class INode:public Pattern::IClone<INode>
{
public:
	INode(StringRef name=StringRef::Empty);
	virtual ~INode(void);
public:
	virtual bool Initialize(){return true;}
	virtual bool OnCreated(){return true;}

	virtual bool Uninitialize(){return true;}
	virtual const CCNode* GetDrawCCNode()const{return NULL;}
	virtual CCNode* GetDrawCCNode(){return NULL;}

	virtual int GetLogicZ() const;

	virtual bool IsModal()const{return false;}

	virtual  ElementType GetElementType()const{return ElementType::Node;}

	bool operator<(const INode& node)const{return GetLogicZ()<node.GetLogicZ();}
	int Compare(const INode& node)const{return GetLogicZ()-node.GetLogicZ();}

	INode* GetParentNode() const { return mParentNode; }
	void SetParentNode(INode* val);
	bool IsRoot()const{return mParentNode==NULL;}

	void AddChild(INode* node);
	void RemoveChild(INode* node);
	void DeleteChild(INode* node);
	const NodeList& GetChildren() const { return mNodes; }
	NodeList& GetChildren() { return mNodes; }
	StringRef GetName() const { return mName; }
	void SetName(StringRef val) { mName = val; }

	INode* FindChild(StringRef name);
	const INode* FindChild(StringRef name)const;

	INode* FindChildConfidently(StringRef name);
	const INode* FindChildConfidently(StringRef name)const;

	bool HasChild(INode* node)const;

	INode* FindChildRecursively(StringRef name);
	const INode* FindChildRecursively(StringRef name)const;

	INode* FindChildWithPath(StringRef file);

	bool HasChildRecursively(INode* node)const;


	void ReorderAllChilds();
	void RemoveAllChilds();


	InputDispatcher* GetInputDispatcher();

	bool IsInputEnabled() const { return mInputEnabled; }
	void EnableInput(bool val);

	bool IsInputPassingEnabled() const { return mInputEnabled&&mInputPassingEnabled; }

	void EnableInputPassing();
	void ResetInputPassing();
	virtual Rect2F GetBoundingBox(){return Rect2F::Zero;}
	virtual Point2F TransformPoint(Point2F pos){return Point2F::Zero;}

	virtual FileId GetDefaultClickEffect()const{return FileId::Empty;}
public:
	virtual bool UpdateRecursively(float dt);
	virtual bool Update(float dt){return true;}
	virtual bool BeforeUpdate(float dt){return true;}
	virtual bool AfterUpdate(float dt){return true;}


	virtual bool EnterRecursively();
	virtual bool Enter(){return true;}

	virtual bool ExitRecursively();
	virtual bool Exit(){return true;}

	virtual bool UpdateLogicRecursively();
	virtual bool UpdateLogic(){return true;}

	virtual bool ResetLogicRecursively();
	virtual bool ResetLogic(){return true;}

public:
	bool AddTapGestureHandler(StringRef name,TapEventHandler handler,const FileId& audioEffect=FileId::Empty,GestureFlags flags=GestureFlags::None);
	bool RemoveTapGestureHandler(StringRef name,TapEventHandler handler);
	bool AddTapGestureHandler(TapEventHandler handler,const FileId& audioEffect=FileId::Empty,GestureFlags flags=GestureFlags::None);
	bool RemoveTapGestureHandler(TapEventHandler handler);

	bool AddSwipeGestureHandler(StringRef name,SwipeEventHandler handler,GestureDirection direction = GestureDirection::Horizontal,float minMoveDuration=10.0f, float minMovement=5.0f,float minVelocity=30.0f,GestureFlags flags=GestureFlags::None);
	bool RemoveSwipeGestureHandler(StringRef name,SwipeEventHandler handler);
	bool AddSwipeGestureHandler(SwipeEventHandler handler,GestureDirection direction = GestureDirection::Horizontal,float minMoveDuration=10.0f, float minMovement=5.0f,float minVelocity=30.0f,GestureFlags flags=GestureFlags::None);
	bool RemoveSwipeGestureHandler(SwipeEventHandler handler);

	bool AddPanGestureHandler(StringRef name,PanEventHandler handler,PanBeginEventHandler beginHandler,PanEndEventHandler endHandler,float minDistance,GestureFlags flags=GestureFlags::None);
	bool RemovePanGestureHandler(StringRef name,PanEventHandler handler,PanBeginEventHandler beginHandler,PanEndEventHandler endHandler);
	bool AddPanGestureHandler(PanEventHandler handler,PanBeginEventHandler beginHandler,PanEndEventHandler endHandler,float minDistance,GestureFlags flags=GestureFlags::None);
	bool RemovePanGestureHandler(PanEventHandler handler,PanBeginEventHandler beginHandler,PanEndEventHandler endHandler);

	bool AddPinchGestureHandler(StringRef name,PinchEventHandler handler,GestureFlags flags=GestureFlags::None);
	bool RemovePinchGestureHandler(StringRef name,PinchEventHandler handler);
	bool AddPinchGestureHandler(PinchEventHandler handler,GestureFlags flags=GestureFlags::None);
	bool RemovePinchGestureHandler(PinchEventHandler handler);


	bool AddDoubleTapGestureHandler(StringRef name,TapEventHandler tapHandler,DoubleTapEventHandler doubleTapHandler,float maxDuration=0.25f,GestureFlags flags=GestureFlags::None);
	bool RemoveDoubleTapGestureHandler(StringRef name,TapEventHandler tapHandler,DoubleTapEventHandler doubleTapHandler);
	bool AddDoubleTapGestureHandler(TapEventHandler tapHandler,DoubleTapEventHandler doubleTapHandler,float maxDuration=0.25f,GestureFlags flags=GestureFlags::None);
	bool RemoveDoubleTapGestureHandler(TapEventHandler tapHandler,DoubleTapEventHandler doubleTapHandler);

	void CancelOtherRecognizers(IGestureRecognizer* self);
	void ResetRecognizers();
	void ResetRecognizersRecursively();


protected:
	HeapString mName;
	Dictionary<HeapString,INode*> mNodeDict;
	NodeList mNodes;
	INode* mParentNode;
	InputDispatcher* mInputDispatcher;


	bool mInputEnabled;	//just for self
	bool mInputPassingEnabled;	//true means to need to check all children' input dispatcher recursively.

};


