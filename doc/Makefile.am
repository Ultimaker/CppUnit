man3dir = $(mandir)/man3

# FIXME: should be in ${datadir} (i.e. ${prefix}/share) ?
docdir  = $(prefix)/doc/@PACKAGE@-@VERSION@

htmldir = $(docdir)/html
html_DATA = html/*

EXTRA_DIST = cookbook.html header.html footer.html other_documentation.dox

all-local: dox #pdf

dox: html/index.html
html/* html/index.html: Doxyfile other_documentation.dox
	@DOXYGEN@

pdf: @PACKAGE@.pdf
@PACKAGE@.pdf:
	$(MAKE) -C ./latex pdf
	ln -s ./latex/refman.ps	 @PACKAGE@.ps
	ln -s ./latex/refman.pdf @PACKAGE@.pdf


#install-data-local:

# This is failing because doxygen generates manpage filenames with
# spaces in them.  Removed until fixed -smr.
# 
#	$(mkinstalldirs) $(DESTDIR)$(man3dir)
#	@for i in ./man/man3/*.3; do \
#		inst=`basename $$i | sed 's/_/:/g'`; \
#		echo "$(INSTALL_DATA) $$i $(DESTDIR)$(man3dir)/$$inst"; \
#		$(INSTALL_DATA) $$i $(DESTDIR)$(man3dir)/$$inst; \
#	done

# This is replaced by html_DATA.
#	$(mkinstalldirs) $(DESTDIR)$(docdir)
#	cp -r html $(DESTDIR)$(docdir)

# This was commented out long ago.
#	@for i in ../README ../ChangeLog @PACKAGE@.ps @PACKAGE@.pdf; do \
#		echo "$(INSTALL_DATA) $$i $(DESTDIR)$(docdir)"; \
#		$(INSTALL_DATA) $$i $(DESTDIR)$(docdir); \
#	done

clean-local:
	$(RM) -r latex
	$(RM) -r html man @PACKAGE@.ps @PACKAGE@.pdf
