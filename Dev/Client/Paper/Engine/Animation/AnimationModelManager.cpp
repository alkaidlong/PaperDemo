
#include "Engine/Animation/AnimationModelManager.h"
#include "Engine/Resource/ResourceManager.h"
#include "Core/IO/FileSystem/FileSystem.h"

AnimationModelManager::AnimationModelManager()
{

}
AnimationModelManager::~AnimationModelManager()
{
	SAFE_DELETE_DICTIONARY_VALUE(mModelDict);
}

const CoreProto::AnimationModel* AnimationModelManager::LoadModel( const FileId& fileID )
{
	if(FileSystem::Instance().IsFileExists(fileID))
	{
		CoreProto::AnimationModel* model = new CoreProto::AnimationModel();
		FileSystem::Instance().LoadProto(*model,fileID);
		mModelDict.Add(FileIdStorage(fileID),model);
		return model;
	}
	return NULL;
}

const CoreProto::AnimationModel* AnimationModelManager::GetModel( const FileId& fileID ) 
{
	const CoreProto::AnimationModel* model = mModelDict.TryGetValueWithFailedByOtherKey(fileID,fileID.GetHashCode(),NULL);

	if(model==NULL)
	{
		return LoadModel(fileID);
	}
	else
	{
		return model;
	}
}


void AnimationModelManager::LoadAllModel()
{

}