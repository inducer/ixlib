# -----------------------------------------------------------------------------
# ixlib main makefile
# -----------------------------------------------------------------------------
# (c) Andreas Kloeckner 2000. See COPYING for license.
# -----------------------------------------------------------------------------




localedir = $(datadir)/locale
DEFS = -DLOCALEDIR=\"$(localedir)\" @DEFS@
INCLUDES = -I..



# Source files ----------------------------------------------------------------
basic_headers=ixlib_base.hpp ixlib_array.hpp ixlib_garbage.hpp \
  ixlib_exbase.hpp ixlib_exgen.hpp ixlib_exio.hpp \
  ixlib_string.hpp ixlib_re.hpp ixlib_re_impl.hpp \
  ixlib_numconv.hpp ixlib_numeric.hpp \
  ixlib_random.hpp ixlib_ring_queue.hpp

basic_objects=base.cpp exbase.cpp exgen.cpp exio.cpp \
  string.cpp numconv.cpp numeric.cpp re.cpp

advanced_headers=ixlib_cmdline.hpp \
  ixlib_geometry.hpp ixlib_geometry_impl.hpp \
  ixlib_polygon.hpp ixlib_polygon_impl.hpp \
  ixlib_matrix.hpp ixlib_matrix_impl.hpp \
  ixlib_textfile.hpp ixlib_scanner.hpp ixlib_token_lex.hpp \
  ixlib_xml.hpp \
  ixlib_javascript.hpp \
  ixlib_drawing_functions.hpp 

advanced_objects=cmdline.cpp textfile.cpp scanner.cpp xml.cpp \
  js_value.cpp js_expression.cpp js_declaration.cpp \
  js_instruction.cpp js_array.cpp js_library.cpp \
  js_interpreter.cpp

internal_headers=ixlib_token_xml.hpp ixlib_scanxml.hpp ixlib_scanjs.hpp \
  ixlib_js_internals.hpp ixlib_token_javascript.hpp \
  ixlib_i18n.hpp 

internal_objects=lex.xml.cpp lex.javascript.cpp

# Generated sources -----------------------------------------------------------
lex.xml.cpp: lex.xml.yy
	$(LEX) $< 

lex.javascript.cpp: lex.javascript.yy
	$(LEX) $< 

BUILT_SOURCES=lex.xml.cpp lex.javascript.cpp 

CLEANFILES=lex.xml.cpp lex.javascript.cpp

EXTRA_DIST=lex.xml.yy lex.javascript.yy flex-gcc3-patch.ed

# Targets ---------------------------------------------------------------------
lib_LTLIBRARIES=libixion.la

libixion_la_SOURCES=$(basic_headers) $(basic_objects) \
   $(advanced_headers) $(advanced_objects) \
   $(internal_headers) $(internal_objects)
libixion_la_LIBADD=@LEXLIB@ $(INTLLIBS)
libixion_la_LDFLAGS=-version-info @IXLIB_BINARY_IFACE_VERSION@:@IXLIB_BINARY_REVISION@:@IXLIB_BINARY_AGE@ \
  -no-undefined

include_HEADERS=$(basic_headers) $(advanced_headers)
noinst_HEADERS=$(internal_headers)
