/*
 * wchar_converter.h
 *
 *  Created on: Nov 17, 2016
 *      Author: parallels
 */

#ifndef WCHAR_CONVERTER_H_
#define WCHAR_CONVERTER_H_

#include <string>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <iconv.h>
#include <string.h>

using std::string;
using std::wstring;

class unicode_converter {
public:
	unicode_converter();
	virtual ~unicode_converter();
	bool utf8_to_wchar(const string& _u8str, wstring& _wstr);//convert utf8 to wchar
	bool wchar_to_utf8(const wstring& _wstr, string& _u8str);//convert wchar to utf8
	bool realloc_buf(const int _len);//reallocate buffer
private:
	char* buf_;
	int buf_len_;
};

#endif /* WCHAR_CONVERTER_H_ */
