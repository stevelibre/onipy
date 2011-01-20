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


#include "conversionHelpers.h"


void convert( 
	BP::tuple& targetTuple, 
	XnRGB24Pixel const* sourceMap, 
	XnUInt32 sourceXResolution, 
	XnUInt32 sourceYResolution )
{

	BP::list proxyMapData;

	XnUInt32 rowIndex;
	XnUInt32 columnIndex;
	unsigned int imageIndex;
	XnUInt8 currentPixelRed;
	XnUInt8 currentPixelGreen;
	XnUInt8 currentPixelBlue;
	BP::tuple currentPixelTuple;

	imageIndex = 0;

	for( rowIndex = 0; rowIndex < sourceXResolution; ++rowIndex )
	{

		for( columnIndex = 0; columnIndex < sourceYResolution; ++columnIndex )
		{

			currentPixelRed = sourceMap[ imageIndex ].nRed;
			currentPixelGreen = sourceMap[ imageIndex ].nGreen;
			currentPixelBlue = sourceMap[ imageIndex ].nBlue;

			currentPixelTuple = BP::make_tuple(
				currentPixelRed,
				currentPixelGreen,
				currentPixelBlue );

			proxyMapData.append( currentPixelTuple );

			++imageIndex;

		}	// for columns

	}	// for rows

	targetTuple = BP::tuple( proxyMapData );

}	// convert (XnRGB24Pixel)

void convert( 
	 BP::tuple& targetTuple, 
	 XnDepthPixel const* sourceMap, 
	 XnUInt32 sourceXResolution, 
	 XnUInt32 sourceYResolution )
{

	BP::list proxyMapData;

	XnUInt32 rowIndex;
	XnUInt32 columnIndex;
	unsigned int imageIndex;
	XnDepthPixel currentPixelDepth;

	imageIndex = 0;

	for( rowIndex = 0; rowIndex < sourceXResolution; ++rowIndex )
	{

		for( columnIndex = 0; columnIndex < sourceYResolution; ++columnIndex )
		{

			currentPixelDepth = sourceMap[ imageIndex ];

			proxyMapData.append( currentPixelDepth );

			++imageIndex;

		}	// for columns

	}	// for rows

	targetTuple = BP::tuple( proxyMapData );

}	// convert (XnDepthPixel)

void convertToGrayscale8Raw( 
	std::string& targetMapRaw, 
	XnDepthPixel const* sourceMap, 
	XnUInt32 sourceXResolution, 
	XnUInt32 sourceYResolution )
{

	XnUInt32 rowIndex;
	XnUInt32 columnIndex;
	unsigned int imageIndex;
	XnDepthPixel currentPixelDepth;
	float currentPixelDepthNormalized;

	imageIndex = 0;
	targetMapRaw.resize( sourceXResolution * sourceYResolution );

	for( rowIndex = 0; rowIndex < sourceXResolution; ++rowIndex )
	{

		for( columnIndex = 0; columnIndex < sourceYResolution; ++columnIndex )
		{

			currentPixelDepth = sourceMap[ imageIndex ];
			currentPixelDepthNormalized = (float)currentPixelDepth / 2048.0f;

			targetMapRaw[ imageIndex ] = 
				(char)( currentPixelDepthNormalized * 255.0f );

			++imageIndex;

		}	// for columns

	}	// for rows

}	// convertToGrayscale8Raw

void convertToBGR24Raw( 
	std::string& targetMapRaw, 
	XnRGB24Pixel const* sourceMap, 
	XnUInt32 sourceXResolution, 
	XnUInt32 sourceYResolution )
{

	XnUInt32 rowIndex;
	XnUInt32 columnIndex;
	unsigned int imageIndex;
	unsigned int targetIndex;
	XnUInt8 currentPixelRed;
	XnUInt8 currentPixelGreen;
	XnUInt8 currentPixelBlue;

	imageIndex = 0;
	targetIndex = 0;
	targetMapRaw.resize( sourceXResolution * sourceYResolution * 3 );

	for( rowIndex = 0; rowIndex < sourceXResolution; ++rowIndex )
	{

		for( columnIndex = 0; columnIndex < sourceYResolution; ++columnIndex )
		{

			currentPixelRed = sourceMap[ imageIndex ].nRed;
			currentPixelGreen = sourceMap[ imageIndex ].nGreen;
			currentPixelBlue = sourceMap[ imageIndex ].nBlue;


			targetMapRaw[ targetIndex + 0 ] = currentPixelBlue;
			targetMapRaw[ targetIndex + 1 ] = currentPixelGreen;
			targetMapRaw[ targetIndex + 2 ] = currentPixelRed;

			++imageIndex;
			targetIndex += 3;

		}	// for columns

	}	// for rows

}	// convertToBGR24Raw
