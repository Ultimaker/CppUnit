EXTRA_DIST = DllPlugInTester.dsp

INCLUDES = -I$(top_builddir)/include -I$(top_srcdir)/include

hierarchy_SOURCES= BoardGame.cpp \
                   Chess.cpp \
                   main.cpp \
                   BoardGame.h \
                   Chess.h \
                   BoardGameTest.h \
                   ChessTest.h

hierarchy_LDADD= \
  $(top_builddir)/src/cppunit/libcppunit.la 

