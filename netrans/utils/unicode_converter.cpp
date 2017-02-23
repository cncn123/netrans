/*
 * wchar_converter.cpp
 *
 *  Created on: Nov 17, 2016
 *      Author: parallels
 */

#include "unicode_converter.h"
#define INIT_BUF_LEN (8192)

const char *WCHAR = "WCHAR_T";
const char *UTF8 = "UTF-8";

unicode_converter::unicode_converter() {
	buf_ = (char*) calloc(INIT_BUF_LEN, sizeof(char));
	buf_len_ = INIT_BUF_LEN;
}

unicode_converter::~unicode_converter() {
	if (NULL == buf_)
	{
		free (buf_);
		buf_ = NULL;
	}
}

bool unicode_converter::utf8_to_wchar(const string& _u8str, wstring& _wstr) {

	if (_u8str.length() > buf_len_ / sizeof(wchar_t))
	{
		realloc_buf(_u8str.length() * sizeof(wchar_t));
	}
	char *iconv_in = const_cast<char*>(_u8str.c_str());
	char *iconv_out= buf_;
	size_t srclen = _u8str.length();
	size_t dstlen = buf_len_;

//	fprintf(stderr,"in: %s\n",src_1);
	iconv_t conv = iconv_open(WCHAR, UTF8);
	int ret = iconv(conv, &iconv_in, &srclen, &iconv_out, &dstlen);
	iconv_close(conv);
	//printf("ret1=%d", ret);
	if (ret < 0)
	{
		return false;
	}
//	fprintf(stderr,"out: %s\n",dst_1);
	_wstr.assign((wchar_t*)buf_, (iconv_out - buf_)/sizeof(wchar_t));
	return true;


}

bool unicode_converter::wchar_to_utf8(const wstring& _wstr, string& _u8str) {
	if (_wstr.length() * 4 > buf_len_  )
	{
		realloc_buf(_wstr.length() * sizeof(char));
	}
	char *iconv_in = (char *)(_wstr.c_str());
	char *iconv_out= buf_;
	//printf("_wstr length=%d",_wstr.length());
	size_t srclen = _wstr.length()*sizeof(wchar_t);
	size_t dstlen = buf_len_;

	//	fprintf(stderr,"in: %s\n",src_1);
	iconv_t conv = iconv_open(UTF8, WCHAR);
	int ret = iconv(conv, &iconv_in, &srclen, &iconv_out, &dstlen);
	//printf("distance=%d\n",(iconv_out - buf_)/sizeof(char));
	iconv_close(conv);
	//printf("ret2=%d", ret);
	if (ret < 0)
	{
		return false;
	}
	//	fprintf(stderr,"out: %s\n",dst_1);

	_u8str.assign((char*)buf_, (iconv_out - buf_)/sizeof(char));
	return true;



}

bool unicode_converter::realloc_buf(const int _new_buf_len) {
	if (_new_buf_len > buf_len_)
	{
		buf_len_ = _new_buf_len;//
	}
	buf_ = (char*) calloc(_new_buf_len, sizeof(char));
	if (NULL == buf_)
	{
		buf_len_ = 0;
		return false;
	}
	buf_len_ = _new_buf_len;
	return true;
}
