
AC_INIT(httpclient, 0.0.1, veleba@novalighting.cz)

AM_INIT_AUTOMAKE(foreign -Wall)

AC_CONFIG_SRCDIR([src/httpclient/httpclient.cc])

AC_PREREQ(2.50)

AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL

### define test-for-header macro
# $1 = header file name (i.e. "mdbg.h")
# function fids out the header or terminates configure script
AC_DEFUN([TEST_HEADER],[
FOUND="no"
AC_CHECK_HEADER($1,FOUND="yes")
if test "$FOUND" = "no"; then
  # try search dirs
  for SRCHDIR in \
      `pwd` \
      $HOME/libs/include \
      $HOME/cvs/libs/include \
      $HOME/CVS/libs/include \
      /usr/local/include \
      /usr/include/mysql \
      ;
  do
    AC_MSG_CHECKING(for $1 ($SRCHDIR))
    AC_TRY_CPP([#include "$SRCHDIR/$1"],FOUND="yes")
    AC_MSG_RESULT($FOUND)
    if test "$FOUND" = "yes"; then
      # add path to env
      CPPFLAGS="$CPPFLAGS -I$SRCHDIR"
      break
    fi
  done
fi
# check for result
if test "$FOUND" = "no"; then
  AC_MSG_ERROR(*** Cannot find $1 header!!! ***)
fi
])
### end macro


### define test-for-lib macro
# $1 = library file name (i.e. "mdbg")
# $2 = test function to link (i.e. "MLOG_LOG")
# $3 = other libs needed to link against lib in $1
# function fids out the library or terminates configure script
AC_DEFUN([TEST_LIB],[
FOUND="no"
AC_CHECK_LIB($1,$2,FOUND="yes"; LIBS="-l$1 $LIBS",,$3)
if test "$FOUND" = "no"; then
  # try search dirs
  SAVED_LIBS=$LIBS
  for SRCHDIR in \
      `pwd` \
      $HOME/libs/lib \
      $HOME/cvs/libs/lib \
      $HOME/CVS/libs/lib \
      /usr/local/lib \
          ;
  do
    AC_MSG_CHECKING(for $2 in -l$1 ($SRCHDIR))
    LIBS="-l$1 $SAVED_LIBS -L$SRCHDIR $3"
    AC_TRY_LINK_FUNC($2, FOUND="yes")
    AC_MSG_RESULT($FOUND)
    if test "$FOUND" = "yes"; then
      # add path to env
      LIBS="-l$1 $SAVED_LIBS -L$SRCHDIR"
      break
    fi
  done
fi
# check for result
if test "$FOUND" = "no"; then
  AC_MSG_ERROR(*** Cannot find $1 library!!! ***)
fi
])
### end macro

AC_LANG_CPLUSPLUS
TEST_HEADER(curl/curl.h)
TEST_LIB(curl, curl_global_init)

AC_SUBST(CXXEXTRAFLAGS)

AC_OUTPUT( \
    Makefile
    src/httpclient/Makefile
)
