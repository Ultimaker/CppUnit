EXTRA_DIST =  WinNtTimer.h WinNtTimer.cpp ClockerPlugIn.dsp \
	Timer.h ClockerListener.h \
	Timer.cpp ClockerListener.cpp \
	ClockerPlugIn.cpp

INCLUDES = -I$(top_builddir)/include -I$(top_srcdir)/include

#dummy stuff to make automake happy

bin_PROGRAMS = dummyMain

dummyMain_SOURCES = dummyMain.cpp

dummyMain_LDADD= \
  $(top_builddir)/src/cppunit/libcppunit.la 

dummyMain_LDFLAGS = -ldl
