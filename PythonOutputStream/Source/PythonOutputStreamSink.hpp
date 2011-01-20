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


#ifndef PYTHON_OUTPUT_STREAM_SINK_H
#define PYTHON_OUTPUT_STREAM_SINK_H

#include <iostream>
#include <algorithm> 
#include <iosfwd> 
#include <boost/iostreams/categories.hpp> 
#include <boost/iostreams/stream.hpp>
#include <boost/format.hpp>
#include <boost/python.hpp>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

const int SIZE_STREAM_BUFFER = 1000;

class PythonOutputStreamSink
{

public: 

    typedef char char_type; 
//    typedef boost::iostreams::sink_tag category; 

	struct category : 
		boost::iostreams::flushable_tag,
		boost::iostreams::sink_tag
        { };

    std::streamsize write( const char* rawString, std::streamsize stringSize ) 
	{ 

        std::streamsize charactersWritten;
		charactersWritten = std::min( stringSize, SIZE_STREAM_BUFFER ); 

        PySys_WriteStdout( ( boost::format( "%%.%1%s" ) % 
			charactersWritten ).str().c_str(), rawString );

        return charactersWritten; 

	}	// PythonOutputStreamSink::write

	bool flush()
	{
		return true;
	}

}; 

#endif	// PYTHON_OUTPUT_STREAM_SINK_H