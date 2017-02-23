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
using std::wstring;
namespace huawei{
namespace eai {

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
		return charactor_handle.get_chn_value(_beg, len);
	}
	else if(charactor_handle.is_all_digit(_beg, len))
	{
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
		if(_year_grp_id >= 0 && _year_grp_id< max_field_index)
			field_index_[_year_grp_id] = ET_DF_YEAR;
		if(_month_grp_id >= 0 && _month_grp_id< max_field_index)
			field_index_[_month_grp_id] = ET_DF_MONTH;
		if(_day_grp_id >= 0 && _day_grp_id< max_field_index)
			field_index_[_day_grp_id] = ET_DF_DAY;
	}

	ne_non_trans* format()
	{
		int year = -1;
		int mon = -1;
		int day = -1;
		for (int i=0; i<wmatch_.size(); ++i)
		{
			if(field_index_[i] == ET_DF_YEAR)
			{
				year = date_wstr2int(wmatch_[i].first, wmatch_[i].second);
			}
			else if(field_index_[i] == ET_DF_MONTH)
			{
				mon = date_wstr2int(wmatch_[i].first, wmatch_[i].second);
			}
			else if(field_index_[i] == ET_DF_DAY)
			{
				day = date_wstr2int(wmatch_[i].first, wmatch_[i].second);
			}
		}

		if (year<0 && mon<0 && day<0)
		{
			return NULL;
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
		for(int i = 0; i<wmatch_.size(); ++i)
		{
			if (field_index_[i] == ET_TF_HOUR)
			{
				hour = date_wstr2int(wmatch_[i].first, wmatch_[i].second);
			}
			else if (field_index_[i] == ET_TF_MIN)
			{
				min = date_wstr2int(wmatch_[i].first, wmatch_[i].second);
			}
			if (field_index_[i] == ET_TF_SEC)
			{
				sec = date_wstr2int(wmatch_[i].first, wmatch_[i].second);
			}
		}
		if (hour<0 && min<0 && sec<0)
		{
			return NULL;
		}
		uint16_t start= wmatch_[0].first - sent_;
		uint16_t len = wmatch_[0].second - wmatch_[0].first;;

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
