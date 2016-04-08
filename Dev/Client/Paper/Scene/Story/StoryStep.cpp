#include "Scene/Story/StoryGroup.h"

#include "Game/PaperScript.h"
#include "Core/Script/ScriptManager.h"
#include "Config/ServerGameConfig.h"


StoryStep::StoryStep(StringRef fun):mFunName(fun)
{

}

StoryStep::~StoryStep()
{

}

bool StoryStep::Initialize()
{
	return true;
}

bool StoryStep::UnInitialize()
{
	return true;
}
