#----------------------------------------------------------------------
# File:    qt_example.pro
# Purpose: qmake config file for the QtTestRunner example.
#          The program is built with the QtTestRunner debug staticlib.
#          Set the CONFIG variable accordingly to build it differently.
#----------------------------------------------------------------------

TEMPLATE = app
LANGUAGE = C++
TARGET   = qt_example

# Get rid of possibly predefined options

CONFIG -= debug
CONFIG -= release

#CONFIG += qt warn_on debug use_static

#CONFIG += qt warn_on release use_static
#CONFIG += qt warn_on debug use_dll
CONFIG += qt warn_on release use_dll

#----------------------------------------------------------------------
# MS Windows
#----------------------------------------------------------------------

win32 {
    use_dll {
        DEFINES += QTTESTRUNNER_DLL
        debug {
            OBJECTS_DIR = DebugDLL
            LIBS += ..\..\lib\cppunitd_dll.lib
            LIBS += ..\..\lib\qttestrunnerd_dll.lib
        }
        release {
            OBJECTS_DIR = ReleaseDLL
            LIBS += ..\..\lib\cppunit_dll.lib
            LIBS += ..\..\lib\qttestrunner_dll.lib
        }
    }
    use_static {
        debug {
            OBJECTS_DIR = Debug
            LIBS += ..\..\lib\cppunitd.lib
            LIBS += ..\..\lib\qttestrunnerd.lib
        }
        release {
            OBJECTS_DIR = Release
            LIBS += ..\..\lib\cppunit.lib
            LIBS += ..\..\lib\qttestrunner.lib
        }
    }
    DESTDIR = $${OBJECTS_DIR}
}

#----------------------------------------------------------------------
# Linux/Unix
#----------------------------------------------------------------------

unix {
    message("NOT IMPLEMENTED YET!")
}

#----------------------------------------------------------------------

HEADERS = \
        ExampleTestCases.h

SOURCES = \
        ExampleTestCases.cpp \
        Main.cpp

INCLUDEPATH += . ../../include
