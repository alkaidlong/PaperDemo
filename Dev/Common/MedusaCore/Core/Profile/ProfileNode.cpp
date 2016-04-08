#include "MedusaCorePreCompiled.h"
#include "Core/Profile/ProfileNode.h"
#include "Core/Math/MathHeader.h"
#include "Core/String/HeapString.h"
#include "Core/String/StringParser.h"

MEDUSA_BEGIN;



ProfileNode::ProfileNode(const StringRef& name,ProfileNode* parent,size_t count/*=1*/ ,size_t logCount/*=0*/)
	:mName(name),mParent(parent),mTestCount(count),mTimeLogs(logCount)
{
	mTotalCount=0;
	mStartTime=0;
	mTotalTime=0;
	mRecursionCounter=0;
	mMinTime=Math::UIntMaxValue;
	mMaxTime=Math::UIntMinValue;
	mMinLogIndex=0;
	mMaxLogIndex=0;

	if (logCount>0)
	{
		mTimeLogs.ReserveSize(logCount);
	}
}

ProfileNode::~ProfileNode()
{
	SAFE_DELETE_COLLECTION(mChildren);
}

void ProfileNode::Begin()
{
	++mTotalCount;
	if (mRecursionCounter++==0)
	{
		mStartTime=Platform::GetTicks();
	}
}


bool ProfileNode::End()
{
	if ( --mRecursionCounter == 0 && mTotalCount != 0 )
	{
		ProfileTimeType currentTime=Platform::GetTicks();
		ProfileTimeType elapsedTime=currentTime-mStartTime;
        if (elapsedTime<mSelfCost)
        {
            elapsedTime=0;
        }
        else
        {
            elapsedTime-=mSelfCost;
		}
		mTotalTime+=elapsedTime;
		if (elapsedTime<mMinTime)
		{
			mMinTime=elapsedTime;
			mMinLogIndex=mTimeLogs.GetCount();
		}
		if (elapsedTime>mMaxTime)
		{
			mMaxTime=elapsedTime;
			mMaxLogIndex=mTimeLogs.GetCount();
		}

		if (!mTimeLogs.IsFull())
		{
			mTimeLogs.Add(elapsedTime);
		}
	}
	return ( mRecursionCounter == 0 );
}

void ProfileNode::Reset()
{
	mTotalCount=0;
	mStartTime=0;
	mTotalTime=0;
	mMinTime=Math::UIntMaxValue;
	mMaxTime=Math::UIntMinValue;
	mRecursionCounter=0;
	mMinLogIndex=0;
	mMaxLogIndex=0;
	mTimeLogs.Clear();

	FOR_EACH_COLLECTION(i,mChildren)
	{
		ProfileNode* node=*i;
		node->Reset();
	}
}


void ProfileNode::Stop()
{
	FOR_EACH_COLLECTION(i,mChildren)
	{
		ProfileNode* node=*i;
		node->End();
	}
	End();
}

ProfileNode* ProfileNode::FindOrCreateChildNode(const  StringRef& name ,size_t count/*=1*/,size_t logCount/*=1*/)
{
	size_t size=mChildren.GetCount();
	FOR_EACH_SIZE(i,size)
	{
		ProfileNode* node=mChildren[i];
		if (node->GetName().IsRefEqualsTo(name))
		{
			return node;
		}
	}

	ProfileNode* newNode=new ProfileNode(name,this,count,logCount);
	mChildren.Append(newNode);
	return newNode;
}

void ProfileNode::InitFreq()
{
	mTimeFreq=Platform::GetTimeFreq();

	mSelfCost=(int64)(mTimeFreq*0.001f/1000.f);
}

void ProfileNode::PrintResult(const StringRef& totalPrefix,const StringRef& perPrefix) const
{
	double dt=(double)mTotalTime/mTimeFreq*1000.f/mTestCount;	//ms
	double minTime=(double)mMinTime/mTimeFreq*1000.f/mTestCount;	//ms
	double maxTime=(double)mMaxTime/mTimeFreq*1000.f/mTestCount;	//ms

	HeapString str=totalPrefix;

	if (!mName.IsNull())
	{
		if (mTestCount!=1)
		{
			str.AppendFormat("%s/%d\t",mName.Buffer(),mTestCount);
		}
		else
		{
			str.AppendFormat("%s\t",mName.Buffer());
		}

	}

	if (dt!=0)
	{
		if (mTotalCount>1)
		{
			str.AppendFormat("%f / %d = %f %f->%f   ",dt,mTotalCount,dt/mTotalCount,minTime,maxTime);
		}
		else
		{
			str.AppendFormat("%f  ",dt);
		}
	}

	if (mTotalCount>0&&dt!=0)
	{
	}

	if (!mTimeLogs.IsEmpty())
	{
		size_t logCount=mTimeLogs.GetCount();
		str.AppendFormat("%d:[",logCount);

		FOR_EACH_SIZE(i,logCount)
		{
			double logTime=(double)mTimeLogs[i]/mTimeFreq*1000.f/mTestCount;	//ms
			if (i==mMinLogIndex)
			{
				str+='#';
				str+=StringParser::ToString(logTime);
				str+='#';
			}
			else if (i==mMaxLogIndex)
			{
				str+='#';
				str+=StringParser::ToString(logTime);
				str+='#';
			}
			else
			{
				str+=StringParser::ToString(logTime);
			}
			if (i!=logCount-1)
			{
				str+=' ';
			}
		}
		str+="]";
	}



	str+='\n';
	MEDUSA_TRACE(str.Buffer());

	HeapString totalPrefixCopy=totalPrefix;
	totalPrefixCopy+=perPrefix;

	FOR_EACH_COLLECTION(i,mChildren)
	{
		const ProfileNode* node=*i;
		node->PrintResult(totalPrefixCopy,perPrefix);
	}
}

ProfileTimeType ProfileNode::mSelfCost;		//it depends on platform
ProfileTimeType ProfileNode::mTimeFreq;

MEDUSA_IMPLEMENT_STATIC_CONSTRUCTOR(ProfileNode,InitFreq);

MEDUSA_END;