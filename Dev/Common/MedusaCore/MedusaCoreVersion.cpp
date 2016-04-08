﻿#include "MedusaCoreVersion.h"

/*
	major.minor[.build[.revision]]
	The components are used by convention as follows:
	Major: Assemblies with the same name but different major versions are not interchangeable. A higher version number might indicate a major rewrite of a product where backward compatibility cannot be assumed.
	Minor: If the name and major version number on two assemblies are the same, but the minor version number is different, this indicates significant enhancement with the intention of backward compatibility. This higher minor version number might indicate a point release of a product or a fully backward-compatible new version of a product.
	Build: A difference in build number represents a recompilation of the same source. Different build numbers might be used when the processor, platform, or compiler changes.
	Revision: Assemblies with the same name, major, and minor version numbers but different revisions are intended to be fully interchangeable. A higher revision number might be used in a build that fixes a security hole in a previously released assembly.

	Subsequent versions of an assembly that differ only by build or revision numbers are considered to be Hotfix updates of the prior version.

	Version information for an assembly consists of the following four values:

	Major Version
	Minor Version 
	Build Number
	Revision Number

	max is UInt16.MaxValue -1
*/

namespace MedusaCoreVersion
{
	const char* AssemblyTitle="MedusaCore";
	const char* AssemblyDescription="";
	const char* AssemblyConfiguration="";
	const char* AssemblyCompany="Medusa";
	const char* AssemblyProduct="MedusaCore";
	const char* AssemblyCopyright="Copyright 2014";

	const Medusa::Version AssemblyVersion(1,0,2,1348);
	const char* AssemblyLastBuildDate="2014-07-01 16:39:40";
}
