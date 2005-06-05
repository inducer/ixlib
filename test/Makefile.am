# -----------------------------------------------------------------------------
# iXiON library test makefile
# -----------------------------------------------------------------------------
# (c) iXiONmedia 1999
# -----------------------------------------------------------------------------

LDADD=../src/libixion.la

check_PROGRAMS=teststring testnumconv testre testcmdline testtextfile \
  testgeo testxml testmat testjs testgarbage

noinst_PROGRAMS=javascript

EXTRA_DIST=src.txt frobnitz.par runem test.js invertmap.js \
  test-big.xml test-structure.xml aarray.js

noinst_SCRIPTS=runem

teststring_SOURCES=teststring.cpp test.hpp
testnumconv_SOURCES=testnumconv.cpp test.hpp
testre_SOURCES=testre.cpp test.hpp
testcmdline_SOURCES=testcmdline.cpp test.hpp
testtextfile_SOURCES=testtextfile.cpp test.hpp
# testscanner_SOURCES=testscanner.cpp
testgeo_SOURCES=testgeo.cpp test.hpp
testxml_SOURCES=testxml.cpp test.hpp
testmat_SOURCES=testmat.cpp test.hpp
testjs_SOURCES=testjs.cpp test.hpp
testgarbage_SOURCES=testgarbage.cpp test.hpp

javascript_SOURCES=javascript.cpp aarray.cpp

check-local:
	./runem $(check_PROGRAMS)
