#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Math/MathHeader.h"
#include "Core/Utility/Utility.h"
#include "Core/Geometry/Rotation3.h"

MEDUSA_BEGIN;

/*
���� heading-pitch-bank ˳�򡣷ֱ��Ӧy,x,z��ѡ��
Ϊ�˱�֤���ⷽλ��ֻ�ж�һ�޶��ı�ʾ���������ƽǶȵķ�Χ.
-��<heading<��
-��<bank<��
-��/2<pitch<��/2

���Ƕ�Ϊ��90��ĵڶ�����תʹ�õ�һ�κ͵�������ת����ת����ͬ��������������Ϊ����������涨���pitchΪ��90�㣬��bankΪ0

��Ƕ�֮��Ĳ�����Ҫ�۵�-�кͦ�֮��
*/

class Quaternion;
class Matrix3;


class EulerAngle
{
public:
	EulerAngle(void){}
	EulerAngle(float heading,float pitch,float bank);

	EulerAngle(const float* items):Heading(*items),Pitch(*(items+1)),Bank(*(items+2)){}
	EulerAngle(const EulerAngle& angle):Heading((float)angle.Heading),Pitch((float)angle.Pitch),Bank((float)angle.Bank){}

	EulerAngle& operator=(const EulerAngle& angle){Heading=(float)angle.Heading;Pitch=(float)angle.Pitch;Bank=(float)angle.Bank;return *this;}
	EulerAngle& operator=(float val){Heading=(float)val;Pitch=(float)val;Bank=(float)val;return *this;}

	
	bool operator==(const EulerAngle& angle)const{return Math::IsEqual(Heading,angle.Heading)&&Math::IsEqual(Pitch,angle.Pitch)&&Math::IsEqual(Bank,angle.Bank);}
	bool operator!=(const EulerAngle& angle)const{return !operator==(angle);}
	bool operator>(const EulerAngle& angle)const{return Heading>angle.Heading&&Pitch>angle.Pitch&&Bank>angle.Bank;}
	bool operator<(const EulerAngle& angle)const{return Heading<angle.Heading&&Pitch<angle.Pitch&&Bank<angle.Bank;}
	bool operator>=(const EulerAngle& angle)const{return Heading>=angle.Heading&&Pitch>=angle.Pitch&&Bank>=angle.Bank;}
	bool operator<=(const EulerAngle& angle)const{return Heading<=angle.Heading&&Pitch<=angle.Pitch&&Bank<=angle.Bank;}

	
	EulerAngle operator+(const EulerAngle& angle)const{return EulerAngle(Heading+angle.Heading,Pitch+angle.Pitch,Bank+angle.Bank);}
	EulerAngle operator-(const EulerAngle& angle)const{return EulerAngle(Heading-angle.Heading,Pitch-angle.Pitch,Bank-angle.Bank);}
	EulerAngle& operator+=(const EulerAngle& angle){Heading+=angle.Heading;Pitch+=angle.Pitch;Bank+=angle.Bank;return *this;}
	EulerAngle& operator-=(const EulerAngle& angle){Heading-=angle.Heading;Pitch-=angle.Pitch;Bank-=angle.Bank;return *this;}
	EulerAngle operator-()const{return EulerAngle(-Heading,-Pitch,-Bank);}

	
	float operator*(const EulerAngle& angle)const{return Heading*angle.Heading+Pitch*angle.Pitch+Bank*angle.Bank;}

	
	EulerAngle operator*(float delta)const{return EulerAngle(Heading*delta,Pitch*delta,Bank*delta);}
	EulerAngle operator/(float delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return EulerAngle(Heading/delta,Pitch/delta,Bank/delta);}
	EulerAngle& operator*=(float delta){Heading*=delta;Pitch*=delta;Bank*=delta;return *this;}
	EulerAngle& operator/=(float delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");Heading/=delta;Pitch/=delta;Bank/=delta;return *this;}
	friend  EulerAngle operator*(float delta,const EulerAngle& angle){return EulerAngle(delta*angle.Heading,delta*angle.Pitch,delta*angle.Bank);}
	friend  EulerAngle operator/(float delta,const EulerAngle& angle){return EulerAngle(delta/angle.Heading,delta/angle.Pitch,delta/angle.Bank);}

	
	EulerAngle operator+(float delta)const{return EulerAngle(Heading+delta,Pitch+delta,Bank+delta);}
	EulerAngle operator-(float delta)const{return EulerAngle(Heading-delta,Pitch-delta,Bank-delta);}
	
	EulerAngle& operator+=(float delta){Heading+=delta;Pitch+=delta;Bank+=delta;return *this;}
	EulerAngle& operator-=(float delta){Heading-=delta;Pitch-=delta;Bank-=delta;return *this;}

	EulerAngle& operator++(){++Heading;++Pitch;++Bank;return *this;}
	EulerAngle& operator--(){--Heading;--Pitch;--Bank;return *this;}

	EulerAngle operator++(int){EulerAngle orign=*this;++Heading;++Pitch;++Bank;return orign;}
	EulerAngle operator--(int){EulerAngle orign=*this;--Heading;--Pitch;--Bank;return orign;}
	
	bool operator==(float val)const{return Math::IsEqual(Heading,val)&&Math::IsEqual(Pitch,val)&&Math::IsEqual(Bank,val);}
	bool operator!=(float val)const{return !operator==(val);}
	bool operator>(float val)const{return Heading>val&&Pitch>val&&Bank>val;}
	bool operator<(float val)const{return Heading<val&&Pitch<val&&Bank<val;}
	bool operator>=(float val)const{return Heading>=val&&Pitch>=val&&Bank>=val;}
	bool operator<=(float val)const{return Heading<=val&&Pitch<=val&&Bank<=val;}

	friend  bool operator==(float val,const EulerAngle& angle){return angle==val;}
	friend  bool operator!=(float val,const EulerAngle& angle){return angle!=val;}
	friend  bool operator>(float val,const EulerAngle& angle){return angle<=val;}
	friend  bool operator<(float val,const EulerAngle& angle){return angle>=val;}
	friend  bool operator>=(float val,const EulerAngle& angle){return angle<val;}
	friend  bool operator<=(float val,const EulerAngle& angle){return angle>val;}
public:
	//************************************
	// ����:    	Limit
	// ����:   	void	
	// ����:		�仯�����Ƽ�
	// ����:		
	// ����:		
	//************************************
	void Limit();

	Rotation3F ToRotation()const{return Rotation3F(Pitch,Heading,Bank);}
	static EulerAngle CreateFromRotation(const Rotation3F& r){return EulerAngle(r.Y,r.X,r.Z);}

	static EulerAngle CreateFromQuaternion(const Quaternion& q);
	static EulerAngle CreateFromMatrix(const Matrix3& m);


public:
	union
	{
		float Angles[3];
		struct
		{
			float Heading;
			float Pitch;
			float Bank;
		};

		
	};
	const static EulerAngle Zero;
	
};
MEDUSA_END;
