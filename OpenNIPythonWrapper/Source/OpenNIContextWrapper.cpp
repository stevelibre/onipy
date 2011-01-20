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


#include "OpenNIContextWrapper.h"
#include <PythonOutputStream.h>


XnStatus OpenNIContextWrapper::InitFromXmlFile( 
	const std::string& initializationFilename )
{

#ifdef _DEBUG
	PyCout << "Initializing OpenNI.." << std::endl;
#endif

	XnStatus returnCode;
	returnCode = xn::Context::InitFromXmlFile( initializationFilename.c_str() );

#ifdef _DEBUG
	if( returnCode == XN_STATUS_OK )
		PyCout << "OpenNI was initialized successfully" << std::endl;
	else
		PyCout << "OpenNI failed to initialize" << std::endl;
#endif
	
	return returnCode;

}	// OpenNIContextWrapper::InitFromXmlFile

void OpenNIContextWrapper::Shutdown()
{

#ifdef _DEBUG
	PyCout << "Shutting down OpenNI.." << std::endl;
#endif

}	// OpenNIContextWrapper::Shutdown
