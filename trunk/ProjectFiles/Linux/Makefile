ONIPY_DIR = ../../OpenNIPythonWrapper/Source
POS_DIR = ../../PythonOutputStream/Source

PYTHON_INC = /usr/include/python2.6
PYTHON_LIB = /usr/lib/python2.6/config
PYTHON_MOD_DIR = /usr/lib/pymodules/python2.6

BOOST_INC = /usr/include
BOOST_LIB = /usr/lib

OPENNI_INC = /usr/include/ni
OPENNI_LIB = /usr/lib

INCL = -I$(PYTHON_INC) -I$(BOOST_INC) -I$(OPENNI_INC) -I$(POS_DIR)
LIBS = -lboost_python -lOpenNI -lpython2.6

CXX = g++
CXXFLAGS = -fPIC $(INCL)

TARGET = OpenNIPythonWrapper.so

_ONIPY_OBJ = wrapper.o OpenNIContextWrapper.o OpenNIDepthGeneratorWrapper.o \
	OpenNIImageGeneratorWrapper.o OpenNIImageMetaDataWrapper.o \
	conversionHelpers.o
_POS_OBJ = PythonOutputStream.o

ONIPY_OBJ = $(patsubst %,$(ONIPY_DIR)/%,$(_ONIPY_OBJ))
POS_OBJ = $(patsubst %,$(POS_DIR)/%,$(_POS_OBJ))

OBJ = $(ONIPY_OBJ) $(POS_OBJ)

$(ONIPY_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

$(POS_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

$(TARGET): $(OBJ)
	$(CXX) -fPIC -shared -Wl,--export-dynamic $(LIBS) -o $@ $^ 

install:
	cp $(TARGET) $(PYTHON_MOD_DIR)

clean: 
	rm -f $(ONIPY_DIR)/*.o $(POS_DIR)/*.o *.so 