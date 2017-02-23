/*
 * ne_recognizer_resource.cpp
 *
 *  Created on: Dec 28, 2016
 *      Author: parallels
 */
#include "ne_recognizer_resource.h"
#include "api/decoder_json.h"
#include "utils/unicode_converter.h"
#include "common_utils/file_util.hpp"
#include "common_utils/log_util.hpp"
#include "common_utils/string_util.hpp"
#include "rapidjson/document.h"
#include <boost/algorithm/string.hpp>
#include <string>
#include <fstream>
#include <iostream>
using std::ifstream;
using std::string;
using namespace std;
namespace huawei {
namespace eai{
static const char* NE_REC_RES_TAG = "ne_reconginzer_resource";
const char* PATTERN_FILE_NAME = "pattern.txt";
const char* PF_SPLIT ="\t";
static const wchar_t* CN_DIGIT_LABEL = L"#InCnDigit#";
static const wchar_t* CN_DIGIT = L"一|二|三|四|五|六|七|八|九|十|零|壹|贰|两|叁|肆|伍|陆|柒|捌|玖";
type_recognizer::type_recognizer(ne_type _type) : type_(_type)
{

}

type_recognizer::~type_recognizer()
{
	for (int i =0; i < type_pattern_.size(); ++i)
	{
		if(NULL != type_pattern_[i])
		{
			delete type_pattern_[i];
			type_pattern_[i] = NULL;
		}

	}
}

bool type_recognizer::recognize_sent(const wchar_t* _sent, const int _sent_len, ne_non_trans** _ne_output, int& _unit_left_in_output)
{
	int start_pos = 0;
	int output_offset = 0;
	while (start_pos < _sent_len)
	{
		int best_match_idx = -1;
		int min_start = _sent_len;
		int max_match_len = -1;
		for(int i = 0; i< type_pattern_.size(); i++)
		{
			if (type_pattern_[i]->search(_sent, _sent_len, start_pos))
			{
				//cout<< "regex[i]=" << i << endl;
				int match_start = type_pattern_[i]->get_match_start();
				int match_len = type_pattern_[i]->get_match_len();
				if (min_start > match_start)
				{
					min_start = match_start;
					max_match_len = match_len;
					best_match_idx = i;
				}
				else if (min_start == match_start)
				{
					if (match_len > max_match_len)
					{
						max_match_len = match_len;
						best_match_idx = i;
					}
				}
			}
		}

		cout<<"best_match_idx="<<best_match_idx<<endl;
		if(best_match_idx != -1){
			cout<<"best_match_pattern="<< type_pattern_[best_match_idx]->get_match_start() <<endl;
			cout<<"best_match_length="<<type_pattern_[best_match_idx]->get_match_len() <<endl;
		}
		//wirte on match
		if (best_match_idx >= 0)
		{
			ne_non_trans* ne = type_pattern_[best_match_idx]->format();
			if (NULL != ne && _unit_left_in_output > 0)
			{
				_ne_output[output_offset] = ne;
				//cout<< ne << endl;
				output_offset++;
				_unit_left_in_output--;


			}
			else if (_unit_left_in_output <= 0)
			{
				LOG_INFO(NE_REC_RES_TAG, "type_recognizer::recognize_sent : insufficient output buff");
				return false;
			}
			else
			{
				LOG_INFO(NE_REC_RES_TAG, "type_recognizer::recognize_sent : bad en format");
			}
			start_pos = min_start + max_match_len;
		}
		else
		{
			return false;
		}
	}
	return true;
}

ne_recognizer_resource::ne_recognizer_resource()
{

}

ne_recognizer_resource::~ne_recognizer_resource()
{

}

ne_recognizer_resource::ne_recognizer_resource(const char* _ne_res_path,
		const char* _lang) : ne_res_path_(_ne_res_path), lang_(_lang)
{

}
bool ne_recognizer_resource::reload_resource()
{
	using namespace huawei::basics;
	using namespace rapidjson;
	unicode_converter uc;
	//read ne_res_path
	string ne_pattern_path = ne_res_path_;
	ne_pattern_path += "/";
	ne_pattern_path += lang_;
	ne_pattern_path += "/";
	ne_pattern_path += PATTERN_FILE_NAME;

	if (!file_exist_not_empty(ne_pattern_path.c_str()))
	{
		LOG_FATAL(NE_REC_RES_TAG, "ne res : " << ne_pattern_path << "not found.");
		return false;
	}
	ifstream ifs;
	ifs.open(ne_pattern_path.c_str());
	if (!ifs.is_open())
	{
		LOG_FATAL(NE_REC_RES_TAG, "ne res : " << ne_pattern_path << "open failure.");
		return false;
	}

	type_recognizers_.reserve(ET_NE_NON_TRANS);
	for (int i = 0; i <= ET_NE_NON_TRANS; ++i)
	{
		type_recognizers_.push_back(type_recognizer((ne_type)(i)));
	}
	string pattern_formatter;
	int success_pattern_formatter_count = 0;
	while (getline(ifs, pattern_formatter))
	{
		if (pattern_formatter.empty())
		{
			continue;
		}
		if (pattern_formatter[0] == '#')
		{
			continue;
		}
		vector<string> pf_pair;
		split(pattern_formatter, PF_SPLIT, pf_pair);
		if (pf_pair.size() !=2 )
		{
			LOG_INFO(NE_REC_RES_TAG, "bad pattern format : " << pattern_formatter);
			continue;
		}
		wstring wpattern;
		uc.utf8_to_wchar(pf_pair[0], wpattern);
		//wcout<<wpattern<<endl;
		boost::replace_all(wpattern, CN_DIGIT_LABEL, CN_DIGIT);
		Document format_json(kObjectType);
		format_json.Parse(pf_pair[1].c_str());

		if (!format_json.HasMember(FT_NE_TYPE_LABEL))
		{
			continue;
		}

		ne_type pf_type = str2ne_type(format_json[FT_NE_TYPE_LABEL].GetString());
		//std::cerr << format_json[FT_NE_TYPE_LABEL].GetString() << std::endl;
		//std::cerr << pf_type << std::endl;
		type_formatter* tformat = NULL;
		if (ET_NE_DATE == pf_type)
		{
			date_formatter* fmt = new date_formatter(wpattern);
			int year = -1;
			if (format_json.HasMember(FT_NE_DATA_YEAR_LABEL))
			{
				year = format_json[FT_NE_DATA_YEAR_LABEL].GetInt();
			}
			int month = -1;
			if (format_json.HasMember(FT_NE_DATA_MONTH_LABEL))
			{
				month = format_json[FT_NE_DATA_MONTH_LABEL].GetInt();
			}
			int day = -1;
			if (format_json.HasMember(FT_NE_DATA_DAY_LABEL))
			{
				day = format_json[FT_NE_DATA_DAY_LABEL].GetInt();
			}
			if (year >= 0 || month >= 0 || day >= 0)
			{
				fmt->set_format(year, month, day);
				tformat = fmt;
			}
		}
		else if (ET_NE_TIME == pf_type)
		{
			time_formatter* fmt = new time_formatter(wpattern);
			int hour = -1;
			if (format_json.HasMember(FT_NE_TIME_HOUR_LABEL))//
			{
				hour = format_json[FT_NE_TIME_HOUR_LABEL].GetInt();
			}
			int min = -1;
			if (format_json.HasMember(FT_NE_TIME_MINUTE_LABEL))//
			{
				min = format_json[FT_NE_TIME_MINUTE_LABEL].GetInt();
			}
			int sec = -1;
			if (format_json.HasMember(FT_NE_TIME_SECOND_LABEL))//
			{
				sec = format_json[FT_NE_TIME_SECOND_LABEL].GetInt();
			}
			if (hour >= 0 || min >= 0 || sec >= 0)
			{
				fmt->set_format(hour, min, sec);
				tformat = fmt;
			}
		}
		else if (ET_NE_CURRENCY == pf_type)
		{

		}
		else if (ET_NE_LCW == pf_type)
		{

		}
		else if (ET_NE_NON_TRANS == pf_type)
		{

		}
		if (NULL != tformat)
		{
			type_recognizers_[pf_type].push_pattern(tformat);
			success_pattern_formatter_count ++;
		}
	}

	LOG_INFO( NE_REC_RES_TAG , "total pattern : " << success_pattern_formatter_count);
	return true;
}

ne_recognizer_dual_resource::ne_recognizer_dual_resource(const char * _ne_res_path, const char* _lang)
	: flag_(LEFT), left_res_(_ne_res_path, _lang), right_res_(_ne_res_path, _lang)
{

}

ne_recognizer_dual_resource::~ne_recognizer_dual_resource()
{

}

void* ne_recognizer_dual_resource::create_ne_dual_resource(const char* _ne_res_path, const char* _lang)
{
	ne_recognizer_dual_resource* ne_res = new ne_recognizer_dual_resource(_ne_res_path, _lang);
	return ne_res;
}

void ne_recognizer_dual_resource::release_ne_dual_resource(void*& _res)
{
	if (NULL != _res)
	{
		ne_recognizer_resource* ne_res = (ne_recognizer_resource*)_res;
		delete ne_res;
		_res = NULL;
	}
}


} /*namespace eai */

} /*namespace huawei */



