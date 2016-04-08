#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/EnumPattern.h"
#include "Core/Pattern/FlagsPattern.h"

MEDUSA_BEGIN;

STRONG_FLAGS_7(MoveableChangedFlags,SizeChanged,PositionChanged,RotationChanged,ScaleChanged,AnchorChanged,MatrixChanged,WorldMatrixChanged);


enum class Direction
{
	Horizontal,
	Vertical
};

STRONG_FLAGS_2(DirectionMask,Horizontal,Vertical);

enum class Alignment
{
	LeftTop,
	MiddleTop,
	RightTop,
	LeftCenter,
	MiddleCenter,
	RightCenter,
	LeftBottom,
	MiddleBottom,
	RightBottom
};

enum class DockPoint
{
	None=-1,
	LeftTop=0,
	MiddleTop,
	RightTop,
	LeftCenter,
	MiddleCenter,
	RightCenter,
	LeftBottom,
	MiddleBottom,
	RightBottom
};



enum class Orientation
{
	Up,
	Down,
	Left,
	Right,

};


//     Describes how content is resized to fill its allocated space.
enum class Stretch
{
	None = 0,
	//     The content is resized to fill the destination dimensions. The aspect ratio
	//     is not preserved.
	Fill = 1,
	//     The content is resized to fit in the destination dimensions while it preserves
	//     its native aspect ratio.
	Uniform = 2,
	//     The content is resized to fill the destination dimensions while it preserves
	//     its native aspect ratio. If the aspect ratio of the destination rectangle
	//     differs from the source, the source content is clipped to fit in the destination
	//     dimensions.
	UniformToFill = 3,

	FillWidth=4,
	FillHeight=5,
};


STRONG_FLAGS_CUSTOM_7(OrientationMask,
					  Up,1<<(uint)Orientation::Up,
					  Down,1<<(uint)Orientation::Down,
					  Left,1<<(uint)Orientation::Left,
					  Right,1<<(uint)Orientation::Right,
					  UpAndDown,((1<<(uint)Orientation::Up)|(1<<(uint)Orientation::Down)),
					  LeftAndRight,((1<<(uint)Orientation::Left)|(1<<(uint)Orientation::Right)),
					  AllButDown,((1<<(uint)Orientation::Up)|(1<<(uint)Orientation::Left)|(1<<(uint)Orientation::Right))
					  );

enum class FlowDirection
{
	LeftToRight = 0,
	RightToLeft = 1,
};


enum class MatrixOrder
{
	Append,
	Prepend
};

//** Determines whether clip space Z ranges from -1 to 1 (OpenGL) or from 0 to 1 (DirectX)
enum class GraphicsSDK
{
	OpenGL,
	DirectX
};

#define MEDUSA_MATRIX_MULTIPLY_DEFAULT_ORDER (MatrixOrder::Append)
#define MEDUSA_MATRIX_TRANSFORM_DEFAULT_ORDER (MatrixOrder::Prepend)

#if MEDUSA_IS_OPENGL==1
#define MEDUSA_IS_RIGHT_HAND	(true)
#define MEDUSA_DEFAULT_GRAPHICS_SDK		(GraphicsSDK::OpenGL)
#else
#define MEDUSA_IS_RIGHT_HAND	(false)
#define MEDUSA_DEFAULT_GRAPHICS_SDK		(GraphicsSDK::DirectX)

#endif

MEDUSA_END;