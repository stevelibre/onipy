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


#ifndef PYTHON_OUTPUT_STREAM_H
#define PYTHON_OUTPUT_STREAM_H

#include "PythonOutputStreamManager.hpp"

class PythonOutputStream
{

public:
	~PythonOutputStream()	
	{

		delete _pythonOutputStreamManagerReference;
		
	}

	static PythonOutputStreamManager* instance()
	{

		if( _pythonOutputStreamManagerReference == NULL )
		{
			_pythonOutputStreamManagerReference = new PythonOutputStreamManager();
		}

		return _pythonOutputStreamManagerReference;

	}	// PythonOutputStream::instance

private:
	PythonOutputStream()	{}

	static PythonOutputStreamManager* _pythonOutputStreamManagerReference;

};

#define PyCout	PythonOutputStream::instance()->pyCout

#endif	// PYTHON_OUTPUT_STREAM_H