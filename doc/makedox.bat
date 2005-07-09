SET VERSION=1.10.4
doxygen CppUnit-win.dox
xcopy FAQ html /Y

@echo Warnings:
@type CppUnit-dox.log
