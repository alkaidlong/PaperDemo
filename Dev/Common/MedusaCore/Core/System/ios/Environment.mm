
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_IOS

#include "Environment.h"
#include <sys/socket.h> // Per msqr
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#import "UIDevice+Reachability.h"



/*
 Platforms
 
 iFPGA ->		??

 iPhone1,1 ->	iPhone 2G
 iPhone1,2 ->	iPhone 3G
 iPhone2,1 ->	iPhone 3GS
 iPhone3,1 ->	iPhone 4/AT&T
 iPhone3,2 ->	iPhone 4/Other Carrier?
 iPhone3,3 ->	iPhone 4 (CDMA)?
 iPhone4,1 ->	iPhone 4S
 iPhone5,1 ->	iPhone 5
 iPhone5,2 ->	iPhone 5 (GSM+CDMA)

 iPod1,1   -> iPod touch 1G 
 iPod2,1   -> iPod touch 2G 
 iPod3,1   -> iPod touch 3G
 iPod4,1   -> iPod touch 4G
 iPod5,1   -> iPod touch 5G
 
 iPad1,1   -> iPad 1G, WiFi
 iPad1,2   -> iPad 1G, 3G <- needs 3G owner to test

 iPad2,1   -> iPad2 WIFI
 iPad2,2   -> iPad2	
 iPad2,3   -> iPad2 CDMA
 iPad2,4   -> iPad2	
 iPad2,5   -> iPad Mini	WIFI
 iPad2,6   -> iPad Mini	
 iPad2,7   -> iPad Mini	GSM+CDMA

 iPad3,1   -> iPad3 WIFI
 iPad3,2   -> iPad3 GSM+CDMA
 iPad3,3   -> iPad3	
 iPad3,4   -> iPad4	WIFI
 iPad3,5   -> iPad4
 iPad3,6   -> iPad4	GSM+CDMA

 
 AppleTV2,1 -> AppleTV 2

 i386, x86_64 -> iPhone Simulator
*/

MEDUSA_BEGIN;

HeapString Environment::GetSystemInfoByName( const StringRef& inName )const
{
	size_t size;
    sysctlbyname(inName.c_str(), NULL, &size, NULL, 0);
    char *answer =new char[size];
	sysctlbyname(inName.c_str(), answer, &size, NULL, 0);
	HeapString result(answer);
	delete[] answer;
	return result;
}

int Environment::GetUIScreenWidth() const
{
	return [[UIScreen mainScreen] bounds].size.width;
}
/*
bool Environment::IsRetinaDisplay() const
{
	if ([UIScreen instancesRespondToSelector:@selector(scale)]) 
	{     
		return [[UIScreen mainScreen] scale] >1.0;
	} 
	return false;
}
*/
bool Environment::IsJailBreakHelper() const
{
	NSString *cydiaPath = @"/Applications/Cydia.app"; 
    NSString *aptPath = @"/private/var/lib/apt/"; 
    if ([[NSFileManager defaultManager] fileExistsAtPath:cydiaPath]) { 
        return true;
    } 
    if ([[NSFileManager defaultManager] fileExistsAtPath:aptPath]) { 
        return true;
    } 
    return false;
}

HeapString Environment::GetMacAddress()
{
	int					mib[6];
	size_t				len;
	char				*buf;
	unsigned char		*ptr;
	struct if_msghdr	*ifm;
	struct sockaddr_dl	*sdl;
	
	mib[0] = CTL_NET;
	mib[1] = AF_ROUTE;
	mib[2] = 0;
	mib[3] = AF_LINK;
	mib[4] = NET_RT_IFLIST;
	
	if ((mib[5] = if_nametoindex("en0")) == 0) {
		printf("Error: if_nametoindex error\n");
		return HeapString::Empty;
	}
	
	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
		printf("Error: sysctl, take 1\n");
		return HeapString::Empty;
	}
	
	if ((buf = (char*)malloc(len)) == NULL) {
		printf("Could not allocate memory. error!\n");
		return HeapString::Empty;
	}
	
	if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
		printf("Error: sysctl, take 2");
		return HeapString::Empty;
	}
	
	ifm = (struct if_msghdr *)buf;
	sdl = (struct sockaddr_dl *)(ifm + 1);
	ptr = (unsigned char *)LLADDR(sdl);
	// NSString *outstring = [NSString stringWithFormat:@"%02x:%02x:%02x:%02x:%02x:%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)];
	NSString *outstring = [NSString stringWithFormat:@"%02x%02x%02x%02x%02x%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)];
	free(buf);
	NSString* result= [outstring uppercaseString];
	const char* pStr=[result cStringUsingEncoding:NSUTF8StringEncoding];
	return HeapString(pStr);
}


bool Environment::IsNetworkAvailable()
{
    return true;
   //return [[UIDevice currentDevice] networkAvailable]==YES;
}


MEDUSA_END;

#endif