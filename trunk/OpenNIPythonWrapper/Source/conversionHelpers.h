/*****************************************************************************
*                                                                            *
*  OpenNI Python Wrapper (ONIPY)                                             *
*  Copyright (C) 2011 Gabriele Nataneli (gamix).                             *
*                                                                            *
*                                                                            *
*  This library is free software: you can redistribute it and/or modify      *
*  it under the terms of the GNU Lesser General Public License as published  *
*  by the Free Software Foundation, either version 3 of the License, or      *
*  (at your option) any later version.                                       *
*                                                                            *
*  OpenNI Python Wrapper is distributed in the hope that it will be useful,  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              *
*  GNU Lesser General Public License for more details.                       *
*                                                                            *
*  You should have received a copy of the GNU Lesser General Public License  *
*  along with OpenNI Python Wrapper. If not,                                 *
* see <http://www.gnu.org/licenses/>.                                        *
*                                                                            *
*****************************************************************************/


#ifndef CONVERSION_HELPERS_H
#define CONVERSION_HELPERS_H

#include "OpenNIWrapperTypes.h"

void convert( 
	BP::tuple& targetTuple, 
   XnRGB24Pixel const* sourceMap,
   XnUInt32 sourceXResolution, 
   XnUInt32 sourceYResolution );

void convert( 
	BP::tuple& targetTuple, 
	XnDepthPixel const* sourceMap,
	XnUInt32 sourceXResolution, 
	XnUInt32 sourceYResolution );

void convertToGrayscale8Raw( 
	std::string& targetMapRaw, 
	XnDepthPixel const* sourceMap,
	XnUInt32 sourceXResolution, 
	XnUInt32 sourceYResolution );

void convertToBGR24Raw( 
	 std::string& targetMapRaw, 
	XnRGB24Pixel const* sourceMap,
	XnUInt32 sourceXResolution, 
	XnUInt32 sourceYResolution );

#endif	// CONVERSION_HELPERS_H