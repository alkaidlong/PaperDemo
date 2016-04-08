#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/Proto/Client/FileList.pb.h"

MEDUSA_BEGIN;

class ICoder
{
public:
	ICoder(const IEventArg& e){}
	ICoder(const MemoryByteData& e){}
	virtual ~ICoder(){}
	virtual bool CodeInPlace(MemoryByteData& data)const=0;
	virtual MemoryByteData Code(const MemoryByteData& data)const=0;
	virtual MemoryByteData CodeSmart(MemoryByteData& data)const=0;

	virtual bool TryGetResultSize(const MemoryByteData& data,size_t& outSize)const=0;
	virtual bool CodeTo(const MemoryByteData& data,MemoryByteData& outData)const=0;

};

/*
#define DECLARE_REGISTER_CODER() 													\
public:																				\
	virtual CoreProto::FileList::FileCoder::FileCoderType GetProtoName()const{return mStaticCoderType;}									\
	static CoreProto::FileList::FileCoder::FileCoderType ClassGetProtoName(){return mStaticCoderType;}									\
private:																				\
	const static CoreProto::FileList::FileCoder::FileCoderType mStaticCoderType;							\
	const static Pattern::StaticConstructor mStaticConstructor;							\
	static void SelfRegisterStaticCallback();

#define IMPLEMENT_REGISTER_CODER(className,coderType) 																					 \
	const CoreProto::FileList::FileCoder::FileCoderType className::mStaticCoderType=coderType;					 \
	const Pattern::StaticConstructor className::mStaticConstructor(SelfRegisterStaticCallback);					 \
	void className::SelfRegisterStaticCallback(){CoderFactory::Instance().Register<className>(coderType);}

	*/

MEDUSA_END;