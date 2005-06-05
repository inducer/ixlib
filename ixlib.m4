dnl AM_PATH_IXLIB([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND [, MODULES]]]])
dnl Test for ixlib, and define IXLIB_CFLAGS, IXLIB_LIBS
dnl
AC_DEFUN(AM_PATH_IXLIB,
[dnl 
dnl Get the cflags and libraries from the ixlib-config script
dnl
AC_ARG_WITH(ixlib-prefix,[  --with-ixlib-prefix=PFX   Prefix where IXLIB is installed (optional)],
            ixlib_config_prefix="$withval", ixlib_config_prefix="")
AC_ARG_WITH(ixlib-exec-prefix,[  --with-ixlib-exec-prefix=PFX Exec prefix where IXLIB is installed (optional)],
            ixlib_config_exec_prefix="$withval", ixlib_config_exec_prefix="")
AC_ARG_ENABLE(ixlibtest, [  --disable-ixlibtest       Do not try to compile and run a test IXLIB program],
		    , enable_ixlibtest=yes)

  if test x$ixlib_config_exec_prefix != x ; then
     ixlib_config_args="$ixlib_config_args --exec-prefix=$ixlib_config_exec_prefix"
     if test x${IXLIB_CONFIG+set} != xset ; then
        IXLIB_CONFIG=$ixlib_config_exec_prefix/bin/ixlib-config
     fi
  fi
  if test x$ixlib_config_prefix != x ; then
     ixlib_config_args="$ixlib_config_args --prefix=$ixlib_config_prefix"
     if test x${IXLIB_CONFIG+set} != xset ; then
        IXLIB_CONFIG=$ixlib_config_prefix/bin/ixlib-config
     fi
  fi

  AC_PATH_PROG(IXLIB_CONFIG, ixlib-config, no)
  min_ixlib_version=ifelse([$1], , 0.90.0, $1)
  AC_MSG_CHECKING(for ixlib version >= $min_ixlib_version)
  no_ixlib=""
  if test "$IXLIB_CONFIG" = "no" ; then
    no_ixlib=yes
  else
    IXLIB_CFLAGS=`$IXLIB_CONFIG $ixlib_config_args --cflags`
    IXLIB_LIBS=`$IXLIB_CONFIG $ixlib_config_args --libs`
    ixlib_config_major_version=`$IXLIB_CONFIG $ixlib_config_args --version | \
	   sed -e 's,[[^0-9.]],,g' -e 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    ixlib_config_minor_version=`$IXLIB_CONFIG $ixlib_config_args --version | \
	   sed -e 's,[[^0-9.]],,g' -e 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    ixlib_config_micro_version=`$IXLIB_CONFIG $ixlib_config_args --version | \
	   sed -e 's,[[^0-9.]],,g' -e 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
    if test "x$enable_ixlibtest" = "xyes" ; then
      ac_save_CXXFLAGS="$CXXFLAGS"
      ac_save_LIBS="$LIBS"
      CXXFLAGS="$CXXFLAGS $IXLIB_CFLAGS"
      LIBS="$IXLIB_LIBS $LIBS"
dnl
dnl Now check if the installed IXLIB is sufficiently new. (Also sanity
dnl checks the results of ixlib-config to some extent
dnl
      rm -f conf.ixlibtest
      AC_LANG_SAVE
      AC_LANG_CPLUSPLUS
      AC_TRY_RUN([
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ixlib_base.hpp>
#include <ixlib_config.hpp>
using namespace ixion;

int 
main ()
{
  int major, minor, micro;
  char *tmp_version;

  system ("touch conf.ixlibtest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = strdup("$min_ixlib_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_ixlib_version");
     return 1;
   }

  if ((ixlibGetMajorVersion() != $ixlib_config_major_version) ||
      (ixlibGetMinorVersion() != $ixlib_config_minor_version) ||
      (ixlibGetMicroVersion() != $ixlib_config_micro_version))
    {
      printf("\n*** 'ixlib-config --version' returned %d.%d.%d, but version %d.%d.%d\n", 
             $ixlib_config_major_version, $ixlib_config_minor_version, $ixlib_config_micro_version,
             ixlibGetMajorVersion(),ixlibGetMinorVersion(),ixlibGetMicroVersion());
      printf ("*** was found! If the script was correct, then it is best\n");
      printf ("*** to remove the old version of the software. You may also be able to fix the error\n");
      printf("*** by modifying your LD_LIBRARY_PATH enviroment variable, or by editing\n");
      printf("*** /etc/ld.so.conf. Make sure you have run ldconfig if that is\n");
      printf("*** required on your system.\n");
      printf("*** If the script was wrong, set the environment variable IXLIB_CONFIG\n");
      printf("*** to point to the correct copy of ixlib-config, and remove the file config.cache\n");
      printf("*** before re-running configure\n");
    } 
  else if ((IXLIB_MAJOR_VERSION != ixlibGetMajorVersion()) ||
	   (IXLIB_MINOR_VERSION != ixlibGetMinorVersion()) ||
           (IXLIB_MICRO_VERSION != ixlibGetMicroVersion()))
    {
      printf("*** header files (version %d.%d.%d) do not match\n",
	     IXLIB_MAJOR_VERSION,IXLIB_MINOR_VERSION,IXLIB_MICRO_VERSION);
      printf("*** library (version %d.%d.%d)\n",
	     ixlibGetMajorVersion(),ixlibGetMinorVersion(),ixlibGetMicroVersion());
    }
  else
    {
      if ((ixlibGetMajorVersion() > major) ||
         ((ixlibGetMajorVersion() == major) && (ixlibGetMinorVersion() > minor)) ||
         ((ixlibGetMajorVersion() == major) && (ixlibGetMinorVersion() == minor) && (ixlibGetMicroVersion() >= micro)))
      {
        return 0;
       }
     else
      {
        printf("\n*** An old version of the software (%d.%d.%d) was found.\n",
               ixlibGetMajorVersion(), ixlibGetMinorVersion(),ixlibGetMicroVersion());
        printf("*** You need version %d.%d.%d or greater of ixlib. The latest version of\n",
	       major, minor, micro);
        printf("*** the software is always available from http://ixlib.sourceforge.net/.\n");
        printf("***\n");
        printf("*** If you have already installed a sufficiently new version, this error\n");
        printf("*** probably means that the wrong copy of the ixlib-config shell script is\n");
        printf("*** being found. The easiest way to fix this is to remove the old version\n");
        printf("*** of the software, but you can also set the IXLIB_CONFIG environment to point to the\n");
        printf("*** correct copy of ixlib-config. (In this case, you will have to\n");
        printf("*** modify your LD_LIBRARY_PATH enviroment variable, or edit /etc/ld.so.conf\n");
        printf("*** so that the correct libraries are found at run-time))\n");
      }
    }
  return 1;
}
],, no_ixlib=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       CXXFLAGS="$ac_save_CXXFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_ixlib" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$IXLIB_CONFIG" = "no" ; then
       echo "*** The ixlib-config script could not be found."
       echo "*** If the package was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the IXLIB_CONFIG environment variable to the"
       echo "*** full path to ixlib-config."
     else
       if test -f conf.ixlibtest ; then
        :
       else
          echo "*** Could not run test program, checking why..."
          CXXFLAGS="$CXXFLAGS $IXLIB_CFLAGS"
          LIBS="$LIBS $IXLIB_LIBS"
          AC_TRY_LINK([
#include <cstdio>
#include <ixlib_base.hh>
using namespace ixion;
],      [ return ((ixlibGetMajorVersion()) || (ixlibGetMinorVersion()) || (ixlibGetMicroVersion())); ],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding the package or finding the wrong"
          echo "*** version of it. If it is not finding it, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"
          echo "***" ],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means the package was incorrectly"
          echo "*** installed or that you have moved ixlib since it was installed. In the latter"
          echo "*** case, you may want to edit the ixlib-config script: $IXLIB_CONFIG" ])
          CXXFLAGS="$ac_save_CXXFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     IXLIB_CFLAGS=""
     IXLIB_LIBS=""
     ifelse([$3], , :, [$3])
  fi

  AC_LANG_RESTORE

  if test "x$no_ixlib" = "xyes" ; then 
	exit 1
  fi

  AC_SUBST(IXLIB_CFLAGS)
  AC_SUBST(IXLIB_LIBS)
  rm -f conf.ixlibtest
])
