# Include cookbook.html in distro
EXTRA_DIST = money.dsp money.dsw configure.in StdAfx.cpp

# Rules to make the production code
#bin_PROGRAMS = Money
#main_SOURCES = Money.h

# Rules for the test code (use `make check` to execute)
TESTS = MoneyApp
check_PROGRAMS = $(TESTS)
MoneyApp_SOURCES = Money.h MoneyTest.h MoneyTest.cpp MoneyApp.cpp StdAfx.h
MoneyApp_CXXFLAGS = $(CPPUNIT_CFLAGS)
MoneyApp_LDFLAGS = $(CPPUNIT_LIBS) -ldl

