if DOC
SUBDIRS = config src include examples doc
else
SUBDIRS = config src include examples 
endif

DIST_SUBDIRS = config src include examples doc

bin_SCRIPTS = cppunit-config

AUTOMAKE_OPTIONS = 1.4

EXTRA_DIST = cppunit.m4 cppunit.spec.in cppunit.spec

m4datadir = $(datadir)/aclocal
m4data_DATA = cppunit.m4

dist-hook:
	cp -dpR src/msvc6 $(distdir)/src
	cp -dpR include/msvc6 $(distdir)/include 
	cp -dpR examples/msvc6 $(distdir)/examples
	find $(distdir) -name CVS | xargs rm -rf

.PHONY: release snapshot rpm docs doc-dist

release:
	rm -rf .deps */.deps
	$(MAKE) distcheck

snapshot:
	$(MAKE) dist distdir=$(PACKAGE)`date +"%y%m%d"`

rpm: dist
	rpm -ta $(PACKAGE)-$(VERSION).tar.gz
	mv -f /usr/src/redhat/SRPMS/$(PACKAGE)-$(VERSION)-*.rpm .
	mv -f /usr/src/redhat/RPMS/*/$(PACKAGE)-$(VERSION)-*.rpm .
	mv -f /usr/src/redhat/RPMS/*/$(PACKAGE)-doc-$(VERSION)-*.rpm .

docs:
	$(MAKE) -C doc

doc-dist: docs
	tar -zcf $(PACKAGE)-docs-$(VERSION).tar.gz -C doc/html .

