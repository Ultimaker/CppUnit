cmake_minimum_required(VERSION 3.2.3)
project(CppUnit)
set(CPPUNIT_PACKAGE_NAME cppunit CACHE STRING "Name of the package to build.")
set(CPPUNIT_MAJOR_VERSION 1 CACHE STRING "Major (first) version number.")
set(CPPUNIT_MINOR_VERSION 14 CACHE STRING "Minor (second) version number.")
set(CPPUNIT_PATCH_VERSION 2 CACHE STRING "Patch (third) version number.")

set(Sources
    src/cppunit/AdditionalMessage.cpp
    src/cppunit/Asserter.cpp
    src/cppunit/BriefTestProgressListener.cpp
    src/cppunit/CompilerOutputter.cpp
    src/cppunit/DefaultProtector.cpp
    #src/cppunit/DllMain.cpp #Apparently this one isn't built.
    src/cppunit/DynamicLibraryManager.cpp
    src/cppunit/DynamicLibraryManagerException.cpp
    src/cppunit/Exception.cpp
    src/cppunit/Message.cpp
    src/cppunit/PlugInManager.cpp
    src/cppunit/PlugInParameters.cpp
    src/cppunit/Protector.cpp
    src/cppunit/ProtectorChain.cpp
    src/cppunit/RepeatedTest.cpp
    src/cppunit/ShlDynamicLibraryManager.cpp
    src/cppunit/SourceLine.cpp
    src/cppunit/StringTools.cpp
    src/cppunit/SynchronizedObject.cpp
    src/cppunit/Test.cpp
    src/cppunit/TestAssert.cpp
    src/cppunit/TestCase.cpp
    src/cppunit/TestCaseDecorator.cpp
    src/cppunit/TestComposite.cpp
    src/cppunit/TestDecorator.cpp
    src/cppunit/TestFactoryRegistry.cpp
    src/cppunit/TestFailure.cpp
    src/cppunit/TestLeaf.cpp
    src/cppunit/TestNamer.cpp
    src/cppunit/TestPath.cpp
    src/cppunit/TestPlugInDefaultImpl.cpp
    src/cppunit/TestResult.cpp
    src/cppunit/TestResultCollector.cpp
    src/cppunit/TestRunner.cpp
    src/cppunit/TestSetUp.cpp
    src/cppunit/TestSuccessListener.cpp
    src/cppunit/TestSuite.cpp
    src/cppunit/TestSuiteBuilderContext.cpp
    src/cppunit/TextOutputter.cpp
    src/cppunit/TextTestProgressListener.cpp
    src/cppunit/TextTestResult.cpp
    src/cppunit/TextTestRunner.cpp
    src/cppunit/TypeInfoHelper.cpp
    src/cppunit/UnixDynamicLibraryManager.cpp
    src/cppunit/Win32DynamicLibraryManager.cpp
    src/cppunit/XmlDocument.cpp
    src/cppunit/XmlElement.cpp
    src/cppunit/XmlOutputter.cpp
    src/cppunit/XmlOutputterHook.cpp
)
set(HeaderDirs
    src/cppunit
    include
)

configure_file("config-auto.h.in" "config-auto.h")

#Build CppUnit's library.
include_directories(${HeaderDirs})
add_library(CppUnit STATIC ${Sources})

#Installation.
include(GNUInstallDirs)
install(TARGETS CppUnit DESTINATION ${CMAKE_INSTALL_LIBDIR})
