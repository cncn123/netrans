#-I/home/parallels/mylibs/boost_1_53/include -I/home/parallels/mylibs/icu_50_1_2/include
AM_CPPFLAGS=-O0  -I../ -I../../ -I../../boost/include -I../../icu/include
AM_CXXFLAGS=-O0 -L/home/parallels/mylibs/boost_1_53/lib -L/home/parallels/mylibs/icu_50_1_2/lib

noinst_LTLIBRARIES=libne_trans.la
libne_trans_la_SOURCES=ne_recognizer_resource.cpp ne_recognizer.cpp

bin_PROGRAMS=netrans_test
netrans_test_SOURCES=netrans_test.cpp
netrans_test_LDADD=-lnoost_regex -larkseg libne_trans.la