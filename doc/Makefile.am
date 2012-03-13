.PHONY: install-data-hook uninstall-local clean-local

if DOC
html_DATA = html/index.html

install-data-hook:
	cp -pR html/* $(DESTDIR)$(htmldir)

uninstall-local:
	rm -rf $(DESTDIR)$(htmldir)

dox: html/index.html
else
install-data-hook:
uninstall-local:
dox:
endif

all-local: dox

html/index.html: Doxyfile $(doxygen_input)
	"@DOXYGEN@"

# Make tarfile to distribute the HTML documentation.
doc-dist: dox
	tar -cJf $(PACKAGE)-docs-$(VERSION).tar.xz -C html .

pdf: @PACKAGE@.pdf
@PACKAGE@.pdf:
	$(MAKE) -C ./latex pdf
	ln -s ./latex/refman.ps	 @PACKAGE@.ps
	ln -s ./latex/refman.pdf @PACKAGE@.pdf

clean-local:
	$(RM) -r latex
	$(RM) -r html man @PACKAGE@.ps @PACKAGE@.pdf
