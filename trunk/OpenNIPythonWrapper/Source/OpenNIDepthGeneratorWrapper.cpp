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


#include "OpenNIDepthGeneratorWrapper.h"
#include "conversionHelpers.h"

#include <PythonOutputStream.h>

OpenNIDepthGeneratorWrapper::OpenNIDepthGeneratorWrapper()
{

#ifdef _DEBUG
	PyCout << "Creating DepthGenerator" << std::endl;
#endif

}	// OpenNIDepthGeneratorWrapper::OpenNIDepthGeneratorWrapper

XnUInt32 OpenNIDepthGeneratorWrapper::XRes() const
{

	xn::DepthMetaData proxyDepthMetaData;
	xn::DepthGenerator::GetMetaData( proxyDepthMetaData );

	return proxyDepthMetaData.XRes();

}	// OpenNIDepthGeneratorWrapper::XRes

XnUInt32 OpenNIDepthGeneratorWrapper::YRes() const
{

	xn::DepthMetaData proxyDepthMetaData;
	xn::DepthGenerator::GetMetaData( proxyDepthMetaData );

	return proxyDepthMetaData.YRes();

}	// OpenNIDepthGeneratorWrapper::YRes

BP::tuple OpenNIDepthGeneratorWrapper::Res() const
{

	return BP::make_tuple( XRes(), YRes() );

}	// OpenNIDepthGeneratorWrapper::Res

BP::tuple OpenNIDepthGeneratorWrapper::GetGrayscale16DepthMapTuple() const
{

	// PRECONDITION: the generator is valid
	assert( IsValid() );

#ifdef _DEBUG
	if( IsDataNew() == false )
		PyCout << "WARNING: data is out of sync!" << std::endl;
#endif

	XnDepthPixel const* depthMap = xn::DepthGenerator::GetDepthMap();

	BP::tuple mapTuple;
	convert( mapTuple, depthMap, XRes(), YRes() );

	return mapTuple;

}	// OpenNIDepthGeneratorWrapper::GetGrayscale16DepthMapTuple

std::string OpenNIDepthGeneratorWrapper::GetGrayscale16DepthMapRaw() const
{

	// PRECONDITION: the generator is valid
	assert( IsValid() );

#ifdef _DEBUG
	if( IsDataNew() == false )
		PyCout << "WARNING: data is out of sync!" << std::endl;
#endif

	XnDepthPixel const* depthMap = xn::DepthGenerator::GetDepthMap();

	std::string rawData( 
		(const char*)depthMap,
		XRes() * YRes() * sizeof( XnDepthPixel ) );

	return rawData;

}	// OpenNIDepthGeneratorWrapper::GetGrayscale16DepthMapRaw

std::string OpenNIDepthGeneratorWrapper::GetGrayscale8DepthMapRaw() const
{

	// PRECONDITION: the generator is valid
	assert( IsValid() );

#ifdef _DEBUG
	if( IsDataNew() == false )
		PyCout << "WARNING: data is out of sync!" << std::endl;
#endif

	XnDepthPixel const* depthMap = xn::DepthGenerator::GetDepthMap();	

	std::string rawDataGrayscale8;
	convertToGrayscale8Raw( rawDataGrayscale8, depthMap, XRes(), YRes() );

	return rawDataGrayscale8;

}	// OpenNIDepthGeneratorWrapper::GetGrayscale8DepthMapRaw
