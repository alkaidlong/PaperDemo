#pragma once
#include "Platform/Platform.h"
#include "Core/Pattern/Singleton.h"
#include "Core/IO/FileIdStorage.h"
#include "PaperHeader.h"
#include "Core/Collection/Dictionary.h"

USING_MEDUSA;


class AudioManager:public Pattern::Singleton<AudioManager>
{
	friend class Pattern::Singleton<AudioManager>;
	typedef Dictionary<FileIdStorage,uint> EffectDict;

private:
	AudioManager(void);
	~AudioManager(void);
public:
	void PlayBackgroundMusic(Medusa::FileId res,bool isLoop=true);
	void StopBackgroundMusic(bool isReleaseData=false);
	void PauseBackgroundMusic();
	void ResumeBackgroundMusic();
	void RewindBackgroundMusic();
	bool IsBackgroundMusicPlaying();

	void PlayEffect(Medusa::FileId res,bool isLoop=false);
	void PauseEffect(Medusa::FileId res);
	void ResumeEffect(Medusa::FileId res);
	void StopEffect(Medusa::FileId res);

	void PauseAllEffect();
	void ResumeAllEffect();
	void StopAllEffect();

	void PreloadEffect(Medusa::FileId res);
	void UnloadEffect(Medusa::FileId res);
public:
	bool IsMusicEnabled() const { return mIsMusicEnabled; }
	void SetIsMusicEnabled(bool val);
	bool IsEffectEnabled() const { return mIsEffectEnabled; }
	void SetIsEffectEnabled(bool val);
private:
	bool mIsMusicEnabled;
	bool mIsEffectEnabled;
	EffectDict mEffectDict;
};

