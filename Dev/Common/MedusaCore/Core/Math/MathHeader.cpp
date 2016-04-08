#include "MedusaCorePreCompiled.h"
#include "Core/Math/MathHeader.h"

MEDUSA_BEGIN;

namespace Math
{
	namespace Tween
	{
		FORCE_INLINE float QuadraticEaseIn(float time)
		{
			return time*time;
		}

		FORCE_INLINE float QuadraticEaseOut(float time)
		{
			return -1 * time * (time - 2);
		}

		FORCE_INLINE float QuadraticEaseInOut(float time)
		{
			time = time*2;
			if (time < 1)
				return 0.5f * time * time;
			--time;
			return -0.5f * (time * (time - 2) - 1);
		}

		FORCE_INLINE float CubicEaseIn(float time)
		{
			return time * time * time;
		}

		FORCE_INLINE float CubicEaseOut(float time)
		{
			time -= 1;
			return (time * time * time + 1);
		}

		FORCE_INLINE float CubicEaseInOut(float time)
		{
			time = time*2;
			if (time < 1)
				return 0.5f * time * time * time;
			time -= 2;
			return 0.5f * (time * time * time + 2);
		}

		FORCE_INLINE float QuarticEaseIn(float time)
		{
			return time * time * time * time;
		}

		FORCE_INLINE float QuarticEaseOut(float time)
		{
			time -= 1;
			return -(time * time * time * time - 1);
		}

		FORCE_INLINE float QuarticEaseInOut(float time)
		{
			time = time*2;
			if (time < 1)
				return 0.5f * time * time * time * time;
			time -= 2;
			return -0.5f * (time * time * time * time - 2);
		}

		FORCE_INLINE float QuinticEaseIn(float time)
		{
			return time * time * time * time * time;
		}

		FORCE_INLINE float QuinticEaseOut(float time)
		{
			time -=1;
			return (time * time * time * time * time + 1);
		}

		FORCE_INLINE float QuinticEaseInOut(float time)
		{
			time = time*2;
			if (time < 1)
				return 0.5f * time * time * time * time * time;
			time -= 2;
			return 0.5f * (time * time * time * time * time + 2);
		}

		FORCE_INLINE float SinusoidalEaseIn(float time)
		{
			return -1 * cosf(time * (float)PiHalf) + 1;
		}

		FORCE_INLINE float SinusoidalEaseOut(float time)
		{
			return sinf(time * (float)PiHalf);
		}

		FORCE_INLINE float SinusoidalEaseInOut(float time)
		{
			return -0.5f * (cosf((float)Pi * time) - 1);
		}

		FORCE_INLINE float ExponentialEaseIn(float time)
		{
			return time == 0 ? 0 : powf(2, 10 * (time/1 - 1)) - 1 * 0.001f;
		}

		FORCE_INLINE float ExponentialEaseOut(float time)
		{
			return time == 1 ? 1 : (-powf(2, -10 * time / 1) + 1);
		}

		FORCE_INLINE float ExponentialEaseInOut(float time)
		{
			time /= 0.5f;
			if (time < 1)
			{
				time = 0.5f * powf(2, 10 * (time - 1));
			}
			else
			{
				time = 0.5f * (-powf(2, -10 * (time - 1)) + 2);
			}

			return time;
		}

		FORCE_INLINE float CircularEaseIn(float time)
		{
			return -1 * (sqrt(1 - time * time) - 1);
		}

		FORCE_INLINE float CircularEaseOut(float time)
		{
			time = time - 1;
			return sqrt(1 - time * time);
		}

		FORCE_INLINE float CircularEaseInOut(float time)
		{
			time = time * 2;
			if (time < 1)
				return -0.5f * (sqrt(1 - time * time) - 1);
			time -= 2;
			return 0.5f * (sqrt(1 - time * time) + 1);
		}

		FORCE_INLINE float ElasticEaseIn(float time, float period)
		{
			float newT = 0;
			if (time == 0 || time == 1)
			{
				newT = time;
			}
			else
			{
				float s = period / 4;
				time = time - 1;
				newT = -powf(2, 10 * time) * sinf((time - s) * Pi2 / period);
			}

			return newT;
		}

		FORCE_INLINE float ElasticEaseOut(float time, float period)
		{
			float newT = 0;
			if (time == 0 || time == 1)
			{
				newT = time;
			}
			else
			{
				float s = period / 4;
				newT = powf(2, -10 * time) * sinf((time - s) * Pi2 / period) + 1;
			}

			return newT;
		}

		FORCE_INLINE float ElasticEaseInOut(float time, float period)
		{
			float newT = 0;
			if (time == 0 || time == 1)
			{
				newT = time;
			}
			else
			{
				time = time * 2;
				if (! period)
				{
					period = 0.3f * 1.5f;
				}

				float s = period / 4;

				time = time - 1;
				if (time < 0)
				{
					newT = -0.5f * powf(2, 10 * time) * sinf((time -s) * Pi2 / period);
				}
				else
				{
					newT = powf(2, -10 * time) * sinf((time - s) * Pi2 / period) * 0.5f + 1;
				}
			}
			return newT;
		}

		FORCE_INLINE float BackEaseIn(float time)
		{
			const float overshoot = 1.70158f;
			return time * time * ((overshoot + 1) * time - overshoot);
		}

		FORCE_INLINE float BackEaseOut(float time)
		{
			const float overshoot = 1.70158f;
			time = time - 1;
			return time * time * ((overshoot + 1) * time + overshoot) + 1;
		}

		FORCE_INLINE float BackEaseInOut(float time)
		{
			const float overshoot = 1.70158f * 1.525f;
			time = time * 2;
			if (time < 1)
			{
				return (time * time * ((overshoot + 1) * time - overshoot)) / 2;
			}
			else
			{
				time = time - 2;
				return (time * time * ((overshoot + 1) * time + overshoot)) / 2 + 1;
			}
		}

		FORCE_INLINE float BounceTime(float time)
		{
			if (time < 1 / 2.75)
			{
				return 7.5625f * time * time;
			}
			else if (time < 2 / 2.75)
			{
				time -= 1.5f / 2.75f;
				return 7.5625f * time * time + 0.75f;
			}
			else if(time < 2.5 / 2.75)
			{
				time -= 2.25f / 2.75f;
				return 7.5625f * time * time + 0.9375f;
			}

			time -= 2.625f / 2.75f;
			return 7.5625f * time * time + 0.984375f;
		}

		FORCE_INLINE float BounceEaseIn(float time)
		{
			return 1 - BounceTime(1 - time);
		}

		FORCE_INLINE float BounceEaseOut(float time)
		{
			return BounceTime(time);
		}

		FORCE_INLINE float BounceEaseInOut(float time)
		{
			float newT = 0;
			if (time < 0.5f)
			{
				time = time * 2;
				newT = (1 - BounceTime(1 - time)) * 0.5f;
			}
			else
			{
				newT = BounceTime(time * 2 - 1) * 0.5f + 0.5f;
			}

			return newT;
		}

		FORCE_INLINE float RateEaseIn(float time, float rate)
		{
			return powf(time, rate);
		}

		FORCE_INLINE float RateEaseOut(float time, float rate)
		{
			return powf(time, 1 / rate);
		}

		FORCE_INLINE float RateEaseInOut(float time, float rate)
		{
			time *= 2;
			if (time < 1)
			{
				return 0.5f * powf(time, rate);
			}
			else
			{
				return (1.0f - 0.5f * powf(2 - time, rate));
			}
		}

		FORCE_INLINE float Bezier( float time,float a, float b, float c, float d)
		{
			return (powf(1-time,3) * a + 3*time*(powf(1-time,2))*b + 3*powf(time,2)*(1-time)*c + powf(time,3)*d );
		}

		FORCE_INLINE float TweenTo(float time, TweenType type, const float* args)
		{
			switch (type)
			{
			case TweenType::Linear:return Linear(time);
			case TweenType::QuadraticEaseIn:return QuadraticEaseIn(time);
			case TweenType::QuadraticEaseOut:return QuadraticEaseOut(time);
			case TweenType::QuadraticEaseInOut:return QuadraticEaseInOut(time);
			case TweenType::CubicEaseIn:return CubicEaseIn(time);
			case TweenType::CubicEaseOut:return CubicEaseOut(time);
			case TweenType::CubicEaseInOut:return CubicEaseInOut(time);
			case TweenType::QuarticEaseIn:return QuarticEaseIn(time);
			case TweenType::QuarticEaseOut:return QuarticEaseOut(time);
			case TweenType::QuarticEaseInOut:return QuarticEaseInOut(time);
			case TweenType::QuinticEaseIn:return QuinticEaseIn(time);
			case TweenType::QuinticEaseOut:return QuinticEaseOut(time);
			case TweenType::QuinticEaseInOut:return QuinticEaseInOut(time);
			case TweenType::SinusoidalEaseIn:return SinusoidalEaseIn(time);
			case TweenType::SinusoidalEaseOut:return SinusoidalEaseOut(time);
			case TweenType::SinusoidalEaseInOut:return SinusoidalEaseInOut(time);
			case TweenType::ExponentialEaseIn:return ExponentialEaseIn(time);
			case TweenType::ExponentialEaseOut:return ExponentialEaseOut(time);
			case TweenType::ExponentialEaseInOut:return ExponentialEaseInOut(time);
			case TweenType::CircularEaseIn:return CircularEaseIn(time);
			case TweenType::CircularEaseOut:return CircularEaseOut(time);
			case TweenType::CircularEaseInOut:return CircularEaseInOut(time);
			case TweenType::ElasticEaseIn:return ElasticEaseIn(time,args[0]);
			case TweenType::ElasticEaseOut:return ElasticEaseOut(time,args[0]);
			case TweenType::ElasticEaseInOut:return ElasticEaseInOut(time,args[0]);
			case TweenType::BackEaseIn:return BackEaseIn(time);
			case TweenType::BackEaseOut:return BackEaseOut(time);
			case TweenType::BackEaseInOut:return BackEaseInOut(time);
			case TweenType::BounceEaseIn:return BounceEaseIn(time);
			case TweenType::BounceEaseOut:return BounceEaseOut(time);
			case TweenType::BounceEaseInOut:return BounceEaseInOut(time);
			case TweenType::RateEaseIn:return RateEaseIn(time,args[0]);
			case TweenType::RateEaseOut:return RateEaseOut(time,args[0]);
			case TweenType::RateEaseInOut:return RateEaseInOut(time,args[0]);
			case TweenType::Bezier:return Bezier(time,args[0],args[1],args[2],args[3]);

			default:
				break;
			}
            return time;
		}

		
	}
}


MEDUSA_END;
