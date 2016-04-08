#pragma once
#include "MedusaCorePreCompiled.h"

#include "Core/IO/FileDefines.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/Singleton.h"

MEDUSA_BEGIN;

class Path:public Pattern::Singleton<Path>
{
	friend class Pattern::Singleton<Path>;
	Path(void);
	~Path(void);
public:
	static void CheckInvalidPathChars(StringRef path,bool checkAdditional=true);
	static HeapString ChangeExtension(StringRef path, StringRef extension);

	static bool IsPathRooted(StringRef path);
	static bool IsRelative(StringRef path);


	static HeapString Combine(StringRef path1, StringRef path2);
	static HeapString Combine(StringRef path1, StringRef path2, StringRef path3);
	static HeapString Combine(StringRef path1, StringRef path2, StringRef path3, StringRef path4);

	static HeapString CombineNoChecks(StringRef path1, StringRef path2);
	static HeapString GetDirectoryName(StringRef path);
	static HeapString GetExtension(StringRef path);
	static HeapString GetFileName(StringRef path);
	static HeapString GetFileNameWithoutExtension(StringRef path);
	static HeapString GetPathRoot(StringRef path);
	static HeapString GetTopDirectory(StringRef path);

	static bool HasExtension(StringRef path);

	static bool IsDirectorySeparator(char c){return c==DirectorySeparatorChar||c==AltDirectorySeparatorChar;}
private:

	static bool HasIllegalCharacters(StringRef path,bool checkAdditional=true);
	static void CheckSearchPattern(StringRef searchPattern);
	static size_t GetRootLength(StringRef path);
public: 
	const static int MaxDirectoryLength=255;
	const static int MaxPathLength=260;


	//It's different from C# windows. but we want to adapt to Linux. So '/' is the default choice.
	const static char AltDirectorySeparatorChar='\\';
	const static char DirectorySeparatorChar='/';

	const static char* DirectorySeparatorChars;

	const static char PathSeparator=';';
	const static char VolumeSeparatorChar=':';



	const static char InvalidFileNameChars[];
	const static char InvalidPathChars[];
	const static char RealInvalidPathChars[];
	const static char TrimEndChars[];


};

MEDUSA_END;