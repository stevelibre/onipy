# What is ONIPY ? #

OpenNI Python Wrapper or ONIPY is a Python binding for the excellent OpenNI API released by PrimeSense.

# What can I do with it ? #
OpenNI is a powerful API for building natural interfaces using a variety of sensors for input. This library is being actively used by researchers and other developers around the world to leverage the capabilities of new depth sensors like the Microsoft Kinect or the PrimeSense PrimeSensor.

# Why is it useful ? #

Python is probably one of the best languages for rapid prototyping and it is widely used both in the industry and academia. Python also enjoys a vast selection of third party libraries that expose a substantial array of functionality that ranges from numerical computing (NumPy) to computer vision (OpenCV) and of course games (PyGame). Combining Python with the exciting new possibilities offered by OpenNI and new compliant hardware like Microsoft Kinect can open up new avenues for creative experimentation.

# How does it work ? #
There are several ways to expose the functionality of a C++ library to Python. SWIG is common tool used to automate the generation of Python wrappers, but SWIG tends to be a good tool only for large non object-oriented libraries, such as OpenGL, for which other methods would be unpractical. ONIPY instead uses Boost Python, which simplifies greatly the details of exposing C++ objects to Python compared to Python's low level C API and offers more detailed control over the binding. As a result, bindings created in Boost Python tend to be more reliable and possibly faster. Last but not least, the build process is much easier with Boost Python.