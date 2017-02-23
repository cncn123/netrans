/*
 * string_util.hpp
 *
 *  Created on: Jan 5, 2017
 *      Author: wyd
 */

#ifndef UTILS_STRING_UTIL_HPP_
#define UTILS_STRING_UTIL_HPP_

#include <string>
#include <vector>
#include <string.h>
#include <cassert>
#include <sstream>
#include <stdint.h>
using std::string;
using std::vector;
namespace huawei
{
namespace basics
{
struct string_part
{
private:
	const char* data_;
	size_t length_;
public:
	string_part(): data_(NULL), length_(0) {}
	string_part(const char* _str)
	{
		data_=_str;
		length_=strlen(_str);
	}
	string_part(const char* _str, size_t _len)
	{
		data_ = _str;
		length_= _len;
	}
	const char* data()const
	{
		return data_;
	}
	size_t size()const
	{
		return length_;
	}
	size_t length()const
	{
		return length_;
	}
	bool empty()const
	{
		return length_ == 0;
	}
};

inline vector<string> split(const char *_str, const char*_sep)
{
	vector<string> split_strs;

	int seplen = strlen(_sep);
	string xstr = _str;
	int start_pos =0;
	int find_pos = -1;
	while((find_pos = xstr.find(_sep,start_pos)) != xstr.npos)
	{
		if (find_pos<0)
		{
			break;
		}
		if (find_pos > start_pos)
		{
			split_strs.push_back(xstr.substr(start_pos, find_pos - start_pos));
		}
		start_pos = find_pos + seplen;
	}

	if (start_pos< xstr.length())
	{
		split_strs.push_back(xstr.substr(start_pos));
	}
	return split_strs;
}
inline vector<string> split(const string &_str, const string &_sep)
{
	return split(_str.c_str(), _sep.c_str());
}

inline void split(const char *_str, const char*_sep, vector<string>& _result)
{
	int seplen= strlen(_sep);
	string xstr = _str;
	int start_pos = 0;
	int find_pos = -1;
	while ((find_pos = xstr.find(_sep, start_pos))!=xstr.npos)
	{
		if (find_pos<0)
		{
			break;
		}
		if(find_pos> start_pos)
		{
			_result.push_back(xstr.substr(start_pos, find_pos - start_pos));
		}
		start_pos = find_pos + seplen;
	}
	if (start_pos < xstr.length())
	{
		_result.push_back(xstr.substr(start_pos));
	}
	return;
}

inline void split(const string &_str, const string &_sep, vector<string>& _result)
{
	return split(_str.c_str(),_sep.c_str(),_result);
}

inline string trim(const string &_str)
{
	int start =0;
	int end = _str.length()-1;
	while(start< _str.length())
	{
		if(_str[start] == '\t' || _str[start] == ' ' || _str[start] == '\r' || _str[start] == '\n')
		{
			++start;
		}
		else
		{
			break;
		}
	}
	while (end >=0 )
	{
		if (_str[end] == '\t' || _str[end] == ' ' || _str[end] == '\r' || _str[end] == '\n')
		{
			--end;
		}
		else
		{
			break;
		}
	}
	if (start <= end )
	{
		return _str.substr(start, end - start +1);
	}
	else
	{
		return "";
	}
}

inline string upper_case(const string &_str)
{
	string upstr = _str;
	for (int i=0; i< upstr.size();i++)
	{
		if (upstr[i] <= 122 && upstr[i] >=97)
		{
			upstr[i]-=32;
		}
	}
	return upstr;
}
inline void upper_case(char* _c)
{
	if (_c[0] >=97 && _c[0] <=122)
	{
		_c[0] -=32;
	}
}
inline bool start_with(const string& _str, const char* _prefix)
{
	return ((_str.length() >= _str.length()) && (memcmp(_str.data(),_prefix, strlen(_prefix))==0));
}
inline uint64_t read_num(const string& _from)
{
	std::stringstream stream(_from);
	uint64_t ret;
	stream >> ret;
	assert(stream);
	return ret;
}

}
}


#endif /* UTILS_STRING_UTIL_HPP_ */
