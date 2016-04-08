#include "MedusaCorePreCompiled.h"
#include "Core/Coder/CoderFactory.h"
#include "Core/Coder/LZMA/LZMADecoder.h"
#include "Core/Coder/LZMA/LZMAEncoder.h"
#include "Core/Coder/XOR/XORDecoder.h"
#include "Core/Coder/XOR/XOREncoder.h"

MEDUSA_BEGIN;


CoderFactory::CoderFactory()
{
	Register<XOREncoder>(CoreProto::FileList::FileCoder::XOREncoder);
	Register<XORDecoder>(CoreProto::FileList::FileCoder::XORDecoder);
	Register<LZMADecoder>(CoreProto::FileList::FileCoder::LZMADecoder);
	Register<LZMAEncoder>(CoreProto::FileList::FileCoder::LZMAEncoder);
}

MEDUSA_END;
