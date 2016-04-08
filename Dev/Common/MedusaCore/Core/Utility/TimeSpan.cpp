#include "MedusaCorePreCompiled.h"
#include "Core/Utility/TimeSpan.h"
#include "Core/String/StringParser.h"

MEDUSA_BEGIN;

HeapString TimeSpan::ToString() const
{
	return StringParser::Format("%d %d:%d:%d",GetDays(),GetHours(),GetMinutes(),GetSeconds());
}

HeapString TimeSpan::ToShortString() const
{
	return StringParser::Format("%02d:%02d:%02d",(int)GetTotalHours(),GetMinutes(),GetSeconds());
}
HeapString TimeSpan::ToTotalSecondsString() const
{
	return StringParser::Format("%d",GetTotalSeconds());
}



MEDUSA_END;