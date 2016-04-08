#pragma  once
#include "Core/Coder/ICoder.h"
#include "Core/Collection/List.h"
#include "Core/Proto/Client/FileList.pb.h"


MEDUSA_BEGIN;

class FileCoderList:public List<ICoder*>
{
public:
    FileCoderList(){}
	void Initialize(const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileList_FileCoder >& coders);
	void Initialize(const List< ::Medusa::CoreProto::FileList_FileCoder,NoCompare< ::Medusa::CoreProto::FileList_FileCoder> >& coders);

	MemoryByteData Code(MemoryByteData& data)const;
	

	const static FileCoderList Empty;
};

MEDUSA_END;
