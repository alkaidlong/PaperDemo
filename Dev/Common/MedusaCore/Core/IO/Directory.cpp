#include "MedusaCorePreCompiled.h"
#include "Directory.h"
#include "Core/IO/FileInfo.h"
#include "Core/IO/File.h"
#include "Core/IO/Path.h"

MEDUSA_BEGIN;
#ifdef WIN32   
#define ACCESS _access   
#define MKDIR(a) _mkdir((a))   
#else
#define ACCESS access   
#define MKDIR(a) mkdir((a),S_IRWXU | S_IRWXG | S_IRWXO)   
#endif 

Directory::Directory(void)
{
}


Directory::~Directory(void)
{
}

bool Directory::CreateDir( const StringRef& dir )
{
    if (Exists(dir)) {
        return  true;
    }
    
   
    if (!dir.IsEmpty())
	{
#ifdef WIN32
        return _mkdir(dir.c_str())==0;
#else
        umask(0);
        int r=mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO );
        //int errorCode= errno; 
        
        return r==0;
#endif
  

	}

	return true;
}

bool Directory::CreateDirRecursively( const StringRef& dir )
{
	RETURN_FALSE_IF_EMPTY(dir);

	int result;  
#ifdef WIN32
	char* pszDir=_strdup(dir.c_str());  
#else
	char* pszDir=strdup(dir.c_str());  

#endif
	size_t length = strlen(pszDir);  

	// 创建中间目录   
	FOR_EACH_SIZE(i,length)
	{  
		if (Path::IsDirectorySeparator(pszDir[i]))  
		{   
			pszDir[i] = '\0';  

			//如果不存在,创建   
			result = ACCESS(pszDir,0);  
			if (result != 0&&i!=0)
			{  
				result = MKDIR(pszDir);  
				if (result != 0)  
				{  
					free(pszDir);
					return false;  
				}   
			}  
			//支持linux,将所有\换成/   
			pszDir[i] =Path::DirectorySeparatorChar;  
		}   
	}  

	result = ACCESS(pszDir,0);
	if (result==0)
	{
		free(pszDir);
		return true;
	}
	result = MKDIR(pszDir);  
	free(pszDir);
	return result==0;  

}

bool Directory::Exists( const StringRef& dir )
{
	FileMode outFileMode;
	if(File::GetFileMode(dir,outFileMode))
	{
		if (outFileMode==FileMode::Directory)
		{
			return true;
		}
	}

	return false;
}

bool Directory::CreateDirectoryForFile( const StringRef& filePath )
{
	if (File::Exists(filePath,6))
	{
		return true;
	}

	FileInfo info(filePath);
	StringRef dir=info.GetDirectory();
	return CreateDirRecursively(dir);
}


void Directory::Copy( const StringRef& fromDir,const StringRef& toDir,bool isRecursively/*=true*/ )
{
    #ifdef WIN32
	_finddata_t findData;
	HeapString curDir=Path::Combine(fromDir,"*");
	intp handle=_findfirst(curDir.c_str(),&findData);
	if (handle==-1)
	{
		return;
	}

	do 
	{
		if (findData.attrib&_A_SUBDIR)
		{
			if( (strcmp(findData.name,".") != 0 ) &&(strcmp(findData.name,"..") != 0))
			{
				if (isRecursively)
				{
					CreateDir(Path::Combine(toDir,findData.name));
					Copy(Path::Combine(fromDir,findData.name),Path::Combine(toDir,findData.name),isRecursively);
				}
			}
		}
		else
		{
			File::Copy(Path::Combine(fromDir,findData.name),Path::Combine(toDir,findData.name));
		}

	} while (_findnext(handle,&findData)==0);
	_findclose(handle);
#else
    DIR* dir=opendir(fromDir.c_str());
    if (dir==NULL) {
        return;
    }
    dirent* ent=NULL;
    struct stat statObj;
	HeapString tempDir;
    
    while ((ent=readdir(dir))!=NULL)
    {
		tempDir=Path::Combine(fromDir,ent->d_name);
        lstat(tempDir.c_str(), &statObj);
        if (S_ISDIR(statObj.st_mode))
        {
            if( (strcmp(ent->d_name,".") != 0 ) &&(strcmp(ent->d_name,"..") != 0))
			{
                if (isRecursively)
				{
                    CreateDir(Path::Combine(toDir,ent->d_name));
					Copy(Path::Combine(fromDir,ent->d_name),Path::Combine(toDir,ent->d_name),isRecursively);
                }
            }
        }
        else
        {
            File::Move(Path::Combine(fromDir,ent->d_name),Path::Combine(toDir,ent->d_name));
        }
        
    }
    closedir(dir);
#endif
}

void Directory::Move( const StringRef& fromDir,const StringRef& toDir,bool isRecursively/*=true*/ )
{
#ifdef WIN32
	_finddata_t findData;
	HeapString curDir=Path::Combine(fromDir,"*");
	intp handle=_findfirst(curDir.c_str(),&findData);
	if (handle==-1)
	{
		return;
	}

	do 
	{
		if (findData.attrib&_A_SUBDIR)
		{
			if( (strcmp(findData.name,".") != 0 ) &&(strcmp(findData.name,"..") != 0))
			{
				if (isRecursively)
				{
					CreateDir(Path::Combine(toDir,findData.name));
					Move(Path::Combine(fromDir,findData.name),Path::Combine(toDir,findData.name),isRecursively);
					RemoveDir(Path::Combine(fromDir,findData.name));
				}
			}
		}
		else
		{
			File::Move(Path::Combine(fromDir,findData.name),Path::Combine(toDir,findData.name));
		}

	} while (_findnext(handle,&findData)==0);
	_findclose(handle);
#else
    DIR* dir=opendir(fromDir.c_str());
    if (dir==NULL) {
        return;
    }
    dirent* ent=NULL;
    struct stat statObj;
	HeapString tempDir;
    
    while ((ent=readdir(dir))!=NULL)
    {
		tempDir=Path::Combine(fromDir,ent->d_name);
		lstat(tempDir.c_str(), &statObj);
        if (S_ISDIR(statObj.st_mode))
        {
            if( (strcmp(ent->d_name,".") != 0 ) &&(strcmp(ent->d_name,"..") != 0))
			{
                if (isRecursively)
				{
                    CreateDir(Path::Combine(toDir,ent->d_name));
					Move(Path::Combine(fromDir,ent->d_name),Path::Combine(toDir,ent->d_name),isRecursively);
					RemoveDir(Path::Combine(fromDir,ent->d_name));
                }
            }
        }
        else
        {
           File::Move(Path::Combine(fromDir,ent->d_name),Path::Combine(toDir,ent->d_name));
        }
        
    }
    closedir(dir);
#endif
}

void Directory::GetFiles( const StringRef& dir,List<HeapString>& outFiles,bool isRecursively/*=false*/,const StringRef& serarchPattern/*=StringRef::Empty*/ )
{
#ifdef MEDUSA_WINDOWS
	_finddata_t findData;
	HeapString curDir=dir;

	if (!serarchPattern.IsEmpty())
	{
		curDir=Path::Combine(curDir,serarchPattern);
	}
	else
	{
		curDir=Path::Combine(curDir,"*.*");
	}

	intp handle=_findfirst(curDir.c_str(),&findData);
	if (handle==-1)
	{
		return;
	}

	do 
	{
		if (findData.attrib&_A_SUBDIR)
		{
			if(isRecursively&& (strcmp(findData.name,".") != 0 ) &&(strcmp(findData.name,"..") != 0))
			{
				GetFiles(Path::Combine(dir,findData.name),outFiles,isRecursively,serarchPattern);
			}
		}
		else
		{
			outFiles.Add(Path::Combine(dir,findData.name));
		}

	} while (_findnext(handle,&findData)==0);
	_findclose(handle);
#else
	DIR* dirObj=opendir(dir.c_str());
	if (dirObj==NULL) {
		return;
	}
	dirent* ent=NULL;
	struct stat statObj;
	HeapString tempDir;
	while ((ent=readdir(dirObj))!=NULL)
	{
		tempDir=Path::Combine(dir,ent->d_name);
		lstat(tempDir.c_str(), &statObj);
		if (S_ISDIR(statObj.st_mode))
		{
			if(isRecursively&& (strcmp(ent->d_name,".") != 0 ) &&(strcmp(ent->d_name,"..") != 0))
			{
				GetFiles(Path::Combine(dir,ent->d_name),outFiles,isRecursively,serarchPattern);
			}
		}
		else
		{
			if (IsFitSearchPattern(ent->d_name,serarchPattern))
			{
				outFiles.Add(Path::Combine(dir,ent->d_name));
			}
		}

	}
	closedir(dirObj);

#endif
}



void Directory::GetDirectories( const StringRef& dir,List<HeapString>& outDirectories,bool isRecursively/*=true*/,const StringRef& serarchPattern/*=StringRef::Empty*/ )
{
#ifdef WIN32
	_finddata_t findData;
	HeapString curDir=dir;
	curDir+=Path::DirectorySeparatorChar;

	if (!serarchPattern.IsEmpty())
	{
		curDir+=serarchPattern;
	}
	else
	{
		curDir+="*";
	}

	intp handle=_findfirst(curDir.c_str(),&findData);
	if (handle==-1)
	{
		return;
	}

	do 
	{
		if (findData.attrib&_A_SUBDIR)
		{
			if( (strcmp(findData.name,".") != 0 ) &&(strcmp(findData.name,"..") != 0))
			{
				StringRef subDir=Path::Combine(dir,findData.name);
				outDirectories.Add(subDir);
				if (isRecursively)
				{
					GetDirectories(subDir,outDirectories,isRecursively,serarchPattern);
				}
			}
		}

	} while (_findnext(handle,&findData)==0);
	_findclose(handle);
#else

	DIR* dirObj=opendir(dir.c_str());
	if (dirObj==NULL) {
		return;
	}
	dirent* ent=NULL;
	struct stat statObj;
	HeapString tempDir;

	while ((ent=readdir(dirObj))!=NULL)
	{
		tempDir=Path::Combine(dir,ent->d_name);
		lstat(tempDir.c_str(), &statObj);

		if (S_ISDIR(statObj.st_mode))
		{
			if( (strcmp(ent->d_name,".") != 0 ) &&(strcmp(ent->d_name,"..") != 0))
			{
                
                StringRef subDir=Path::Combine(dir,ent->d_name);
				if (IsFitSearchPattern(ent->d_name,serarchPattern))
				{
					outDirectories.Add(subDir);
				}
				
				if (isRecursively)
				{
					GetDirectories(subDir,outDirectories,isRecursively,serarchPattern);
				}
			}
		}
	}
	closedir(dirObj);
#endif
}


bool Directory::RemoveDir( const StringRef& dir )
{
	if (!dir.IsEmpty())
	{
#ifdef WIN32
        return _rmdir(dir.c_str())==0;
#else
        return rmdir(dir.c_str())==0;
#endif
        

	}

	return true;

}

bool Directory::RemoveDirRecursively( const StringRef& dir )
{
#ifdef WIN32
	_finddata_t findData;
	StringRef curDir=Path::Combine(dir,"*");
	intp handle=_findfirst(curDir.c_str(),&findData);
	if (handle==-1)
	{
		return false;
	}

	do 
	{
		if (findData.attrib&_A_SUBDIR)
		{
			if( (strcmp(findData.name,".") != 0 ) &&(strcmp(findData.name,"..") != 0))
			{
				StringRef subDir=Path::Combine(dir,findData.name);
				RemoveDirRecursively(subDir);
				RemoveDir(subDir);
			}
		}
		else
		{
			File::Delete(Path::Combine(dir,findData.name));
		}

	} while (_findnext(handle,&findData)==0);
	_findclose(handle);
#else
	DIR* dirObj=opendir(dir.c_str());
	if (dirObj==NULL) {
		return false;
	}
	dirent* ent=NULL;
	struct stat statObj;
	HeapString tempDir;

	while ((ent=readdir(dirObj))!=NULL)
	{
		tempDir=Path::Combine(dir,ent->d_name);
		lstat(tempDir.c_str(), &statObj);
		if (S_ISDIR(statObj.st_mode))
		{
			if( (strcmp(ent->d_name,".") != 0 ) &&(strcmp(ent->d_name,"..") != 0))
			{
				HeapString subDir=Path::Combine(dir,ent->d_name);
				RemoveDirRecursively(subDir);
				RemoveDir(subDir);
			}
		}
		else
		{
			File::Delete(Path::Combine(dir,ent->d_name));
		}

	}
	closedir(dirObj);

#endif

	return true;
}

bool Directory::IsFitSearchPattern( const StringRef& fileName,const StringRef& serarchPattern )
{
	RETURN_TRUE_IF_EMPTY(serarchPattern);
	intp index=serarchPattern.IndexOf('*');
	if (index>=0)
	{
		if (index>0&&serarchPattern[index-1]=='.')	//contains .*
		{
			FileInfo info(fileName);
			StringRef name= serarchPattern.SubString(0,index-1);
			return info.GetFullName()==name;
		}
		else if(index+1<(int)serarchPattern.Length()&&serarchPattern[index+1]=='.')	//contains *.
		{
			FileInfo info(fileName);
			StringRef ext= serarchPattern.SubString(index+1);
			return info.GetExtension()==ext;
		}
		else	//only *
		{
			return true;
		}
	}
	else
	{
		return fileName==serarchPattern;
	}
	
}


MEDUSA_END;
