
AM_CXXFLAGS = -Werror -Wall -O2 -D_FILE_OFFSET_BITS=64 -g ${CXXEXTRAFLAGS} -I../../include

lib_LTLIBRARIES = libhttpclient.la

noinst_PROGRAMS = test

libhttpclient_la_SOURCES = \
    error.cc \
    httpclient.cc \
    message.cc \
    request.cc \
    response.cc

library_includedir = $(includedir)/httpclient

library_include_HEADERS = \
    ../../include/httpclient/error.h \
    ../../include/httpclient/httpclient.h \
    ../../include/httpclient/message.h \
    ../../include/httpclient/request.h \
    ../../include/httpclient/response.h

test_sources = \
    test.cc

test_LDADD = libhttpclient.la
