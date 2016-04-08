#pragma once

#include "Core/Pattern/Singleton.h"
#include "Core/Proto/Client/AnimationModel.pb.h"
#include "Engine/Resource/ResourceManager.h"
#include "Core/IO/FileId.h"
#include "Core/IO/FileIdStorage.h"
USING_MEDUSA;


class AnimationModelManager : public Pattern::Singleton< AnimationModelManager >
{
	friend class Pattern::Singleton<AnimationModelManager>;
private:
	AnimationModelManager();
	~AnimationModelManager();
private:
	Dictionary<FileIdStorage,CoreProto::AnimationModel*> mModelDict;
public:
	void LoadAllModel();
	const CoreProto::AnimationModel* LoadModel( const FileId& fileID );
	const CoreProto::AnimationModel* GetModel( const FileId& fileID );

};


