htmldir = $(pkgdatadir)/html

EXTRA_DIST = $(doxygen_input) $(static_pages)

doxygen_input = other_documentation.dox header.html footer.html
static_pages = cookbook.html FAQ


# DOC is defined if installer requests doc generation.
# For now, we only install HTML documentation.  We could install manpages
# using the following
#   man_MANS = man/man3/CppUnit.3
#   man/man3/CppUnit.3: dox
# and an extra copy or two in the install-data-hook.  
# However, the manpages do not appear to be tremendously useful, so
# let's not bother.

if DOC

html_DATA = $(static_pages) html/index.html

install-data-hook:
	cp -dpR html/* $(DESTDIR)$(htmldir)

# Automake's "distcheck" is sensitive to having files left over
# after "make uninstall", so we have to clean up the install hook.
uninstall-local:
	rm -rf $(DESTDIR)$(htmldir)

all-local: dox #pdf

endif


# Workaround for broken Doxygen.  Version 1.2.9.1 doesn't create
# this directory, though it does create man/man3.
man_extension_dir = man/man3/extensions
$(man_extension_dir):
	mkdir -p $@


dox: html/index.html

html/index.html: Doxyfile $(doxygen_input) $(man_extension_dir)
	@DOXYGEN@


# Distribute the HTML documentation.
doc-dist: dox
	cp $(static_pages) html
	tar -czf $(PACKAGE)-docs-$(VERSION).tar.gz -C html .

pdf: @PACKAGE@.pdf
@PACKAGE@.pdf:
	$(MAKE) -C ./latex pdf
	ln -s ./latex/refman.ps	 @PACKAGE@.ps
	ln -s ./latex/refman.pdf @PACKAGE@.pdf


clean-local:
	$(RM) -r latex
	$(RM) -r html man @PACKAGE@.ps @PACKAGE@.pdf
