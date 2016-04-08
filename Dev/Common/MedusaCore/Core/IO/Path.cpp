#include "MedusaCorePreCompiled.h"
#include "Path.h"
#include "Core/Log/Log.h"
#include "Core/String/StdString.h"

MEDUSA_BEGIN;

Path::Path( void )
{

}

Path::~Path( void )
{

}

void Path::CheckInvalidPathChars( StringRef path,bool checkAdditional/*=true*/ )
{
	if (path.IsNullOrEmpty())
	{
		Log::LogError("Null path");
	}

	if (HasIllegalCharacters(path,checkAdditional))
	{
		Log::LogError("Invalid path chars");
	}
}

bool Path::HasIllegalCharacters( StringRef path,bool checkAdditional/*=true*/ )
{
	size_t length=path.Length();
	FOR_EACH_SIZE(i,length)
	{
		int num2 = path[i];
		if (((num2 == '"') || (num2 == 60)) || (((num2 == '>') || (num2 == '|')) || (num2 < 0x20)))
		{
			return true;
		}
		if (checkAdditional && ((num2 == '?') || (num2 == '*')))
		{
			return true;
		}
	}
	return false;
}



Medusa::HeapString Path::ChangeExtension( StringRef path, StringRef extension )
{
	if (path.IsNullOrEmpty())
	{
		return HeapString::Empty;
	}
	CheckInvalidPathChars(path, false);
	HeapString str = path;
	intp length = path.Length();
	while (--length >= 0)
	{
		char ch = path[length];
		if (ch == '.')
		{
			str = str.SubString(0, length);
			break;
		}
		if (IsDirectorySeparator(ch) || (ch == VolumeSeparatorChar))
		{
			break;
		}
	}

	if ((extension.IsNullOrEmpty()) || (path.IsNullOrEmpty()))
	{
		return str;
	}
	if ((extension.IsNullOrEmpty()) || (extension[0] != '.'))
	{
		str = str + ".";
	}
	return (str + extension);
}



void Path::CheckSearchPattern( StringRef searchPattern )
{
	intp num;
	while ((num = searchPattern.IndexOf("..")) != -1)
	{
		if ((num + 2) == searchPattern.Length())
		{
			Log::LogError("Invalid search pattern");
		}
		if (IsDirectorySeparator(searchPattern[num + 2]))
		{
			Log::LogError("Invalid search pattern");
		}
		searchPattern = searchPattern.SubString(num + 2);
	}
}

bool Path::IsPathRooted( StringRef path )
{
	if (!path.IsNullOrEmpty())
	{
		CheckInvalidPathChars(path, false);
		size_t length = path.Length();
		if (((length >= 1) && (IsDirectorySeparator(path[0]))) || ((length >= 2) && (path[1] == VolumeSeparatorChar)))
		{
			return true;
		}
	}
	return false;
}

Medusa::HeapString Path::CombineNoChecks( StringRef path1, StringRef path2 )
{
	if (path1.IsEmpty())
	{
		return path2;
	}
	else
	{
		if (path2.IsEmpty())
		{
			return path1;
		}
		else
		{
			char lastChar=path1[path1.Length()-1];
			char firstChar=path2[0];
			bool hasLast=IsDirectorySeparator(lastChar);
			bool hasFirst=IsDirectorySeparator(firstChar);
			if (hasLast&&hasFirst)
			{
				HeapString path1Copy=path1;
				path1Copy.RemoveFrom(path1Copy.Length()-1);
				return path1Copy+path2;
			}
			else if(!hasLast&&!hasFirst)
			{
				return HeapString(path1)+DirectorySeparatorChar+path2;
			}
			else
			{
				return HeapString(path1)+path2;
			}
		}
	}
}

Medusa::HeapString Path::Combine( StringRef path1, StringRef path2, StringRef path3, StringRef path4 )
{
	if (((path1.IsNullOrEmpty()) || (path2.IsNullOrEmpty())) || ((path3.IsNullOrEmpty()) || (path4.IsNullOrEmpty())))
	{
		Log::LogError((path1.IsNullOrEmpty()) ? "path1" : ((path2.IsNullOrEmpty()) ? "path2" : ((path3.IsNullOrEmpty()) ? "path3" : "path4")));
	}
	CheckInvalidPathChars(path1, false);
	CheckInvalidPathChars(path2, false);
	CheckInvalidPathChars(path3, false);
	CheckInvalidPathChars(path4, false);
	return CombineNoChecks(CombineNoChecks(CombineNoChecks(path1, path2), path3), path4);
}

Medusa::HeapString Path::Combine( StringRef path1, StringRef path2, StringRef path3 )
{
	if (((path1.IsNullOrEmpty()) || (path2.IsNullOrEmpty())) || (path3.IsNullOrEmpty()))
	{
		Log::LogError((path1.IsNullOrEmpty()) ? "path1" : ((path2.IsNullOrEmpty()) ? "path2" : "path3"));
	}
	CheckInvalidPathChars(path1, false);
	CheckInvalidPathChars(path2, false);
	CheckInvalidPathChars(path3, false);
	return CombineNoChecks(CombineNoChecks(path1, path2), path3);
}

Medusa::HeapString Path::Combine( StringRef path1, StringRef path2 )
{
	if ((path1.IsNullOrEmpty()) || (path2.IsNullOrEmpty()))
	{
		Log::LogError((path1.IsNullOrEmpty()) ? "path1" : "path2");
	}
	CheckInvalidPathChars(path1, false);
	CheckInvalidPathChars(path2, false);
	return CombineNoChecks(path1, path2);
}

Medusa::HeapString Path::GetDirectoryName( StringRef path )
{
	if (!path.IsNullOrEmpty())
	{
		CheckInvalidPathChars(path, false);
		size_t rootLength = GetRootLength(path);
		if (path.Length() > rootLength)
		{
			size_t length = path.Length();
			if (length == rootLength)
			{
				return HeapString::Empty;
			}
			while (length > rootLength&& !IsDirectorySeparator(path[--length]))
			{
			}
			if (length!=0)
			{
				return path.SubString(0, length);
			}
		}
	}

	return HeapString::Empty;

}

size_t Path::GetRootLength( StringRef path )
{
	CheckInvalidPathChars(path, false);
	size_t num = 0;
	size_t length = path.Length();
	if ((length >= 1) && IsDirectorySeparator(path[0]))
	{
		num = 1;
		if ((length >= 2) && IsDirectorySeparator(path[1]))
		{
			num = 2;
			size_t num3 = 2;
			while ((num < length && !IsDirectorySeparator(path[num])) || --num3 > 0)
			{
				num++;
			}
		}
		return num;
	}
	if ((length >= 2) && (path[1] == VolumeSeparatorChar))
	{
		num = 2;
		if ((length >= 3) && IsDirectorySeparator(path[2]))
		{
			num++;
		}
	}
	return num;
}

Medusa::HeapString Path::GetExtension( StringRef path )
{
	if (!path.IsNullOrEmpty())
	{
		CheckInvalidPathChars(path, false);
		size_t length = path.Length();
		intp startIndex = length;
		while (--startIndex >= 0)
		{
			char ch = path[startIndex];
			if (ch == '.')
			{
				if (startIndex != (length - 1))
				{
					return path.SubString(startIndex, length - startIndex);
				}
				return HeapString::Empty;
			}
			if (IsDirectorySeparator(ch)|| (ch == VolumeSeparatorChar))
			{
				break;
			}
		}
	}


	return HeapString::Empty;
}

Medusa::HeapString Path::GetFileName( StringRef path )
{
	if (!path.IsNullOrEmpty())
	{
		CheckInvalidPathChars(path, false);
		size_t length = path.Length();
		intp num2 = length;
		while (--num2 >= 0)
		{
			char ch = path[num2];
			if ( IsDirectorySeparator(ch)|| (ch == VolumeSeparatorChar))
			{
				return path.SubString(num2 + 1, (length - num2) - 1);
			}
		}
	}
	return path;
}

Medusa::HeapString Path::GetFileNameWithoutExtension( StringRef path )
{
	HeapString path2 = GetFileName(path);
	RETURN_SELF_IF_EMPTY(path2);
	intp length = path2.LastIndexOf('.');
	if (length == -1)
	{
		return path2;
	}
	return path2.SubString(0, length);
}

Medusa::HeapString Path::GetPathRoot( StringRef path )
{
	RETURN_SELF_IF_EMPTY(path);
	return path.SubString(0, GetRootLength(path));
}

Medusa::HeapString Path::GetTopDirectory( StringRef path )
{
	RETURN_SELF_IF_EMPTY(path);
	intp index=path.IndexOfAny(DirectorySeparatorChars);
	if (index>=0)
	{
		return path.SubString(0,index);
	}
	return HeapString::Empty;
}

bool Path::HasExtension( StringRef path )
{
	if (!path.IsNullOrEmpty())
	{
		CheckInvalidPathChars(path, false);
		intp length = path.Length();
		while (--length >= 0)
		{
			char ch = path[length];
			if (ch == '.')
			{
				return (length != (path.Length() - 1));
			}
			if (IsDirectorySeparator(ch) || (ch == VolumeSeparatorChar))
			{
				break;
			}
		}
	}
	return false;
}

bool Path::IsRelative( StringRef path )
{
	return path.Length() < 3 || path[1] != VolumeSeparatorChar
		||!IsDirectorySeparator(path[2])
		||path.Length() < 2
		||!IsDirectorySeparator(path[0])
		||!IsDirectorySeparator(path[1]);
}


const char Path::InvalidFileNameChars[]={'"', '<', '>', '|', '\0', '\x0001', '\x0002', '\x0003', '\x0004', '\x0005', '\x0006', '\a', '\b', '\t', '\n', '\v', 
	'\f', '\r', '\x000e', '\x000f', '\x0010', '\x0011', '\x0012', '\x0013', '\x0014', '\x0015', '\x0016', '\x0017', '\x0018', '\x0019', '\x001a', '\x001b', 
	'\x001c', '\x001d', '\x001e', '\x001f', ':', '*', '?', '\\', '/'};

const char Path::InvalidPathChars[]={'"', '<', '>', '|', '\0', '\x0001', '\x0002', '\x0003', '\x0004', '\x0005', '\x0006', '\a', '\b', '\t', '\n', '\v', 
	'\f', '\r', '\x000e', '\x000f', '\x0010', '\x0011', '\x0012', '\x0013', '\x0014', '\x0015', '\x0016', '\x0017', '\x0018', '\x0019', '\x001a', '\x001b', 
	'\x001c', '\x001d', '\x001e', '\x001f'};


const char Path::RealInvalidPathChars[]={'"', '<', '>', '|', '\0', '\x0001', '\x0002', '\x0003', '\x0004', '\x0005', '\x0006', '\a', '\b', '\t', '\n', '\v', 
	'\f', '\r', '\x000e', '\x000f', '\x0010', '\x0011', '\x0012', '\x0013', '\x0014', '\x0015', '\x0016', '\x0017', '\x0018', '\x0019', '\x001a', '\x001b', 
	'\x001c', '\x001d', '\x001e', '\x001f'};

const char Path::TrimEndChars[]={'\t', '\n', '\v', '\f', '\r', ' ', '\x0085', '\x00a0'};


const char* Path::DirectorySeparatorChars="\\/";

MEDUSA_END;
