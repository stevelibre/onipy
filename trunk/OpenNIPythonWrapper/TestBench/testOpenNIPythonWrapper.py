"""
Test module for the OpenNI Python bindings

Copyright (C) 2011 Gabriele Nataneli (gamix)

"""


#-------------------------------------------------------------------------------
# flags

# if you don't want this script to setup the PATH at run time, change this to
# False
FLAG_SETUP_ENVIRONMENT = True


#-------------------------------------------------------------------------------
# import built-in modules

import os
import sys
import platform


#-------------------------------------------------------------------------------
# setup the environment so that Python can find all required dependencies

if FLAG_SETUP_ENVIRONMENT == True:
	
	if platform.system() == 'Windows':
	
		# add all the directories where the dlls are located to the system PATH
		# variable, so that Windows can find them
	
		# set the Boost path based on the BOOST_ROOT environment variable. I expect
		# to find the dlls for Boost in $(BOOST_ROOT)\lib. If this is not the case,
		# then change BOOST_LIB_PATH to point to the absolute path where the dlls are
	
		EXTENDED_PATH_ITEMS = []
	
		BOOST_PATH = os.getenv( 'BOOST_ROOT' )
		BOOST_LIB_PATH = os.path.join( BOOST_PATH, 'lib' )
		EXTENDED_PATH_ITEMS.append( BOOST_LIB_PATH )
	
		# set the Boost path based on the OPENNI_DIR environment variable. I expect
		# to find the dlls for Boost in $(OPENNI_DIR)\Bin. If this is not 
		# the case, then change OPENI_LIB_PATH to point to the absolute path where the
		#  dlls are
		
		OPENNI_PATH = os.getenv( 'OPENNI_DIR' )
		OPENI_LIB_PATH = os.path.join( OPENNI_PATH, 'Bin' )
		EXTENDED_PATH_ITEMS.append( OPENI_LIB_PATH )
		
		EXTENDED_PATH_VARIABLE = ""
		
		for currentPath in EXTENDED_PATH_ITEMS:
			EXTENDED_PATH_VARIABLE += currentPath + ";"
	
		EXTENDED_PATH_VARIABLE += os.getenv( "PATH" )
	
		os.putenv( "PATH", EXTENDED_PATH_VARIABLE )
		
	elif platform.system() == 'Darwin':
		# make sure that libboost_python.dylib is in the same dyrectory as this
		# script
		pass
			
	elif platform.system() == 'Linux':
		# Linux: it's assumed that the library paths are already
		# taken care of in the environment, so we do nothing
		pass
	else:
		raise "ERROR: the current platform is not supported yet!"	


#-------------------------------------------------------------------------------
# constants

OPENNI_INITIALIZATION_FILE = "../OpenNIConfigurations/BasicColorAndDepth.xml"
TEST_IMAGE_FRAME = "testImageFrame.jpg"
TEST_DEPTH_FRAME = "testDepthFrame.jpg"
KEY_ESC = 27


#-------------------------------------------------------------------------------
# global variables
g_context = None
g_supportPIL = None
g_supportOpenCV = None


#-------------------------------------------------------------------------------
# import custom modules

import OpenNIPythonWrapper as ONIPY


#-------------------------------------------------------------------------------
# import optional modules

try:
	from PIL import Image
	g_supportPIL = True
except:
	print "WARNING: Python Imaging library (PIL) is not available on this machine"
	g_supportPIL = False

try:
	import cv
	g_supportOpenCV = True
except:
	print "WARNING: The OpenCV Python binding is not available on this machine"
	g_supportOpenCV = False


#-------------------------------------------------------------------------------
# runUnitTest

def runUnitTest( unitTestFunction ):
	print "RUNNING UNIT TEST: %s" %( unitTestFunction.__name__ )
	unitTestFunction()
	print "COMPLETED UNIT TEST: %s " %( unitTestFunction.__name__ )


#-------------------------------------------------------------------------------
# unitTestConstants

def unitTestConstants():
	"""
	Print out the constants exposed by the wrapper.
	"""
	
	
	for variableName in ONIPY.__dict__.keys():
		
		if variableName.find( "__" ) >= 0:
			continue
		
		value = ONIPY.__dict__[ variableName ]
		if type( value ) == int or \
			type( value ) == float or \
			type( value ) == str:
			print variableName, ":", value 
			
		if type( value ) == ONIPY.XnProductionNodeType:
			print variableName, "[enum]"


#-------------------------------------------------------------------------------
# unitTestBasicInitialization

def unitTestBasicInitialization():
	"""
	Initialize OpenNI and shutdown. You always need to do this!
	"""
	
	
	global g_context
	g_context = ONIPY.OpenNIContext()
	returnCode = g_context.InitFromXmlFile( OPENNI_INITIALIZATION_FILE )
	
	if returnCode != ONIPY.XN_STATUS_OK:
		print "failed to initialize OpenNI"
		return	
		
	g_context.Shutdown()


#-------------------------------------------------------------------------------
# unitTestImageGenerator

def unitTestImageGenerator():
	"""
	Set up an image generator node and use PIL to save a single frame from the
	sensor.
	"""


	global g_context
	
	g_context = ONIPY.OpenNIContext()
	returnCode = g_context.InitFromXmlFile( OPENNI_INITIALIZATION_FILE )
	
	if returnCode != ONIPY.XN_STATUS_OK:
		print "failed to initialize OpenNI"
		return	
		
	imageGenerator = ONIPY.OpenNIImageGenerator()
	
	returnCode = g_context.FindExistingNode( \
		ONIPY.XN_NODE_TYPE_IMAGE, \
		imageGenerator )
	
	returnCode = g_context.WaitAndUpdateAll()
	
	if returnCode == ONIPY.XN_STATUS_OK:
		print "update was successful"
	else:
		print "update was not successful"
			
	if imageGenerator.IsValid():
		
		# NOTE: the meta data is exposed directly through the generator
		print "X resolution: ", imageGenerator.XRes()
		print "Y resolution: ", imageGenerator.YRes()
	
		imageDataRaw = imageGenerator.GetRGB24ImageMapRaw()
		
		if g_supportPIL:
			image = Image.fromstring( \
			mode = "RGB",
			size = [ imageGenerator.XRes(), imageGenerator.YRes() ], 
			data = imageDataRaw )
	
			image.save( TEST_IMAGE_FRAME )
	
	g_context.Shutdown()


#-------------------------------------------------------------------------------
# unitTestDepthGenerator

def unitTestDepthGenerator():
	"""
	Set up an depth generator node and use PIL to save a single frame from the
	sensor.
	"""


	global g_context
	
	g_context = ONIPY.OpenNIContext()
	returnCode = g_context.InitFromXmlFile( OPENNI_INITIALIZATION_FILE )
	
	if returnCode != ONIPY.XN_STATUS_OK:
		print "failed to initialize OpenNI"
		return	
	
	depthGenerator = ONIPY.OpenNIDepthGenerator()
	
	returnCode = g_context.FindExistingNode( \
		ONIPY.XN_NODE_TYPE_DEPTH, \
		depthGenerator )
	
	returnCode = g_context.WaitAndUpdateAll()
	
	if returnCode == ONIPY.XN_STATUS_OK:
		print "update was successful"
	else:
		print "update was not successful"
			
	if depthGenerator.IsValid():
		
		# NOTE: the meta data is exposed directly through the generator
		print "X resolution: ", depthGenerator.XRes()
		print "Y resolution: ", depthGenerator.YRes()
	
		depthDataRaw = depthGenerator.GetGrayscale8DepthMapRaw()
		
		if g_supportPIL:
			image = Image.fromstring( \
			mode = "L",
			size = depthGenerator.Res(), 
			data = depthDataRaw )
	
			image.save( TEST_DEPTH_FRAME )
	
	g_context.Shutdown()


#-------------------------------------------------------------------------------
# unittestVideoStreams

def unittestVideoStreams():
	"""
	Show both the image and depth streams in separate OpenCV Windows
	"""
	
	
	if g_supportOpenCV == False:
		print "This unit test requires OpenCV!"
		return

	global g_context
	
	g_context = ONIPY.OpenNIContext()
	returnCode = g_context.InitFromXmlFile( OPENNI_INITIALIZATION_FILE )

	if returnCode != ONIPY.XN_STATUS_OK:
		print "failed to initialize OpenNI"
		return	

	try:
	
		imageGenerator = ONIPY.OpenNIImageGenerator()
		
		returnCode = g_context.FindExistingNode( \
			ONIPY.XN_NODE_TYPE_IMAGE, \
			imageGenerator )

		currentImageFrame = None

		depthGenerator = ONIPY.OpenNIDepthGenerator()

		returnCode = g_context.FindExistingNode( \
			ONIPY.XN_NODE_TYPE_DEPTH, \
			depthGenerator )
		
		currentDepthFrame = None
			
		while( True ):
	
			returnCode = g_context.WaitAndUpdateAll()
			
			if returnCode != ONIPY.XN_STATUS_OK:
				print "failed to update OpenNI"
				break	
			
			if imageGenerator.IsValid() == False:
				print "image generator is not valid"
				break
			
			if depthGenerator.IsValid() == False:
				print "depth generator is not valid"
				break
			
			if currentImageFrame == None:
				currentImageFrame = cv.CreateImageHeader( \
				imageGenerator.Res(), \
				cv.IPL_DEPTH_8U, \
					3 )

			if currentDepthFrame == None:
				currentDepthFrame = cv.CreateImageHeader( \
				depthGenerator.Res(), \
				cv.IPL_DEPTH_8U, \
					1 )

						
			imageDataRaw = imageGenerator.GetBGR24ImageMapRaw()
			cv.SetData( currentImageFrame, imageDataRaw )

			depthDataRaw = depthGenerator.GetGrayscale8DepthMapRaw()
			cv.SetData( currentDepthFrame, depthDataRaw )

			cv.ShowImage( "Image Stream", currentImageFrame )
			cv.ShowImage( "Depth Stream", currentDepthFrame )

			currentKey = cv.WaitKey( 5 )

			if currentKey == KEY_ESC:
				break

	finally:
	
		g_context.Shutdown()


#-------------------------------------------------------------------------------
# main

def main():
	"""
	Run some unit tests to exercise the functionality exposed by the binding.
	"""
	
	
	print "OpenNI Python Wrapper version %s " % ( ONIPY.version() )
	print "Copyright (C) 2011 Gabriele Nataneli (gamix)"
	print ""
	
	# runUnitTest( unitTestConstants )
	runUnitTest( unitTestBasicInitialization )
	# runUnitTest( unitTestImageGenerator )
	# runUnitTest( unitTestDepthGenerator )
	# runUnitTest( unittestVideoStreams )


#-------------------------------------------------------------------------------
# entry point

if __name__ == '__main__':
	main()

