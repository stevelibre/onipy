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


#include "OpenNIImageGeneratorWrapper.h"
#include "conversionHelpers.h"

#include <PythonOutputStream.h>

OpenNIImageGeneratorWrapper::OpenNIImageGeneratorWrapper()
{

#ifdef _DEBUG
	PyCout << "Creating ImageGenerator" << std::endl;
#endif

}	// OpenNIImageGeneratorWrapper::OpenNIImageGeneratorWrapper

void OpenNIImageGeneratorWrapper::GetMetaData( 
	OpenNIImageMetaDataWrapper& metaData ) const
{

	// FIXME: it does not seem to be a good idea to expose the meta data
	// directly to Python
	assert( false );

}	// OpenNIImageGeneratorWrapper::GetMetaData

XnUInt32 OpenNIImageGeneratorWrapper::XRes() const
{

	xn::ImageMetaData proxyImageMetaData;
	xn::ImageGenerator::GetMetaData( proxyImageMetaData );

	return proxyImageMetaData.XRes();

}	// OpenNIImageGeneratorWrapper::XRes

XnUInt32 OpenNIImageGeneratorWrapper::YRes() const
{

	xn::ImageMetaData proxyImageMetaData;
	xn::ImageGenerator::GetMetaData( proxyImageMetaData );

	return proxyImageMetaData.YRes();

}	// OpenNIImageGeneratorWrapper::YRes

BP::tuple OpenNIImageGeneratorWrapper::Res() const
{

	return BP::make_tuple( XRes(), YRes() );

}	// OpenNIImageGeneratorWrapper::Res

BP::tuple OpenNIImageGeneratorWrapper::GetRGB24ImageMapTuple() const
{

	// PRECONDITION: the generator is valid
	assert( IsValid() );

#ifdef _DEBUG
	if( IsDataNew() == false )
		PyCout << "WARNING: data is out of sync!" << std::endl;
#endif

	XnRGB24Pixel const* imageMap = xn::ImageGenerator::GetRGB24ImageMap();

	BP::tuple mapTuple;
	convert( mapTuple, imageMap, XRes(), YRes() );

	return mapTuple;

}	// OpenNIImageGeneratorWrapper::GetRGB24ImageMapTuple

std::string OpenNIImageGeneratorWrapper::GetRGB24ImageMapRaw()
{

	_GetRGB24ImageMapRaw();

	return _rawData;

}	// OpenNIImageGeneratorWrapper::GetRGB24ImageMapRaw

std::string OpenNIImageGeneratorWrapper::GetSyncedRGB24ImageMapRaw()
{
	
	WaitAndUpdateData();

	_GetRGB24ImageMapRaw();

	return _rawData;

}	// OpenNIImageGeneratorWrapper::GetSyncedRGB24ImageMapRaw

std::string OpenNIImageGeneratorWrapper::GetBGR24ImageMapRaw()
{

	_GetBGR24ImageMapRaw();

	return _rawData;

}

std::string OpenNIImageGeneratorWrapper::GetSyncedBGR24ImageMapRaw()
{

	WaitAndUpdateData();

	_GetBGR24ImageMapRaw();

	return _rawData;

}

void OpenNIImageGeneratorWrapper::_GetRGB24ImageMapRaw()
{

	// PRECONDITION: the generator is valid
	assert( IsValid() );

#ifdef _DEBUG
	if( IsDataNew() == false )
		PyCout << "WARNING: data is out of sync!" << std::endl;
#endif

	XnRGB24Pixel const* imageMap = xn::ImageGenerator::GetRGB24ImageMap();
	_rawData.assign( (const char*)imageMap, GetDataSize() );

}	// OpenNIImageGeneratorWrapper::_GetRGB24ImageMapRaw

void OpenNIImageGeneratorWrapper::_GetBGR24ImageMapRaw()
{

	// PRECONDITION: the generator is valid
	assert( IsValid() );

#ifdef _DEBUG
	if( IsDataNew() == false )
		PyCout << "WARNING: data is out of sync!" << std::endl;
#endif

	XnRGB24Pixel const* imageMap = xn::ImageGenerator::GetRGB24ImageMap();

	convertToBGR24Raw( _rawData, imageMap, XRes(), YRes() );

}	// OpenNIImageGeneratorWrapper::_GetBGR24ImageMapRaw
