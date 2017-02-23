/*
 * ne_recognizer_resource.h
 *
 *  Created on: Dec 28, 2016
 *      Author: parallels
 */

#ifndef PREPROCESS_NETRANS_NE_RECOGNIZER_RESOURCE_H_
#define PREPROCESS_NETRANS_NE_RECOGNIZER_RESOURCE_H_
#include <vector>
#include <boost/regex.hpp>
#include <string>

#include "../../utils/unicode_converter.h"
#include "preprocess/netrans/ne_types.hpp"
#include "preprocess/netrans/ne_formatter.hpp"
//#include "seg_utils/unicode_converter.h"
using std::vector;
using boost::wregex;
using std::string;
namespace huawei {
namespace eai {

class type_recognizer
{
public:
	type_recognizer(ne_type _type);
	virtual ~type_recognizer();
	bool recognize_sent(const wchar_t* _sent, const int _sent_len, ne_non_trans** _ne_output, int& _unit_left_in_output);
	void push_pattern(type_formatter*& _reg)
	{
		type_pattern_.push_back(_reg);
	}
	int size()
	{
		return type_pattern_.size();
	}
private:
	vector<type_formatter*> type_pattern_;
	ne_type type_;
};

class ne_recognizer_resource {
public:
	ne_recognizer_resource();
	ne_recognizer_resource(const char* _ne_res_path, const char* _lang);
	virtual ~ne_recognizer_resource();
	vector<type_recognizer>& get_recognizers()
	{
		return type_recognizers_;
	}
	void set_res_path(const char* _ne_res_path, const char* _lang)
	{
		ne_res_path_=_ne_res_path;
		lang_=_lang;
	}
	bool reload_resource();

private:
	vector<type_recognizer> type_recognizers_;
	string ne_res_path_;
	string lang_;
	static inline ne_type str2ne_type(const char* _type_str)
	{
		if(memcmp(_type_str, FT_NE_DATA_VALUE, FT_NE_DATE_VALUE_LEN)==0)
		{
			return ET_NE_DATE;
		}
		else if (memcmp(_type_str, FT_NE_TIME_VALUE, FT_NE_TIME_VALUE_LEN)==0)
		{
			return ET_NE_TIME;
		}
		else if (memcmp(_type_str, FT_NE_CURRENCY_VALUE, FT_NE_CURRENCY_VALUE_LEN)==0)
		{
			return ET_NE_CURRENCY;
		}
		else if (memcmp(_type_str, FT_NE_LWC_VALUE, FT_NE_LWC_VALUE_LEN)==0)
		{
			return ET_NE_LCW;
		}
		else
		{
			return ET_NE_NON_TRANS;
		}
	}
};

enum ne_recoginizer_res_flag {
	LEFT = 0, RIGHT
};

class ne_recognizer_dual_resource {
public:
	ne_recognizer_dual_resource(const char* _ne_res_path, const char* _lang);
	virtual ~ne_recognizer_dual_resource();
	static void* create_ne_dual_resource(const char* _ne_res_path, const char* _lang);
	static void release_ne_dual_resource(void*& _res);
	ne_recognizer_resource& get_ne_res()
	{
		return flag_ == LEFT ? left_res_ : right_res_;
	}
	void reload_resource()
	{
		if (LEFT == flag_)
		{
			right_res_.reload_resource();
			flag_ = RIGHT;
		}
		else
		{
			left_res_.reload_resource();
			flag_ = LEFT;
		}
	}
private:
	ne_recognizer_resource left_res_;
	ne_recognizer_resource right_res_;
	ne_recoginizer_res_flag flag_;

};
} /*namespace eai* */
} /*namespace huawei */

#endif /* PREPROCESS_NETRANS_NE_RECOGNIZER_RESOURCE_H_ */
