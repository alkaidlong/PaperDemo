#pragma once
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Rotation3.h"
#include "Core/Geometry/Scale3.h"
#include "Core/Geometry/Matrix4.h"

MEDUSA_BEGIN;

class TransformMoveable
{
public:
	TransformMoveable();
	virtual ~TransformMoveable(void);

	const Matrix4& GetMatrix()  { return mMatrix;}
	void SetMatrix(const Matrix4& val);
	bool IsMatrixDirty()const{return false;}

	const CubeF& GetBoundingBox() const { return mBoundingBox; }
	void SetBoundingBox(const CubeF& val){mBoundingBox=val;}

	const Matrix4& GetWorldMatrix(){return mWorldMatrix.Value();}
	bool IsWorldMatrixDirty()const{return mWorldMatrix.IsDirty();}
	void SetWorldMatrixDirty(){mWorldMatrix.SetDirty();mWorldInverseMatrix.SetDirty();}
	void ForceSetWorldMatrix(const Matrix4& val){mWorldMatrix=val;}
	bool TryUpdateWorldMatrix(){return mWorldMatrix.TryUpdate();}

	size_t GetWorldMatrixVersion()const{return mWorldMatrix.Version();}

	const Matrix4& GetWorldInverseMatrix(){return mWorldInverseMatrix.Value();}

protected:
	virtual TransformMoveable* GetParentMoveable(){return NULL;}
	void OnUpdateWorldMatrix(Matrix4& transform);
	void OnUpdateWorldInverseMatrix(Matrix4& transform);

protected:

	Matrix4 mMatrix;
	LazyMatrix4 mWorldMatrix;
	LazyMatrix4 mWorldInverseMatrix;

	CubeF mBoundingBox;	//self bounding box

};

MEDUSA_END;