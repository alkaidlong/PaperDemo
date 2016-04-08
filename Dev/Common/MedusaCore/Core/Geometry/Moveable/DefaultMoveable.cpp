#include "MedusaCorePreCompiled.h"
#include "DefaultMoveable.h"
#include "Core/Log/Log.h"
MEDUSA_BEGIN;


DefaultMoveable::DefaultMoveable()
	:mMatrix(Matrix4::Identity),mWorldMatrix(Matrix4::Identity),
	mPosition(Point3F::Zero),mAnchor(Point3F::Zero),
	mRotation(Rotation3F::Zero),mScale(Scale3F::One),mSize(Size3F::Zero)
{
	mMatrix.SetUpdateDelegate(LazyMatrix4::TUpdateDelegateType(this,&DefaultMoveable::OnUpdateMatrix));
	mWorldMatrix.SetUpdateDelegate(LazyMatrix4::TUpdateDelegateType(this,&DefaultMoveable::OnUpdateWorldMatrix));
	mWorldInverseMatrix.SetUpdateDelegate(LazyMatrix4::TUpdateDelegateType(this,&DefaultMoveable::OnUpdateWorldInverseMatrix));
	mBoundingBox.SetUpdateDelegate(LazyBoundingBox::TUpdateDelegateType(this,&DefaultMoveable::OnUpdateBoundingBox));
	mWorldBoundingBox.SetUpdateDelegate(LazyBoundingBox::TUpdateDelegateType(this,&DefaultMoveable::OnUpdateWorldBoundingBox));

}


DefaultMoveable::~DefaultMoveable(void)
{
}

void DefaultMoveable::OnUpdateMatrix(Matrix4& transform)
{
	Point3F pivot(mAnchor.X*mSize.Width*mScale.X,mAnchor.Y*mSize.Height*mScale.Y,mAnchor.Z*mSize.Depth*mScale.Z);
	transform.ResetWorld(mScale,mRotation,mPosition,pivot);
}


void DefaultMoveable::OnUpdateWorldMatrix( Matrix4& transform )
{
	DefaultMoveable* parent=GetParentMoveable();
	if (parent!=NULL&&parent->IsWorldMatrixDirty())
	{
		ForceSetWorldMatrix(GetMatrix()*(parent->GetWorldMatrix()));
	}
	else
	{
		ForceSetWorldMatrix(GetMatrix());
	}
}


void DefaultMoveable::OnUpdateWorldInverseMatrix(Matrix4& transform)
{
	//Point3F pivot(mAnchor.X*mSize.Width*mScale.X,mAnchor.Y*mSize.Height*mScale.Y,mAnchor.Z*mSize.Depth*mScale.Z);
	//transform.ResetWorld(mScale.CreateInverse(),mRotation.CreateInverse(),-mPosition,-pivot);	//just for test

	transform=mWorldMatrix.Value();
	transform.Inverse43();
}


void DefaultMoveable::OnUpdateBoundingBox(BoundingBox& outVal)
{
	CubeF cube;
	cube.Origin=Point3F::Zero;
	cube.Size=mSize;
	outVal=GetMatrix().TransformCube(cube);
}


void DefaultMoveable::OnUpdateWorldBoundingBox(BoundingBox& outVal)
{
	CubeF cube;
	cube.Origin=Point3F::Zero;
	cube.Size=mSize;
	outVal=GetWorldMatrix().TransformCube(cube);
}

void DefaultMoveable::SetMatrix( const Matrix4& val )
{
	mMatrix.SetValue(val);
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();

	val.DecomposeXYZ(mScale,mRotation,mPosition);
	mAnchor=Point3F::Zero;

	OnMoveableDirty(MoveableChangedFlags::MatrixChanged);
}

bool DefaultMoveable::IsWorldMatrixDirty() const
{
	DefaultMoveable* parent=GetParentMoveable();
	if (parent!=NULL&&parent->IsWorldMatrixDirty())
	{
		return true;
	}
	else
	{
		return mWorldMatrix.IsDirty();
	}
}


const Matrix4& DefaultMoveable::GetWorldMatrix() const
{
	if (IsWorldMatrixDirty())
	{
		mWorldMatrix.ForceUpdate();
	}
	return mWorldMatrix.Value();
}


const Matrix4& DefaultMoveable::GetWorldInverseMatrix() const
{
	if (IsWorldMatrixDirty())
	{
		mWorldMatrix.ForceUpdate();
		mWorldInverseMatrix.ForceUpdate();
	}
	return mWorldInverseMatrix.Value();
}

void DefaultMoveable::ForceSetWorldMatrix( const Matrix4& val )
{
	mWorldMatrix.SetValue(val);
	mWorldInverseMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();

	OnMoveableDirty(MoveableChangedFlags::WorldMatrixChanged);
}

Point3F DefaultMoveable::GetWorldPosition() const
{
	return GetWorldMatrix().TransformPoint(mPosition);
}


Point3F DefaultMoveable::GetLocalPosition() const
{
	return GetMatrix().Translation();
}

Size3F DefaultMoveable::GetLocalSize() const
{
	return GetBoundingBox().Size;
}

Size3F DefaultMoveable::GetWorldSize() const
{
	return GetWorldBoundingBox().Size;
}


Medusa::Scale3F DefaultMoveable::GetWorldScale() const
{
	return GetWorldMatrix().GetScale();
}

Rotation3F DefaultMoveable::GetWorldRotation() const
{
	return GetWorldMatrix().GetRotationXYZ();
}


void DefaultMoveable::SetSize( const Size3F& val )
{
	RETURN_IF_EQUAL(mSize,val);
	mSize = val;
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::SizeChanged);
}


void DefaultMoveable::SetLocalSize(const Size3F& val)
{
	const Size3F& localSize=GetLocalSize();
	RETURN_IF_EQUAL(localSize,val);
	
	mScale.X=val.Width/localSize.Width;
	mScale.Y=val.Height/localSize.Height;
	if (!Math::IsZero(localSize.Depth))
	{
		mScale.Z=val.Depth/localSize.Depth;
	}
	else
	{
		mScale.Z=1.f;
	}

}

void DefaultMoveable::SetPosition( const Point3F& val )
{
	RETURN_IF_EQUAL(mPosition,val);

	mPosition = val;
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::PositionChanged);
}


void DefaultMoveable::SetLocalPosition(const Point3F& val)
{
	RemoveAnchor();
	SetPosition(val);
}


void DefaultMoveable::SetRotation( const Rotation3F& val )
{
	RETURN_IF_EQUAL(mRotation,val);

	mRotation = val;
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::RotationChanged);

}

void DefaultMoveable::SetScale( const Scale3F& val )
{
	RETURN_IF_EQUAL(mScale,val);

	mScale = val; 
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::ScaleChanged);

}

void DefaultMoveable::SetAnchor( const Point3F& val )
{
	RETURN_IF_EQUAL(mAnchor,val);

	mAnchor = val;
	mMatrix.SetDirty();
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
	mBoundingBox.SetDirty();
	mWorldBoundingBox.SetDirty();
	OnMoveableDirty(MoveableChangedFlags::AnchorChanged);
}

void DefaultMoveable::SetAnchorX(float val)
{
	SetAnchor(Point3F(val,mAnchor.Y,mAnchor.Z));
}

void DefaultMoveable::SetAnchorY(float val)
{
	SetAnchor(Point3F(mAnchor.X,val,mAnchor.Z));
}

void DefaultMoveable::SetAnchorZ(float val)
{
	SetAnchor(Point3F(mAnchor.X,mAnchor.Y,val));
}



void DefaultMoveable::RemoveAnchor()
{
	if (mAnchor!=Point3F::Zero)
	{
		mPosition=GetLocalPosition();
		mAnchor=Point3F::Zero;
	}
}

Point3F DefaultMoveable::TransformToWorld(const Point3F& val) const
{
	return GetWorldMatrix().TransformPoint(val);
}

Medusa::Rect2F DefaultMoveable::TransformToWorld(const Rect2F& val) const
{
	return GetWorldMatrix().TransformRect(val);
}

Point3F DefaultMoveable::TransformToLocal(const Point3F& val) const
{
	return GetWorldInverseMatrix().TransformPoint(val);
}

Medusa::Rect2F DefaultMoveable::TransformToLocal(const Rect2F& val) const
{
	return GetWorldInverseMatrix().TransformRect(val);
}

void DefaultMoveable::SetDirtyOnParentChanged()
{
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
	mWorldBoundingBox.SetDirty();
}

void DefaultMoveable::ForceSetWorldBoundingBox(const BoundingBox& val)
{
	mWorldBoundingBox=val;
}




MEDUSA_END;