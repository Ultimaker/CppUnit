htmldir = $(pkgdatadir)/html

EXTRA_DIST = $(doxygen_input) $(static_pages)


doxygen_input = other_documentation.dox
static_pages = cookbook.html header.html footer.html 


# DOC is defined if installer requests doc generation
if DOC
man_MANS = man/man3/*.3 man/man3/extensions/*.3
html_DATA = $(static_pages) html/*
all-local: dox #pdf
endif


# Workaround for broken Doxygen.  Version 1.2.9.1 doesn't create
# this directory, though it does create man/man3.
man_extension_dir = man/man3/extensions
$(man_extension_dir):
	mkdir -p $@


dox: html/index.html
html/* man/man3/*.3 man/man3/extensions/*.3: html/index.html
html/index.html: Doxyfile other_documentation.dox $(man_extension_dir)
	@DOXYGEN@

pdf: @PACKAGE@.pdf
@PACKAGE@.pdf:
	$(MAKE) -C ./latex pdf
	ln -s ./latex/refman.ps	 @PACKAGE@.ps
	ln -s ./latex/refman.pdf @PACKAGE@.pdf


clean-local:
	$(RM) -r latex
	$(RM) -r html man @PACKAGE@.ps @PACKAGE@.pdf
