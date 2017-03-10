/*
 * ne_formatter.hpp
 *
 *  Created on: Dec 27, 2016
 *      Author: wyd
 */

#ifndef PREPROCESS_NETRANS_NE_FORMATTER_HPP_
#define PREPROCESS_NETRANS_NE_FORMATTER_HPP_
#include <ne_types.hpp>
#include <boost/regex.hpp>
#include <string>
#include <cwchar>
#include <sstream>
#include "common_utils/log_util.hpp"
#include "seg_utils/charactor_handler.h"
#include "utils/unicode_converter.h"
using std::wstring;
namespace huawei{
namespace eai {
#include<iostream>
#pragma pack(push)
#pragma pack(2)

static const char* NE_DATE_FORMATTER_TAG = "date_formatter";

static const int max_field_index = 8;
static const int default_base = 10;
enum date_format_index {
	ET_DF_YEAR = 0,
	ET_DF_MONTH,
	ET_DF_DAY
};

enum time_format_index {
	ET_TF_HOUR = 0,
	ET_TF_MIN,
	ET_TF_SEC
};

inline int date_wstr2int(const wchar_t* _beg, const wchar_t* _end)
{
	//using namespace huawei::lips;

	uint32_t len = _end -_beg;
	charactor_handler charactor_handle;
	if(charactor_handle.is_all_chn_digit(_beg,len))
	{
		std::cout<<"chn"<<"\t"<<_end - _beg<<"\n";
		long long int result;
		if (charactor_handle.get_chn_value(_beg, len, &result)){
			std::cout<<"result= "<<result<<std::endl;
			return result;
		}
	}
	else if(charactor_handle.is_all_digit(_beg, len))
	{
		std::cout<<"_beg len "<<_end - _beg<<"\n";
		return charactor_handle.get_value(_beg, len);
	}
	return 0;
}

inline int time_wstr2int(const wchar_t* _beg, const wchar_t* _end)
{
	//using namespace huawei::lips;

	uint32_t len = _end -_beg;
	charactor_handler charactor_handle;
	if(charactor_handle.is_all_chn_digit(_beg,len))
	{
		std::cout<<"chn"<<"\t"<<_end - _beg<<"\n";
		long long int result;
		if (charactor_handle.get_chn_value(_beg, len, &result)){
			std::cout<<"result= "<<result<<std::endl;
			return result;
		}
	}
	else if(charactor_handle.is_all_digit(_beg, len))
	{
		std::cout<<"_beg len "<<_end - _beg<<"\n";
		return charactor_handle.get_value(_beg, len);
	}
	return 0;
}

class type_formatter
{
public:
	type_formatter(const wchar_t* _pattern):pattern_(_pattern),sent_(NULL),start_pos_(0),sentlen_(0)
    {
		init_field_index();
    };
	type_formatter(const wstring& _pattern):pattern_(_pattern),sent_(NULL),start_pos_(0),sentlen_(0)
    {
		init_field_index();
	};
	virtual ~type_formatter() {};
	virtual ne_non_trans* format()=0;
	virtual bool search(const wchar_t* _sent, const int& _sentlen, const int& _start)
	{
		const wchar_t* match_start =_sent + _start;
		const wchar_t* match_end = _sent + _sentlen;
		bool found = boost::regex_search(match_start, match_end, wmatch_, pattern_);
		sent_= _sent;
		sentlen_=_sentlen;
		return found;
	};
	virtual int get_match_start()
	{
		return wmatch_[0].first - sent_;
	}
	virtual int get_match_len()
	{
		return wmatch_[0].second - wmatch_[0].first;
	}
protected:
	int8_t field_index_[max_field_index];
	boost::wregex pattern_;
	const wchar_t* sent_;
	int sentlen_;
	int start_pos_;
	boost::match_results<const wchar_t*> wmatch_;
	void init_field_index()
	{
		for (int i = 0; i< max_field_index; ++i)
		{
			field_index_[i]=-1;
		}
	}

};

class date_formatter : public type_formatter
{
public:
	date_formatter(const wchar_t* _pattern):type_formatter(_pattern){};
	date_formatter(const wstring& _pattern):type_formatter(_pattern){};
	~date_formatter(){};
	void set_format(int _year_grp_id, int _month_grp_id, int _day_grp_id)
	{
		std::cout<<"_year_grp_id= "<<_year_grp_id<<std::endl;
		std::cout<<"_month_grp_id= "<<_month_grp_id<<std::endl;
		std::cout<<"_day_grp_id= "<<_day_grp_id<<std::endl;
		if(_year_grp_id >= 0 && _year_grp_id< max_field_index)
			field_index_[_year_grp_id] = ET_DF_YEAR;
		if(_month_grp_id >= 0 && _month_grp_id< max_field_index)
			field_index_[_month_grp_id] = ET_DF_MONTH;
		if(_day_grp_id >= 0 && _day_grp_id< max_field_index)
			field_index_[_day_grp_id] = ET_DF_DAY;
	}

	ne_non_trans* format()
	{
		//wrong initial
		int year = -1;
		int mon = -1;
		int day = -1;
		std::cout<<"wmatch_size= "<<wmatch_.size()<<std::endl;
		int j = 1;
		for (int i=1; i<wmatch_.size(); ++i)// wrong i
		{

			while((int)field_index_[j] == -1 && j < max_field_index){
				j++;
			}
			std::cout<<"i= "<<i<< "\t"<<"j= "<<j<<" "<<"index "<<(int)field_index_[j]<<"\n";
			string test;
			wstring test_1 = wmatch_[i];
			unicode_converter uc;
			uc.wchar_to_utf8(test_1, test);
			std::cout<<"test:"<<test<<"\n";
//			if(strcmp(test,"半"){
//				wmatch_[i] = L"30";
//			}

			if(field_index_[j] == ET_DF_YEAR)
			{
				year = date_wstr2int(wmatch_[i].first, wmatch_[i].second);
				std::cout<<"year len = "<<wmatch_[i].second-wmatch_[i].first<<"\n";
				std::cout<<"year = "<<year<<"\n";
			}
			else if(field_index_[j] == ET_DF_MONTH)
			{
				mon = date_wstr2int(wmatch_[i].first, wmatch_[i].second);
				std::cout<<"mon len = "<<wmatch_[i].second-wmatch_[i].first<<"\n";
				std::cout<<"mon = "<<mon<<"\n";
			}
			else if(field_index_[j] == ET_DF_DAY)
			{
				day = date_wstr2int(wmatch_[i].first, wmatch_[i].second);
				std::cout<<"day len = "<<wmatch_[i].second-wmatch_[i].first<<"\n";
				std::cout<<"day = "<<day<<"\n";
			}
			j++;
		}
//wrong year

		if (year<0 && mon<0 && day<0)
		{
			return NULL;
		}
		if (year<0){
			year=NULL;
		}
		if (mon<0) {
			mon=NULL;
		}
		if (day<0) {
			day=NULL;
		}
		uint16_t start = wmatch_[0].first - sent_;
		uint16_t len = wmatch_[0].second - wmatch_[0].first;
#ifdef __HW_DEBUG__
		LOG_INFO(NE_DATE_FORMATTER_TAG, "DATE: y="<<year<< "; m="<<mon<<";d="<<day<<";start="<<start<<"; len"<<len);
#endif
		return new ne_date(start, len, year, mon, day);
	}
};

class time_formatter : public type_formatter
{
public:
	time_formatter(const wchar_t* _pattern) : type_formatter(_pattern) {};
	time_formatter(const wstring& _pattern) : type_formatter(_pattern) {};
	~time_formatter() {};
	void set_format(int _hour_grp_id, int _min_grp_id, int _sec_grp_id)
	{
		std::cout<<"_hour_grp_id= "<<_hour_grp_id<<std::endl;
		std::cout<<"_min_grp_id= "<<_min_grp_id<<std::endl;
		std::cout<<"_sec_grp_id= "<<_sec_grp_id<<std::endl;
		if(_hour_grp_id>= 0 && _hour_grp_id<max_field_index)
			field_index_[_hour_grp_id]= ET_TF_HOUR;
		if(_min_grp_id>= 0 && _min_grp_id<max_field_index)
			field_index_[_min_grp_id]= ET_TF_MIN;
		if(_sec_grp_id>= 0 && _sec_grp_id<max_field_index)
			field_index_[_sec_grp_id]= ET_TF_SEC;
	}

	ne_non_trans* format()
	{
		int hour = -1;
		int min = -1;
		int sec = -1;
		int j = 1;
		std::cout<<"wmatch_size= "<<wmatch_.size()<<std::endl;
		for(int i = 1; i<wmatch_.size(); ++i)
		{
			while((int)field_index_[j] == -1 && j < max_field_index){
				j++;
			}
			std::cout<<"i= "<<i<< "\t"<<"j= "<<j<<" "<<"index "<<(int)field_index_[j]<<"\n";
			string test;
			wstring test_1 = wmatch_[i];
			unicode_converter uc;
			uc.wchar_to_utf8(test_1, test);
			std::cout<<"test:"<<test<<"\n";
			if (field_index_[j] == ET_TF_HOUR)
			{
				hour = time_wstr2int(wmatch_[i].first, wmatch_[i].second);
				std::cout<<"hour len = "<<wmatch_[i].second-wmatch_[i].first<<"\n";
				std::cout<<"hour = "<<hour<<"\n";
			}
			else if (field_index_[j] == ET_TF_MIN)
			{
				min = time_wstr2int(wmatch_[i].first, wmatch_[i].second);
				std::cout<<"min len = "<<wmatch_[i].second-wmatch_[i].first<<"\n";
				std::cout<<"min = "<<min<<"\n";
			}
			if (field_index_[j] == ET_TF_SEC)
			{
				sec = time_wstr2int(wmatch_[i].first, wmatch_[i].second);
				std::cout<<"sec len = "<<wmatch_[i].second-wmatch_[i].first<<"\n";
				std::cout<<"sec = "<<sec<<"\n";
			}
			j++;
		}
		if (hour<0 && min<0 && sec<0)
		{
			return NULL;
		}
		uint16_t start= wmatch_[0].first - sent_;
		uint16_t len = wmatch_[0].second - wmatch_[0].first;
		if(hour<0){
			hour=NULL;
		}
		if(min<0){
			min=NULL;
		}
		if(sec<0){
			sec=NULL;
		}
#ifdef __HW_DEBUG__
		LOG_INFO(NE_DATE_FORMATTER_TAG, "TIME: h = "<< hour << "; m="<<min<<"; s="<< sec<<"; start ="<< start <<";len ="<< len);
#endif
		return new ne_time(start, len, hour, min, (float)sec);
	}
};

#pragma pack(pop)

}/*end of namespace eai */
}/*end of namespace huawei*/





#endif /* PREPROCESS_NETRANS_NE_FORMATTER_HPP_ */
