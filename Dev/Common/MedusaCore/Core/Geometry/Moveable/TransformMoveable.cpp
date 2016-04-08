#include "MedusaCorePreCompiled.h"
#include "TransformMoveable.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


TransformMoveable::TransformMoveable()
	:mMatrix(Matrix4::Identity),mWorldMatrix(Matrix4::Identity)
{
	mWorldMatrix.SetUpdateDelegate(LazyMatrix4::TUpdateDelegateType(this,&TransformMoveable::OnUpdateWorldMatrix));
	mWorldInverseMatrix.SetUpdateDelegate(LazyMatrix4::TUpdateDelegateType(this,&TransformMoveable::OnUpdateWorldInverseMatrix));

}


TransformMoveable::~TransformMoveable(void)
{
}


void TransformMoveable::OnUpdateWorldMatrix( Matrix4& transform )
{
	TransformMoveable* parent=GetParentMoveable();
	if (parent!=NULL&&parent->IsWorldMatrixDirty())
	{
		ForceSetWorldMatrix(GetMatrix()*(parent->GetWorldMatrix()));
	}
	else
	{
		ForceSetWorldMatrix(GetMatrix());
	}
}


void TransformMoveable::OnUpdateWorldInverseMatrix(Matrix4& transform)
{
	transform=mWorldMatrix.Value();
	transform.Inverse43();
}

void TransformMoveable::SetMatrix( const Matrix4& val )
{
	mMatrix=val;
	mWorldMatrix.SetDirty();
	mWorldInverseMatrix.SetDirty();
}


MEDUSA_END;