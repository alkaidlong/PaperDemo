#pragma once

#include "MedusaCorePreCompiled.h"

/*
 *level:
 *0:highest
 *1:first
 *
 *ASSERT_LEVEL:
 *-1:disable all assert
 *0:enable level 0
 **/
//

/*
printf("%s\n",__DATE__);
printf("%s\n",__TIME__);
printf("%s\n",__TIMESTAMP__);


printf("%s\n",__FILE__);
printf("%s\n",__FUNCTION__);
printf("%s\n",__FUNCDNAME__);
printf("%s\n",__FUNCSIG__);

printf("%d\n",__LINE__);

Output:

Dec 23 2011
14:29:04
Fri Dec 23 14:28:48 2011
d:\workspace\testarray\testarray\testst~1.cpp
main
main
int __cdecl main(int,char **)
133


*/
#ifdef MEDUSA_DEBUG

#define MEDUSA_ASSERT_SILENT(cond)		assert((cond));

#define MEDUSA_ASSERT(cond,msg)		assert((cond)&&msg);
#define MEDUSA_ASSERT_IF(cond,msg)		assert((cond)&&msg);
#define MEDUSA_ASSERT_TRUE(cond,msg)		assert((cond)==true&&msg);
#define MEDUSA_ASSERT_FALSE(cond,msg)	assert((cond)==false&&msg);
#define MEDUSA_ASSERT_NULL(cond,msg)		assert((cond)==NULL&&msg);
#define MEDUSA_ASSERT_EMPTY(cond,msg)	assert((cond).IsEmpty()&&msg);
#define MEDUSA_ASSERT_ZERO(cond,msg)		assert((cond)==0&&msg);

#define MEDUSA_ASSERT_NOT(cond,msg)			assert(!(cond)&&msg);
#define MEDUSA_ASSERT_NOT_NULL(cond,msg)		assert((cond)!=NULL&&msg);
#define MEDUSA_ASSERT_NOT_EMPTY(cond,msg)	assert(!(cond).IsEmpty()&&msg);
#define MEDUSA_ASSERT_NOT_ZERO(cond,msg)		assert((cond)!=0&&msg);

#define MEDUSA_ASSERT_NULL_OR_EMPTY_STRING(cond,msg)	assert((cond).IsNullOrEmpty()&&msg);
#define MEDUSA_ASSERT_NOT_NULL_OR_EMPTY_STRING(cond,msg)	assert(!(cond).IsNullOrEmpty()&&msg);

#define MEDUSA_ASSERT_EQUAL(object,cond,msg)			assert((object)==(cond)&&msg);
#define MEDUSA_ASSERT_NOT_EQUAL(object,cond,msg)		assert((object)!=(cond)&&msg);
#define MEDUSA_ASSERT_LESS(object,cond,msg)			assert((object)<(cond)&&msg);
#define MEDUSA_ASSERT_LESS_EQUAL(object,cond,msg)			assert((object)<=(cond)&&msg);
#define MEDUSA_ASSERT_GREATER(object,cond,msg)			assert((object)>(cond)&&msg);
#define MEDUSA_ASSERT_GREATER_EQUAL(object,cond,msg)			assert((object)>=(cond)&&msg);

#define MEDUSA_ASSERT_FAILED(msg)	assert(false&&msg);
#define MEDUSA_ASSERT_NOT_IMPLEMENT()	assert(false&&"Not implement!");


#define MEDUSA_ASSERT_LEVEL_VALUE 0

#ifdef MEDUSA_ASSERT_LEVEL_VALUE
#define MEDUSA_ASSERT_LEVEL(cond,level)		if(level<=ASSERT_LEVEL){assert((cond));}
#define MEDUSA_ASSERT_LEVEL_IF(cond,level)		if(level<=ASSERT_LEVEL){assert((cond));}
#define MEDUSA_ASSERT_LEVEL_TRUE(cond,level)		if(level<=ASSERT_LEVEL){assert((cond)==true);}
#define MEDUSA_ASSERT_LEVEL_FALSE(cond,level)	if(level<=ASSERT_LEVEL){assert((cond)==false);}
#define MEDUSA_ASSERT_LEVEL_NULL(cond,level)		if(level<=ASSERT_LEVEL){assert((cond)==NULL);}
#define MEDUSA_ASSERT_LEVEL_EMPTY(cond,level)	if(level<=ASSERT_LEVEL){assert((cond).IsEmpty());}
#define MEDUSA_ASSERT_LEVEL_ZERO(cond,level)		if(level<=ASSERT_LEVEL){assert((cond)==0);}

#define MEDUSA_ASSERT_LEVEL_NULL_OR_EMPTY_STRING(cond,level)	if(level<=ASSERT_LEVEL){assert((cond).IsNullOrEmpty());}
#define MEDUSA_ASSERT_LEVEL_NOT_NULL_OR_EMPTY_STRING(cond,level)	if(level<=ASSERT_LEVEL){assert(!(cond).IsNullOrEmpty());}

#define MEDUSA_ASSERT_LEVEL_NOT(cond,level)			if(level<=ASSERT_LEVEL){assert(!(cond));}
#define MEDUSA_ASSERT_LEVEL_NOT_NULL(cond,level)		if(level<=ASSERT_LEVEL){assert((cond)!=NULL);}
#define MEDUSA_ASSERT_LEVEL_NOT_EMPTY(cond,level)	if(level<=ASSERT_LEVEL){assert(!(cond).IsEmpty());}
#define MEDUSA_ASSERT_LEVEL_NOT_ZERO(cond,level)		if(level<=ASSERT_LEVEL){assert((cond)!=0);}
			   
#define MEDUSA_ASSERT_LEVEL_EQUAL(object,cond,level)			if(level<=ASSERT_LEVEL){assert((object)==(cond));}
#define MEDUSA_ASSERT_LEVEL_NOT_EQUAL(object,cond,level)		if(level<=ASSERT_LEVEL){assert((object)!=(cond));}

#define MEDUSA_ASSERT_LEVEL_FAILED()	assert(false);

#else
#define MEDUSA_ASSERT_LEVEL(cond,level)		assert((cond));
#define MEDUSA_ASSERT_LEVEL_IF(cond,level)		assert((cond));
#define MEDUSA_ASSERT_LEVEL_TRUE(cond,level)		assert((cond)==true);
#define MEDUSA_ASSERT_LEVEL_FALSE(cond,level)	assert((cond)==false);
#define MEDUSA_ASSERT_LEVEL_NULL(cond,level)		assert((cond)==NULL);
#define MEDUSA_ASSERT_LEVEL_EMPTY(cond,level)	assert((cond).IsEmpty());
#define MEDUSA_ASSERT_LEVEL_ZERO(cond,level)		assert((cond)==0);
			   
#define MEDUSA_ASSERT_LEVEL_NOT(cond,level)			assert(!(cond));
#define MEDUSA_ASSERT_LEVEL_NOT_NULL(cond,level)		assert((cond)!=NULL);
#define MEDUSA_ASSERT_LEVEL_NOT_EMPTY(cond,level)	assert(!(cond).IsEmpty());
#define MEDUSA_ASSERT_LEVEL_NOT_ZERO(cond,level)		assert((cond)!=0);
			   
#define MEDUSA_ASSERT_LEVEL_EQUAL(object,cond,level)			assert((object)==(cond))
#define MEDUSA_ASSERT_LEVEL_NOT_EQUAL(object,cond,level)		assert((object)!=(cond))

#define MEDUSA_ASSERT_LEVEL_FAILED()	assert(false);
#endif

#else
#define MEDUSA_ASSERT_SILENT(cond)		
#define MEDUSA_ASSERT(cond,msg)
#define MEDUSA_ASSERT_IF(cond,msg)
#define MEDUSA_ASSERT_TRUE(cond,msg)
#define MEDUSA_ASSERT_FALSE(cond,msg)
#define MEDUSA_ASSERT_NULL(cond,msg)
#define MEDUSA_ASSERT_EMPTY(cond,msg)
#define MEDUSA_ASSERT_ZERO(cond,msg)

#define MEDUSA_ASSERT_NOT(cond,msg)
#define MEDUSA_ASSERT_NOT_NULL(cond,msg)
#define MEDUSA_ASSERT_NOT_EMPTY(cond,msg)
#define MEDUSA_ASSERT_NOT_ZERO(cond,msg)

#define MEDUSA_ASSERT_NULL_OR_EMPTY_STRING(cond,msg)
#define MEDUSA_ASSERT_NOT_NULL_OR_EMPTY_STRING(cond,msg)

#define MEDUSA_ASSERT_EQUAL(object,cond,msg)
#define MEDUSA_ASSERT_NOT_EQUAL(object,cond,msg)
#define MEDUSA_ASSERT_LESS(object,cond,msg)
#define MEDUSA_ASSERT_LESS_EQUAL(object,cond,msg)
#define MEDUSA_ASSERT_GREATER(object,cond,msg)
#define MEDUSA_ASSERT_GREATER_EQUAL(object,cond,msg)

#define MEDUSA_ASSERT_FAILED(msg)	
#define MEDUSA_ASSERT_NOT_IMPLEMENT()	


#define MEDUSA_ASSERT_LEVEL_VALUE 0

#ifdef MEDUSA_ASSERT_LEVEL_VALUE
#define MEDUSA_ASSERT_LEVEL(cond,level)		if(level<=ASSERT_LEVEL){((cond);}
#define MEDUSA_ASSERT_LEVEL_IF(cond,level)		if(level<=ASSERT_LEVEL){(cond);}
#define MEDUSA_ASSERT_LEVEL_TRUE(cond,level)		if(level<=ASSERT_LEVEL){(cond)==true;}
#define MEDUSA_ASSERT_LEVEL_FALSE(cond,level)	if(level<=ASSERT_LEVEL){(cond)==false;}
#define MEDUSA_ASSERT_LEVEL_NULL(cond,level)		if(level<=ASSERT_LEVEL){(cond)==NULL;}
#define MEDUSA_ASSERT_LEVEL_EMPTY(cond,level)	if(level<=ASSERT_LEVEL){(cond).IsEmpty();}
#define MEDUSA_ASSERT_LEVEL_ZERO(cond,level)		if(level<=ASSERT_LEVEL){(cond)==0;}

#define MEDUSA_ASSERT_LEVEL_NULL_OR_EMPTY_STRING(cond,level)	if(level<=ASSERT_LEVEL){(cond).IsNullOrEmpty();}
#define MEDUSA_ASSERT_LEVEL_NOT_NULL_OR_EMPTY_STRING(cond,level)	if(level<=ASSERT_LEVEL){(cond).IsNullOrEmpty();}

#define MEDUSA_ASSERT_LEVEL_NOT(cond,level)			if(level<=ASSERT_LEVEL){(cond);}
#define MEDUSA_ASSERT_LEVEL_NOT_NULL(cond,level)		if(level<=ASSERT_LEVEL){(cond)!=NULL;}
#define MEDUSA_ASSERT_LEVEL_NOT_EMPTY(cond,level)	if(level<=ASSERT_LEVEL){(cond).IsEmpty();}
#define MEDUSA_ASSERT_LEVEL_NOT_ZERO(cond,level)		if(level<=ASSERT_LEVEL){(cond)!=0;}

#define MEDUSA_ASSERT_LEVEL_EQUAL(object,cond,level)			if(level<=ASSERT_LEVEL){((object)==(cond));}
#define MEDUSA_ASSERT_LEVEL_NOT_EQUAL(object,cond,level)		if(level<=ASSERT_LEVEL){((object)!=(cond));}

#define MEDUSA_ASSERT_LEVEL_FAILED()	

#else
#define MEDUSA_ASSERT_LEVEL(cond,level)		
#define MEDUSA_ASSERT_LEVEL_IF(cond,level)		
#define MEDUSA_ASSERT_LEVEL_TRUE(cond,level)		
#define MEDUSA_ASSERT_LEVEL_FALSE(cond,level)	
#define MEDUSA_ASSERT_LEVEL_NULL(cond,level)
#define MEDUSA_ASSERT_LEVEL_EMPTY(cond,level)
#define MEDUSA_ASSERT_LEVEL_ZERO(cond,level)

#define MEDUSA_ASSERT_LEVEL_NOT(cond,level)
#define MEDUSA_ASSERT_LEVEL_NOT_NULL(cond,level)
#define MEDUSA_ASSERT_LEVEL_NOT_EMPTY(cond,level)
#define MEDUSA_ASSERT_LEVEL_NOT_ZERO(cond,level)

#define MEDUSA_ASSERT_LEVEL_EQUAL(object,cond,level)
#define MEDUSA_ASSERT_LEVEL_NOT_EQUAL(object,cond,level)

#define MEDUSA_ASSERT_LEVEL_FAILED()	
#endif
#endif


template<bool> struct CompileError;
template<> struct CompileError<true> {};

#define MEDUSA_COMPILE_ASSERT(cond, msg) { CompileError<(cond)> ERROR_##msg; (void)ERROR_##msg;	 } //(void)ERROR_##msg; to disable warning ERROR_##msg not used
#define MEDUSA_COMPILE_ASSERT_IF(cond, msg)		{ CompileError<(cond)> ERROR_##msg; (void)ERROR_##msg;}
#define MEDUSA_COMPILE_ASSERT_TRUE(cond, msg)		{ CompileError<((cond)==true)> ERROR_##msg; (void)ERROR_##msg;}
#define MEDUSA_COMPILE_ASSERT_FALSE(cond, msg)	{ CompileError<((cond)==false)> ERROR_##msg; (void)ERROR_##msg;}
#define MEDUSA_COMPILE_ASSERT_NULL(cond, msg)		{ CompileError<((cond)==NULL)> ERROR_##msg; (void)ERROR_##msg;}
#define MEDUSA_COMPILE_ASSERT_ZERO(cond, msg)		{ CompileError<((cond)==0)> ERROR_##msg; (void)ERROR_##msg;}
		
#define MEDUSA_COMPILE_ASSERT_NOT(cond, msg)			{ CompileError<(!(cond))> ERROR_##msg; (void)ERROR_##msg;}
#define MEDUSA_COMPILE_ASSERT_NOT_NULL(cond, msg)		{ CompileError<((cond)!=NULL)> ERROR_##msg; (void)ERROR_##msg;}
#define MEDUSA_COMPILE_ASSERT_NOT_ZERO(cond, msg)		{ CompileError<((cond)!=0)> ERROR_##msg; (void)ERROR_##msg;}
		
#define MEDUSA_COMPILE_ASSERT_EQUAL(object,cond, msg)		{ CompileError<((object)==(cond))> ERROR_##msg; (void)ERROR_##msg;}
#define MEDUSA_COMPILE_ASSERT_NOT_EQUAL(object,cond, msg)	{ CompileError<((object)!=(cond))> ERROR_##msg; (void)ERROR_##msg;}
