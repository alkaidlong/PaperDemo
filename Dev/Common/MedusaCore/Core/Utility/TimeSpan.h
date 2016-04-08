#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class TimeSpan
{
public:
	TimeSpan(time_t seconds=0):mTotalSeconds(seconds){}
	TimeSpan(size_t day,size_t hour,size_t minute,size_t second)
		:mTotalSeconds(second + 60* (minute + 60* (hour + 24 * day))){}

	TimeSpan(const TimeSpan& timeSpan):mTotalSeconds(timeSpan.mTotalSeconds){}
	TimeSpan& operator=(const TimeSpan& timeSpan){mTotalSeconds=timeSpan.mTotalSeconds;return *this;}
public:
	void AddSeconds(int seconds){mTotalSeconds +=seconds;}
	void AddMinutes(int minutes){AddSeconds(minutes *60);}
	void AddHours(int hours){AddMinutes(hours*60);}
	void AddDays(int days){AddHours(days*24);}
public:
	static int Compare(const TimeSpan& value1,const TimeSpan& value2){return value1.CompareTo(value2);}
	int CompareTo(const TimeSpan& val) const{return (int)(mTotalSeconds - val.mTotalSeconds);}
	bool Equals(const TimeSpan& timeSpan) const{return mTotalSeconds == timeSpan.mTotalSeconds;}
	static bool Equals(const TimeSpan& value1,const TimeSpan& value2){return value1.mTotalSeconds == value2.mTotalSeconds;}

	HeapString ToString() const;
	HeapString ToShortString() const;

	HeapString ToTotalSecondsString() const;

public:        
	size_t GetDays() const{return (size_t)GetTotalDays();}
	size_t GetHours() const{return (size_t)(GetTotalHours()-GetDays()*24);}
	size_t GetMinutes() const{return (size_t)(GetTotalMinutes()-GetTotalHours()*60);}
	size_t GetSeconds() const{return (size_t)(GetTotalSeconds()-GetTotalMinutes()*60);}

	time_t GetTotalDays() const{return mTotalSeconds/86400;}
	time_t GetTotalHours() const{return mTotalSeconds/3600;}
	time_t GetTotalMinutes() const{return mTotalSeconds/60;}
	time_t GetTotalSeconds()const{return mTotalSeconds;}
public:
	bool operator==(const TimeSpan& timeSpan)const{return mTotalSeconds==timeSpan.mTotalSeconds;}
	bool operator>(const TimeSpan& timeSpan)const{return mTotalSeconds>timeSpan.mTotalSeconds;}
	bool operator<(const TimeSpan& timeSpan)const{return mTotalSeconds<timeSpan.mTotalSeconds;}
	bool operator>=(const TimeSpan& timeSpan)const{return mTotalSeconds>=timeSpan.mTotalSeconds;}
	bool operator<=(const TimeSpan& timeSpan)const{return mTotalSeconds<=timeSpan.mTotalSeconds;}
	bool operator!=(const TimeSpan& timeSpan)const{return mTotalSeconds!=timeSpan.mTotalSeconds;}

public:
	TimeSpan operator-(const TimeSpan& timeSpan)const{return TimeSpan(mTotalSeconds-timeSpan.mTotalSeconds);}
	TimeSpan operator+(const TimeSpan& timeSpan)const{return TimeSpan(mTotalSeconds+timeSpan.mTotalSeconds);}

	TimeSpan& operator-=(const TimeSpan& timeSpan){mTotalSeconds-=timeSpan.mTotalSeconds;return *this;}
	TimeSpan& operator+=(const TimeSpan& timeSpan){mTotalSeconds+=timeSpan.mTotalSeconds;return *this;}
private:
	time_t mTotalSeconds;	
};
MEDUSA_END;