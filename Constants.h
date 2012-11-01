/*
 * Constants.h
 *
 *  Created on: Nov 1, 2012
 *      Author: Catur Wirawan Wijiutomo
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_



//---------------------------------
//----  temukan tipe sistem  ------
//---------------------------------

#if defined( __WIN32__ ) || defined( _WIN32 )
	#define TARGET_WIN32
#elif defined( __APPLE_CC__)
	#define TARGET_OSX
#elif defined (ANDROID)
	#define TARGET_ANDROID
	#define TARGET_OPENGLES
#else
	#define TARGET_LINUX
#endif
//----------------------


#endif /* CONSTANTS_H_ */
