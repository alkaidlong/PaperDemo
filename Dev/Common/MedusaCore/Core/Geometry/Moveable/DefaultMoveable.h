#pragma once
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Rotation3.h"
#include "Core/Geometry/Scale3.h"
#include "Core/Geometry/Matrix4.h"
#include "Core/Pattern/LazyValue.h"
#include "Core/Geometry/Cube.h"

MEDUSA_BEGIN;

//model => local => world

class DefaultMoveable
{
public:
	DefaultMoveable();
	virtual ~DefaultMoveable(void);

	const Size3F& GetSize() const { return mSize; }
	void SetSize(const Size3F& val);
	void SetSize(float width,float height,float depth=0.f){SetSize(Size3F(width,height,depth));}

	Size3F GetLocalSize()const;
	void SetLocalSize(const Size3F& val);
	void SetLocalSize(float width,float height,float depth=0.f){SetLocalSize(Size3F(width,height,depth));}

	Size3F GetWorldSize()const;

	const Point3F& GetPosition() const { return mPosition; }
	void SetPosition(const Point3F& val);
	void SetPosition(float x,float y,float z=0.f){SetPosition(Point3F(x,y,z));}
	void SetPositionX(float x){SetPosition(Point3F(x,mPosition.Y,mPosition.Z));}
	void SetPositionY(float y){SetPosition(Point3F(mPosition.X,y,mPosition.Z));}
	void Move(const Point3F& val){SetPosition(mPosition+val);}


	Point3F GetLocalPosition()const;	//left bottom, without anchor
	void SetLocalPosition(const Point3F& val);
	void SetLocalPosition(float x,float y,float z=0.f){SetLocalPosition(Point3F(x,y,z));}

	Point3F GetWorldPosition()const;

	const Point3F& GetAnchor() const { return mAnchor; }
	void SetAnchor(const Point3F& val);
	void SetAnchor(float x,float y,float z=0.f){SetAnchor(Point3F(x,y,z));}

	void SetAnchorX(float val);
	void SetAnchorY(float val);
	void SetAnchorZ(float val);


	void RemoveAnchor();	//keep local position not changed

	const Rotation3F& GetRotation() const { return mRotation; }
	void SetRotation(const Rotation3F& val);
	void SetRotation(float x,float y,float z=0.f){SetRotation(Rotation3F(x,y,z));}


	Rotation3F GetWorldRotation()const;

	const Scale3F& GetScale() const { return mScale; }
	void SetScale(const Scale3F& val);
	void SetScale(float x,float y,float z=1.f){SetScale(Scale3F(x,y,z));}
	void SetScaleX(float x){SetScale(Scale3F(x,mScale.Y,mScale.Z));}
	void SetScaleY(float y){SetScale(Scale3F(mScale.X,y,mScale.Z));}



	Scale3F GetWorldScale()const;

	const Matrix4& GetMatrix()const{ return mMatrix.Value(); }
	void SetMatrix(const Matrix4& val);
	bool IsMatrixDirty()const{return mMatrix.IsDirty();}

	const Matrix4& GetWorldMatrix()const;
	bool IsWorldMatrixDirty()const;
	void ForceSetWorldMatrix(const Matrix4& val);
	bool TryUpdateWorldMatrix()const{return mWorldMatrix.TryUpdate();}
	size_t GetWorldMatrixVersion()const{return mWorldMatrix.Version();}

	const Matrix4& GetWorldInverseMatrix()const;

	const BoundingBox& GetBoundingBox()const{return mBoundingBox.Value();}

	const BoundingBox& GetWorldBoundingBox()const{return mWorldBoundingBox.Value();}
	void ForceSetWorldBoundingBox(const BoundingBox& val);
public:
	Point3F TransformToWorld(const Point3F& val)const;
	Point3F TransformToLocal(const Point3F& val)const;

	Rect2F TransformToWorld(const Rect2F& val)const;
	Rect2F TransformToLocal(const Rect2F& val)const;
protected:
	virtual DefaultMoveable* GetParentMoveable()const{return NULL;}
	virtual void OnMoveableDirty(MoveableChangedFlags chagnedFlags){}
	void SetDirtyOnParentChanged();

private:
	void OnUpdateMatrix(Matrix4& transform);
	void OnUpdateWorldMatrix(Matrix4& transform);
	void OnUpdateWorldInverseMatrix(Matrix4& transform);
	void OnUpdateBoundingBox(BoundingBox& outVal);
	void OnUpdateWorldBoundingBox(BoundingBox& outVal);

protected:
	Size3F mSize;
	
	Point3F mAnchor;
	Point3F mPosition;
	Rotation3F mRotation;
	Scale3F mScale;

	LazyMatrix4 mMatrix;
	LazyMatrix4 mWorldMatrix;
	LazyMatrix4 mWorldInverseMatrix;


	LazyBoundingBox mBoundingBox;	//self bounding box
	LazyBoundingBox mWorldBoundingBox;	//recursive bounding box
};

MEDUSA_END;