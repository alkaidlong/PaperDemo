#include "MedusaCorePreCompiled.h"
#include "Core/System/EnvironmentTag.h"
#include "Core/Math/MathHeader.h"
#include "Core/IO/Path.h"
#include "Core/Log/Log.h"
#include "Core/String/StringParser.h"

MEDUSA_BEGIN;


EnvironmentTag::EnvironmentTag():Version(Math::IntMinValue),Device(Math::IntMinValue),Language(Math::IntMinValue)
{

}

int EnvironmentTag::GetDiffScore( PublishVersions fileVersion,PublishVersions targetVersion )
{
	if ((fileVersion&targetVersion)==targetVersion)
	{
		return (fileVersion^targetVersion).ToInt();
	}
	return Math::IntMinValue;
}

int EnvironmentTag::GetDiffScore( PublishDevices fileDevice,PublishDevices targetDevice )
{
	if ((fileDevice&targetDevice)==targetDevice)
	{
		return (fileDevice^targetDevice).ToInt();
	}
	return Math::IntMinValue;
}

int EnvironmentTag::GetDiffScore( PublishLanguages fileLanguage,PublishLanguages targetLanguage )
{
	if ((fileLanguage&targetLanguage)==targetLanguage)
	{
		return (fileLanguage^targetLanguage).ToInt();
	}
	return Math::IntMinValue;
}


int EnvironmentTag::GetDiffScore( const EnvironmentTag& tag ) const
{
	int versionDiff=GetDiffScore(Version,tag.Version);
	int deviceDiff=GetDiffScore(Device,tag.Device);
	int languageDiff=GetDiffScore(Language,tag.Language);

	if (versionDiff<0||deviceDiff<0||languageDiff<0)	//not match
	{
		return Math::IntMinValue;
	}

	return (versionDiff<<16)|(deviceDiff<<8)|(languageDiff);	//diff
}

bool EnvironmentTag::IsMatch( const EnvironmentTag& tag ) const
{
	return GetDiffScore(tag)!=Math::IntMinValue;
}

Medusa::EnvironmentTag EnvironmentTag::Parse( StringRef fileName )
{
	if (!fileName.Contains('-'))
	{
		return MatchAll;
	}

	HeapString rawName=Path::GetFileNameWithoutExtension(fileName);
	rawName.RemoveBeginExclude('-');
	if (rawName.IsEmpty())
	{
		return MatchAll;
	}
	

	List<HeapString> outResults;
	StringParser::Split<char>(rawName,"-",outResults);
	if (outResults.IsEmpty())
	{
		return MatchAll;
	}

	int resultTag=0;
	FOR_EACH_COLLECTION(i,outResults)
	{
		const HeapString& str=*i;
		int* tempTag=mTagDict.TryGetValue(str);
		if(tempTag!=NULL)
		{
			resultTag|=*tempTag;
		}
		else
		{
			Log::LogErrorFormat("Invalid tag:%s",str.c_str());
		}
	}

	return EnvironmentTag(resultTag);
}


void EnvironmentTag::InitializeDict()
{
	FOR_EACH_SIZE(i,PublishVersions::Size)
	{
		StringRef name=PublishVersions::Names[i];
		mTagDict.Add(name,PublishVersions::Values[i]<<16);
	}

	FOR_EACH_SIZE(i,PublishDevices::Size)
	{
		StringRef name=PublishDevices::Names[i];
		mTagDict.Add(name,PublishDevices::Values[i]<<8);
	}

	FOR_EACH_SIZE(i,PublishLanguages::Size)
	{
		StringRef name=PublishLanguages::Names[i];
		mTagDict.Add(name,PublishLanguages::Values[i]<<16);
	}
}

Dictionary<StringRef,int> EnvironmentTag::mTagDict;
const EnvironmentTag EnvironmentTag::MatchAll(PublishVersions::All,PublishDevices::All,PublishLanguages::All);
MEDUSA_IMPLEMENT_STATIC_CONSTRUCTOR(EnvironmentTag,InitializeDict);
MEDUSA_END;
