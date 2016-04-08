#include "MedusaCorePreCompiled.h"
#include "FileIdStorage.h"

MEDUSA_BEGIN;


Medusa::FileIdStorage FileIdStorage::ParseFrom(const StringRef& name)
{
	FileIdStorage result(name);
	intp index=result.Name.IndexOf('-');
	if (index>=0)
	{
		intp endIndex=result.Name.LastIndexOf('.');
		if (endIndex>=0)
		{
			HeapString orderString=result.Name.SubString(index+1,endIndex-index-1);
			result.Order=StringParser::StringTo<uint>(orderString);
			result.Name.RemoveAt(index,endIndex-index);
		}
		else
		{
			result.Name.RemoveAt(index,result.Name.Length()-index);
			result.Order=0;
		}
	}

	return result;
}

MEDUSA_END;
