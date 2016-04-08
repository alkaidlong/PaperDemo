#include "Game/Battle/Logic/Buffer.h"
#include "Game/PaperScript.h"

Buffer::Buffer(uint id,uint level)
{
	PaperScript::Instance().LoadBufferScript(id);
	mScript = PaperScript::Instance().NewBufferScriptObject(id);
}

Buffer::~Buffer(void)
{
	
}

void Buffer::LoadResource()
{
	mScript->Invoke("LoadResource");
}

void Buffer::Initialize()
{
	mScript->Invoke("Initialize");
}

void Buffer::Uninitialize()
{
	mScript->Invoke("Uninitialize");
	SAFE_DELETE(mScript);
}

void Buffer::Update(float dt)
{
	mScript->Invoke("Update",dt);
}

void Buffer::SetPause(bool isPause)
{
	mScript->Invoke("SetPause",isPause);
}
