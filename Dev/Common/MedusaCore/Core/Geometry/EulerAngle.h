#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Math/MathHeader.h"
#include "Core/Utility/Utility.h"
#include "Core/Geometry/Rotation3.h"

MEDUSA_BEGIN;

/*
采用 heading-pitch-bank 顺序。分别对应y,x,z的选择
为了保证任意方位都只有独一无二的表示，必须限制角度的范围.
-π<heading<π
-π<bank<π
-π/2<pitch<π/2

但角度为±90°的第二次旋转使得第一次和第三次旋转的旋转轴相同，称作万向锁。为了消除，则规定如果pitch为±90°，则bank为0

另角度之间的差总是要折到-π和π之间
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
	// 名称:    	Limit
	// 返回:   	void	
	// 功能:		变化到限制集
	// 描述:		
	// 例子:		
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
