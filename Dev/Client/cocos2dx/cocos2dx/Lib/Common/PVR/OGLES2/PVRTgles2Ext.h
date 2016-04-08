/*!****************************************************************************

 @file         OGLES2/PVRTgles2Ext.h
 @ingroup      API_OGLES2
 @copyright    Copyright (c) Imagination Technologies Limited.
 @brief        OpenGL ES 2.0 extensions

******************************************************************************/

#ifndef _PVRTGLES2EXT_H_
#define _PVRTGLES2EXT_H_


/*!
 @addtogroup   API_OGLES2
 @{
*/


/****************************************************************************
** Build options
****************************************************************************/


/**************************************************************************
****************************** GL EXTENSIONS ******************************
**************************************************************************/

/*!************************************************************************
 @class CPVRTgles2Ext
 @brief A class for initialising and managing OGLES2 extensions
**************************************************************************/
class CPVRTgles2Ext
{

public:
	static bool IsGLExtensionSupported(const char * const extension);
};

/*! @} */

#endif /* _PVRTGLES2EXT_H_ */

/*****************************************************************************
 End of file (PVRTgles2Ext.h)
*****************************************************************************/
