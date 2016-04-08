
#include "AudioManager.h"
#include "Core/IO/FileSystem/FileSystem.h"


AudioManager::AudioManager(void)
{
	mIsMusicEnabled=true;
	mIsEffectEnabled=true;
}


AudioManager::~AudioManager(void)
{
}

void AudioManager::PlayBackgroundMusic( Medusa::FileId res,bool isLoop/*=true*/ )
{
	RETURN_IF_FALSE(mIsMusicEnabled);
	HeapString path=FileSystem::Instance().GetReadFilePath(res);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(path.c_str(),isLoop);
}

void AudioManager::StopBackgroundMusic( bool isReleaseData/*=false*/ )
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(isReleaseData);
}

void AudioManager::PauseBackgroundMusic()
{
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AudioManager::ResumeBackgroundMusic()
{
	RETURN_IF_FALSE(mIsMusicEnabled);
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AudioManager::RewindBackgroundMusic()
{
	RETURN_IF_FALSE(mIsMusicEnabled);
	SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
}

bool AudioManager::IsBackgroundMusicPlaying()
{
	return SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying();
}

void AudioManager::PlayEffect( Medusa::FileId res,bool isLoop/*=false*/ )
{
	RETURN_IF_FALSE(mIsEffectEnabled);

	HeapString path=FileSystem::Instance().GetReadFilePath(res);
	uint id=SimpleAudioEngine::sharedEngine()->playEffect(path.c_str(),isLoop);

	mEffectDict.SetValue(FileIdStorage(res),id);
}

void AudioManager::PauseEffect( Medusa::FileId res )
{
	uint id=mEffectDict.TryGetValueWithFailedByOtherKey(res,res.GetHashCode(),0);
	if (id!=0)
	{
		SimpleAudioEngine::sharedEngine()->pauseEffect(id);
	}
	else
	{
		Log::LogInfo("Cannot find effect");
	}
}

void AudioManager::ResumeEffect( Medusa::FileId res )
{
	RETURN_IF_FALSE(mIsEffectEnabled);
	uint id=mEffectDict.TryGetValueWithFailedByOtherKey(res,res.GetHashCode(),0);
	if (id!=0)
	{
		SimpleAudioEngine::sharedEngine()->resumeEffect(id);
	}
	else
	{
		Log::LogInfo("Cannot find effect");
	}
}

void AudioManager::StopEffect( Medusa::FileId res )
{
	RETURN_IF_FALSE(mIsEffectEnabled);
	uint id=mEffectDict.RemoveOtherKeyWithValueReturned(res,res.GetHashCode(),0);
	if (id!=0)
	{
		SimpleAudioEngine::sharedEngine()->stopEffect(id);
	}
	else
	{
		Log::LogInfo("Cannot find effect");
	}
}

void AudioManager::PauseAllEffect()
{
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

void AudioManager::ResumeAllEffect()
{
	RETURN_IF_FALSE(mIsEffectEnabled);
	SimpleAudioEngine::sharedEngine()->resumeAllEffects();

}

void AudioManager::StopAllEffect()
{
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
	mEffectDict.Clear();
}

void AudioManager::PreloadEffect( Medusa::FileId res )
{
	RETURN_IF_FALSE(mIsEffectEnabled);
	HeapString path=FileSystem::Instance().GetReadFilePath(res);
	SimpleAudioEngine::sharedEngine()->preloadEffect(path.c_str());
}

void AudioManager::UnloadEffect( Medusa::FileId res )
{
	mEffectDict.RemoveOtherKey(res,res.GetHashCode());

	HeapString path=FileSystem::Instance().GetReadFilePath(res);
	SimpleAudioEngine::sharedEngine()->unloadEffect(path.c_str());

}

void AudioManager::SetIsMusicEnabled( bool val )
{
	mIsMusicEnabled = val;
	if (!mIsMusicEnabled)
	{
		PauseBackgroundMusic();
	}
	else
	{
		ResumeBackgroundMusic();
	}
}

void AudioManager::SetIsEffectEnabled( bool val )
{
	mIsEffectEnabled = val;
	if (!mIsEffectEnabled)
	{
		PauseAllEffect();
	}
	else
	{
		ResumeAllEffect();
	}
}
