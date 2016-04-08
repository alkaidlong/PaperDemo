#include "MedusaCorePreCompiled.h"
#include "Core/Geometry/Matrix3.h"
#include "Core/Geometry/Matrix43.h"
#include "Core/Geometry/Matrix4.h"
#include "Core/Geometry/EulerAngle.h"
#include "Core/Geometry/Quaternion.h"
MEDUSA_BEGIN;

EulerAngle::EulerAngle( float heading,float pitch,float bank ):Heading(heading),Pitch(pitch),Bank(bank)
{

}

void EulerAngle::Limit()
{
	//First, transform pitch to -pi to pi
	Pitch=Math::WrapPi(Pitch);
	//transform  pitch to -pi/2 to pi/2
	if (Pitch<-Math::PiHalf)
	{
		Pitch=-Math::Pi-Pitch;
		Heading+=Math::Pi;
		Bank+=Math::Pi;
	}
	else if (Pitch>Math::PiHalf)
	{
		Pitch=Math::Pi-Pitch;
		Heading+=Math::Pi;
		Bank+=Math::Pi;
	}

	//check ������
	if (Math::IsEqual(Math::Abs(Pitch),Math::PiHalf))
	{
		//set all rotation from bank to heading
		Bank=0.f;
		Heading+=Bank;
	}
	else
	{
		Bank=Math::WrapPi(Bank);
	}
	Heading=Math::WrapPi(Heading);
}

EulerAngle EulerAngle::CreateFromQuaternion( const Quaternion& q )
{
	EulerAngle angle;
	float sinp=-2.f*(q.Y*q.Z-q.W*q.X);
	//���������
	if (Math::IsEqual(Math::Abs(sinp),0.999f))
	{
		angle.Pitch=Math::PiHalf*sinp;
		angle.Bank=0.f;
		angle.Heading=Math::Atan2(-q.X*q.Z+q.W*q.Y,0.5f-q.Y*q.Y-q.Z*q.Z);
	}
	else
	{
		angle.Pitch=Math::Asin(sinp);
		angle.Heading=Math::Atan2(q.X*q.Z+q.W*q.Y,0.5f-q.X*q.X-q.Y*q.Y);
		angle.Bank=Math::Atan2(q.X*q.Y+q.W*q.Z,0.5f-q.X*q.X-q.Z*q.Z);
	}

	return angle;
}

EulerAngle EulerAngle::CreateFromMatrix( const Matrix3& m )
{
	/*
	[cosh*cosb+sinh*sinp*sinb,	sinb*cosp,	-sinh*cosb+cosh*sinp*sinb	]
	[-cosh*sinb+sinh*sinp*cosb,	cosb*cosp,	sinb*sinh+cosh*sinp*cosb	]
	[sinh*cosp,					-sinp,		cosh*cosp					]
	*/

	EulerAngle angle;
	float sinp=-m.M32;
	angle.Pitch=Math::Asin(sinp);

	//��������������
	if (Math::IsEqual(angle.Pitch,0.999f))
	{
		angle.Bank=0.f;
		angle.Heading=Math::Atan2(-m.M13,m.M11);
	}
	else
	{
		angle.Heading=Math::Atan2(m.M31,m.M33);
		angle.Bank=Math::Atan2(m.M12,m.M22);
	}

	return angle;
}

const EulerAngle EulerAngle::Zero(0.f,0.f,0.f);


MEDUSA_END;
