#include "MedusaCorePreCompiled.h"
#include "Version.h"
#include "Core/String/StringParser.h"

MEDUSA_BEGIN;


Version::Version(uint major/*=0*/,uint minor/*=0*/,uint build/*=0*/,uint revision/*=0*/)
	:mMajor(major),
	mMinor(minor),
	mBuild(build),
	mRevision(revision)
{

}

Version::Version(const StringRef& versionString)
{
	*this=ParseFrom(versionString);
}

Version::Version(const Version& val)
	:mMajor(val.Major()),
	mMinor(val.Minor()),
	mBuild(val.Build()),
	mRevision(val.Revision())
{

}


Version& Version::operator=(const Version& val)
{
	mMajor=val.Major();
	mMinor=val.Minor();
	mBuild=val.Build();
	mRevision=val.Revision();
	return *this;
}

Version::~Version( void )
{

}

int Version::Compare(const Version& val) const
{
	if (mMajor!=val.mMajor)
	{
		return mMajor>val.mMajor?1:-1;
	}

	if (mMinor!=val.mMinor)
	{
		return mMinor>val.mMinor?1:-1;
	}

	if (mBuild!=val.mBuild)
	{
		return mBuild>val.mBuild?1:-1;
	}

	if (mRevision!=val.mRevision)
	{
		return mRevision>val.mRevision?1:-1;
	}

	return 0;
}

HeapString Version::ToString(uint fieldCount/*=4*/) const
{

	switch (fieldCount)
	{
	case 0:
		return HeapString::Empty;
	case 1:
		return StringParser::ToString(mMajor);
	case 2:
		{
			HeapString str;
			str=StringParser::ToString(mMajor);
			str+='.';
			str+=StringParser::ToString(mMinor);
			return str;
		}
		break;
	case 3:
		{
			HeapString str;
			str=StringParser::ToString(mMajor);
			str+='.';
			str+=StringParser::ToString(mMinor);
			str+='.';
			str+=StringParser::ToString(mBuild);
			return str;
		}
		break;
	case 4:
	default:
		{
			HeapString str;
			str=StringParser::ToString(mMajor);
			str+='.';
			str+=StringParser::ToString(mMinor);
			str+='.';
			str+=StringParser::ToString(mBuild);
			str+='.';
			str+=StringParser::ToString(mRevision);
			return str;
		}
		break;
	}
}

Medusa::Version Version::ParseFrom(const StringRef& versionString)
{
	Version outVersion;
	TryParse(versionString,outVersion);
	return outVersion;
}

bool Version::TryParse(const StringRef& versionString,Version& outVersion)
{
	outVersion=Version::Zero;
	List<HeapString> parts;
	StringParser::Split(versionString,StringRef("."),parts);

	uint length=parts.GetCount();
	RETURN_FALSE_IF(length<2||length>4);

	long outMajor;
	if(parts[0].TryParseInteger(outMajor))
	{
		outVersion.SetMajor(outMajor);
	}
	else
	{
		return false;
	}

	long outMinor;
	if(parts[1].TryParseInteger(outMinor))
	{
		outVersion.SetMinor(outMinor);
	}
	else
	{
		return false;
	}

	length-=2;
	if (length>0)
	{
		long outBuild;
		if(parts[2].TryParseInteger(outBuild))
		{
			outVersion.SetBuild(outBuild);
		}
		else
		{
			return false;
		}

		--length;
		if (length>0)
		{
			long outRevision;
			if(parts[3].TryParseInteger(outRevision))
			{
				outVersion.SetRevision(outRevision);
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}

const Version Version::Zero;


MEDUSA_END;
