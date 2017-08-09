cmake_minimum_required(VERSION 3.2.3)
project(CppUnit)

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
set(SourcesAbsolute "")
foreach(Source ${Sources})
    list(APPEND SourcesAbsolute ${CMAKE_SOURCE_DIR}/${Source})
endforeach()
set(HeaderDirsAbsolute "")
foreach(HeaderDir ${HeaderDirs})
    list(APPEND HeaderDirsAbsolute ${CMAKE_SOURCE_DIR}/${HeaderDir})
endforeach()

#Build CppUnit's library.
include_directories(${HeaderDirsAbsolute})
add_library(CppUnit STATIC ${SourcesAbsolute})

#Installation.
include(GNUInstallDirs)
install(TARGETS CppUnit DESTINATION ${CMAKE_INSTALL_LIBDIR})
