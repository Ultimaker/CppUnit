if DOC
SUBDIRS = cppunit examples doc
else
SUBDIRS = cppunit examples 
endif

DIST_SUBDIRS = cppunit examples doc

bin_SCRIPTS = cppunit-config

AUTOMAKE_OPTIONS = 1.4

EXTRA_DIST = \
	cppunit.m4 \
	AUTHORS \
	COPYING \
	ChangeLog \
	INSTALL \
	README \
	TODO 

m4datadir = $(datadir)/aclocal
m4data_DATA = cppunit.m4

.PHONY: release snapshot docs

release:
	rm -rf .deps */.deps
	$(MAKE) distcheck

snapshot:
	$(MAKE) dist distdir=$(PACKAGE)`date +"%y%m%d"`

docs:
	$(MAKE) -C doc


