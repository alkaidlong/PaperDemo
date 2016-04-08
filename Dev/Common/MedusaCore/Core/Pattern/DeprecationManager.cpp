#include "MedusaCorePreCompiled.h"
#include "DeprecationManager.h"
#include "Core/String/HeapString.h"
#include "Core/String/StackString.h"
#include "Core/String/StringParser.h"


MEDUSA_BEGIN;


void Pattern::DeprecationManager::AddDeprecateFunction( const char* funcName,const char* comment,const char* fileName,const char* lineName )
{
	mDeprecatedFunction[funcName]=comment;
	//char txt[1024];
	TStackString<char,1024> txt=StringParser::FormatStackString<char,1024>("==>Deprecated:%s\t%s\t%s\t%s\n",funcName,comment,fileName,lineName);
	MEDUSA_TRACE (txt.Buffer());
}

Pattern::DeprecationManager::~DeprecationManager()
{
	MEDUSA_TRACE( "*************************************************************\n" );
	MEDUSA_TRACE( "WARNING. You are using the following deprecated functions:\n" );

	List<char> buffer;
	FOR_EACH_COLLECTION_STL(i,mDeprecatedFunction)
	{
		const char* funcName=i->first;
		const char* comment=i->second;
		StringParser::FormatToBuffer(buffer,"==>Deprecated:%s\t%s\n",funcName,comment);
		MEDUSA_TRACE (buffer.GetItems());
	}
	MEDUSA_TRACE( "*************************************************************\n" );
	mDeprecatedFunction.clear();
}

MEDUSA_END;