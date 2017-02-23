#-I/home/parallels/mylibs/boost_1_53/include -I/home/parallels/mylibs/icu_50_1_2/include
AM_CPPFLAGS=-O0  -I../ -I../../ -I../../boost/include 
AM_CXXFLAGS=-O0  -L../../boost/lib -L../../icu/lib

noinst_LTLIBRARIES=libne_trans.la
libne_trans_la_SOURCES=ne_recognizer_resource.cpp ne_recognizer.cpp

bin_PROGRAMS=netrans_test
netrans_test_SOURCES=netrans_test.cpp
netrans_test_LDADD=-lboost_regex -licuuc -licui18n -licudata libne_trans.la ../../seg_utils/libseg_utils.la ../../utils/libutils.la