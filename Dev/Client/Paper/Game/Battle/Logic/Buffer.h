#pragma once
#include "Core/Script/ScriptObject.h"
#include "Game/Battle/Data/BufferProperty.h"
USING_MEDUSA;

class Buffer
{
public:
	Buffer(uint id,uint level);
	~Buffer(void);
public:
	void LoadResource();
	void Initialize();
	void Uninitialize();
public:
	void Update(float dt);
	void SetPause( bool isPause );
	const ScriptObject* GetScript() const { return mScript; };
private:
	ScriptObject* mScript;
};