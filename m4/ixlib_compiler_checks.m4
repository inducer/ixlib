# -----------------------------------------------------------------------------
# iXiON library extended compiler checks
# -----------------------------------------------------------------------------
# (c) iXiONmedia 1999
# -----------------------------------------------------------------------------




AC_DEFUN(IX_CXX_SUPPORTS_CLASS_TEMPLATES,[
  AC_MSG_CHECKING([whether c++ compiler ($CXX) supports class templates])
  AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  AC_TRY_COMPILE([template <class T> class oomph { T x; }; ],[oomph<int> u;],
    ix_cxx_supports_class_templates=yes,
    ix_cxx_supports_class_templates=no)
  AC_LANG_RESTORE
  if test "$ix_cxx_supports_class_templates" = "yes" ; then
    AC_MSG_RESULT([yup])
  else
    AC_MSG_RESULT([no])
    AC_MSG_ERROR([Sorry, you'll need a compiler that supports class templates 
	to compile $PACKAGE. Try using GNU C++, available from ftp.gnu.org, and
	see 'config.log' for further diagnostics.])
  fi
])




AC_DEFUN(IX_CXX_SUPPORTS_EXCEPTIONS,[
  AC_MSG_CHECKING([whether c++ compiler ($CXX) supports exceptions])
  AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  AC_TRY_COMPILE(,[try { throw 1; } catch (int a) { return 1; } ],
    ix_cxx_supports_exceptions=yes,
    ix_cxx_supports_exceptions=no)
  AC_LANG_RESTORE
  if test "$ix_cxx_supports_exceptions" = "yes" ; then
    AC_MSG_RESULT([yup])
  else
    AC_MSG_RESULT([no])
    AC_MSG_ERROR([Sorry, you'll need a compiler that supports exceptions
	to compile $PACKAGE. Try using GNU C++, available from ftp.gnu.org, and
	see 'config.log' for further diagnostics. If your compiler ($CXX)
	needs special flags for this, define CXXFLAGS appropriately and rerun
	configure.])
  fi
])




AC_DEFUN(IX_CXX_SUPPORTS_BOOL,[
  AC_MSG_CHECKING([whether c++ compiler ($CXX) supports bool])
  AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  AC_TRY_COMPILE(,[ bool a = true; ],
    ix_cxx_supports_bool=yes,
    ix_cxx_supports_bool=no)
  AC_LANG_RESTORE
  if test "$ix_cxx_supports_bool" = "yes" ; then
    AC_MSG_RESULT([yup])
  else
    AC_MSG_RESULT([no])
    AC_DEFINE(bool,unsigned char,[Substitute 'bool' by 'unsigned char' if necessary])
    AC_DEFINE(true,1,[Substitute 'true' by '1' if necessary])
    AC_DEFINE(false,0,[Substitute 'false' by '0' if necessary])
  fi
])




AC_DEFUN(IX_CXX_SUPPORTS_WSTRING,[
  AC_MSG_CHECKING([whether c++ compiler ($CXX) supports wstring])
  AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  AC_TRY_COMPILE(#include <string>,[ wstring a; ],
    ix_cxx_supports_wstring=yes,
    ix_cxx_supports_wstring=no)
  AC_LANG_RESTORE
  if test "$ix_cxx_supports_wstring" = "yes" ; then
    AC_MSG_RESULT([yup])
    AC_DEFINE(IX_CXX_HAVE_WSTRING,1,[Whether C++ compiler knows wstring])
  else
    AC_MSG_RESULT([no])
  fi
])
