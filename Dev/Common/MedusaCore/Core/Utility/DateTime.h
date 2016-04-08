#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Utility/TimeSpan.h"

MEDUSA_BEGIN;

//struct tm 
//{
// int tm_sec;     /* seconds after the minute - [0,59] */
// int tm_min;     /* minutes after the hour - [0,59] */
// int tm_hour;    /* hours since midnight - [0,23] */
// int tm_mday;    /* day of the month - [1,31] */
// int tm_mon;     /* months since January - [0,11] */
// int tm_year;    /* years since 1900 */
// int tm_wday;    /* days since Sunday - [0,6] */
// int tm_yday;    /* days since January 1 - [0,365] */
// int tm_isdst;   /* daylight savings time flag */
//};

class DateTime
{
public:
	static void SetTimeZone(StringRef timezone);
	static void SetTimeZoneToUTC();
	static bool IsDayLight();
	static long GetTimeZoneSeconds();
	static HeapString GetTimeZoneName();
	static void PrintTimeZone();


	static DateTime Parse(const StringRef& strDateTime,bool isUTC=true);//yyyy-MM-dd HH:mm:ss	//month begins from 1
	static DateTime Parse(const StringRef& strDateTime,const StringRef& format,bool isUTC=true);	//month begins from 1
	static DateTime Now();
	static DateTime UTCNow();

	static uint DaysInMonth(uint year,uint month);
	static size_t Ticks();
public:
	static DateTime* TryParse(const StringRef& strDateTime,bool isUTC=true);	//month begins from 1
	static DateTime* TryParse(const StringRef& strDateTime,const StringRef& format,bool isUTC=true);	//month begins from 1

public:    
	DateTime(time_t seconds,bool isUTC=true);
	DateTime(uint year,uint month,uint day,uint hour=0,uint minute=0,uint second=0,bool isUTC=true);
	DateTime(const StringRef& strDateTime,bool isUTC=true);	//month begins from 1
	DateTime(const StringRef& strDateTime, const StringRef& format,bool isUTC=true);	//month begins from 1
	DateTime(const DateTime& dateTime);
	DateTime& operator=(const DateTime& dateTime);
public:
	void AddSeconds(int seconds); 
	void AddMinutes(int minutes){AddSeconds(minutes *60);}
	void AddHours(int hours){AddMinutes(hours*60);}
	void AddDays(int days){AddHours(days*24);}
	void AddWeeks(int weeks){AddDays(weeks*7);}
	void AddMonths(int Months);
	void AddYears(int years);
public:
	static int Compare(const DateTime& value1,const DateTime& value2){return value1.CompareTo(value2);}
	int CompareTo(const DateTime& val) const{return (int)(mTotalSeconds - val.mTotalSeconds);}
	bool Equals(const DateTime& dateTime) const{return mTotalSeconds == dateTime.mTotalSeconds;}
	static bool Equals(const DateTime& value1,const DateTime& value2){return value1.mTotalSeconds == value2.mTotalSeconds;}

	HeapString ToString() const;//default: %Y-%m-%d %H:%M:%S
	HeapString ToString(const StringRef& format) const;
	HeapString ToShortDateString() const;
	HeapString ToTotalSecondsString() const;

public:        
	uint GetYears() const{return (uint)mDate.tm_year+1900;}
	void SetYears(uint years){mDate.tm_year=years-1900;}

	uint GetMonths() const{return (uint)mDate.tm_mon;}	//month begins from 0
	void SetMonths(uint val){mDate.tm_mon=val;}

	uint GetDays() const{return (uint)mDate.tm_mday;}
	void SetDays(uint val){mDate.tm_mday=val;}

	uint GetHours() const{return (uint)mDate.tm_hour;}
	void SetHours(uint val){mDate.tm_hour=val;}

	uint GetMinutes() const{return (uint)mDate.tm_min;}
	void SetMinutes(uint val){mDate.tm_min=val;}

	uint GetSeconds() const{return (uint)mDate.tm_sec;}
	void SetSeconds(uint val){mDate.tm_sec=val;}

	time_t GetTotalSeconds()const{return mTotalSeconds;}
	uint GetTotalDays()const{return (uint)(GetTotalSeconds()/86400);}

	uint DayOfWeek() const{return (uint)mDate.tm_wday;}
	uint DayOfYear() const{return (uint)mDate.tm_yday;}

	bool IsUTC() const { return mIsUTC; }
	void ConvertToUTC();
	void ConvertToLocal();

public:
	bool operator==(const DateTime& dateTime)const{return mTotalSeconds==dateTime.mTotalSeconds;}
	bool operator>(const DateTime& dateTime)const{return mTotalSeconds>dateTime.mTotalSeconds;}
	bool operator<(const DateTime& dateTime)const{return mTotalSeconds<dateTime.mTotalSeconds;}
	bool operator>=(const DateTime& dateTime)const{return mTotalSeconds>=dateTime.mTotalSeconds;}
	bool operator<=(const DateTime& dateTime)const{return mTotalSeconds<=dateTime.mTotalSeconds;}
	bool operator!=(const DateTime& dateTime)const{return mTotalSeconds!=dateTime.mTotalSeconds;}
public:
	TimeSpan operator-(const DateTime& dateTime)const{return TimeSpan(mTotalSeconds-dateTime.mTotalSeconds);}

	DateTime operator-(const TimeSpan& timeSpan)const{return DateTime(mTotalSeconds-timeSpan.GetTotalSeconds());}
	DateTime operator+(const TimeSpan& timeSpan)const{return DateTime(mTotalSeconds+timeSpan.GetTotalSeconds());}
	DateTime& operator-=(const TimeSpan& timeSpan){mTotalSeconds-=timeSpan.GetTotalSeconds();return *this;}
	DateTime& operator+=(const TimeSpan& timeSpan){mTotalSeconds+=timeSpan.GetTotalSeconds();return *this;}
private:
	void UpdateUTCDateToSeconds();
	void UpdateSecondsToUTCDate();
	void UpdateLocalDateToSeconds();
	void UpdateSecondsToLocalDate();


	void Init(uint year,uint month,uint day,uint hour,uint minute,uint second,bool isUTC=true);		//month begins from 0
	void Init(const StringRef& strDateTime, const StringRef& format,bool isUTC=true);

	time_t mTotalSeconds;//��1970�������,����UTC��
	tm mDate;
	bool mIsUTC;

public:
	const static DateTime StartDate;

};
MEDUSA_END;