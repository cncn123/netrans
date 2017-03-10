/*
 * ne_types.hpp
 *
 *  Created on: Dec 22, 2016
 *      Author: wyd
 */

#ifndef SRC_MAIN_CPP_PREPROCESS_NETRANS_NE_TYPES_HPP_
#define SRC_MAIN_CPP_PREPROCESS_NETRANS_NE_TYPES_HPP_

#include<stdint.h>
namespace huawei{
namespace eai{

#pragma pack(push)
#pragma pack(2)

static const char* FT_NE_TYPE_LABEL = "TYPE";

static const char* FT_NE_DATA_VALUE = "DATE";
static const int FT_NE_DATE_VALUE_LEN = 4;
static const char* FT_NE_DATA_YEAR_LABEL= "YEAR";
static const char* FT_NE_DATA_MONTH_LABEL="MONTH";
static const char* FT_NE_DATA_DAY_LABEL="DAY";

static const char* FT_NE_TIME_VALUE = "TIME";
static const int FT_NE_TIME_VALUE_LEN = 4;
static const char* FT_NE_TIME_MINUTE_LABEL= "MINUTE";
static const char* FT_NE_TIME_HOUR_LABEL="HOUR";
static const char* FT_NE_TIME_SECOND_LABEL="SECOND";

static const char* FT_NE_CURRENCY_VALUE = "CURRENCY";
static const int FT_NE_CURRENCY_VALUE_LEN = 8;
static const char* FT_NE_CURRENCY_VALUE_LABEL= "VALUE";

static const char* FT_NE_LWC_VALUE = "LCW";
static const int FT_NE_LWC_VALUE_LEN=3;

static const char* FT_NE_NON_TRANS_VALUE = "NON_TRANS";
static const int FT_NE_NON_TRANS_VALUE_LEN= 9;



enum ne_type {
	    ET_NE_DATE = 0,
        ET_NE_TIME,
		ET_NE_CURRENCY,
		ET_NE_LCW,
		ET_NE_NON_TRANS
};

enum ne_currency_type_name {
	    ET_NE_CUR_MOP = 1,
	    ET_NE_CUR_HKD,
		ET_NE_CUR_THP,
		ET_NE_CUR_SGD,
		ET_NE_CUR_CNY,
};

class ne_non_trans {
public:
	    uint16_t start_;
	    uint16_t length_;
	    ne_type type_;
	    ne_non_trans(ne_type _type = ET_NE_NON_TRANS):start_(0),length_(0),type_(_type){};
	    ne_non_trans(const uint16_t& _start, const uint16_t& _len, ne_type _type=ET_NE_NON_TRANS):
	    	start_(_start),length_(_len),type_(_type){};
	    //void print()=0;
};

class ne_date : public ne_non_trans {
public:
	    uint16_t year_;
	    uint16_t month_;
	    uint16_t day_;
	    ne_date():ne_non_trans(ET_NE_DATE),year_(0), month_(0), day_(0){};
	    ne_date(const uint16_t& _start, const uint16_t& _len,const int _year, const int _month, const int _day):
	    	ne_non_trans(_start, _len, ET_NE_DATE)
	    {
	    	if (_year >= 0)
	    	{
	    		year_ = _year;
	    	}
	    	if (_month >= 0)
	    	{
	    		month_ = _month;
	    	}
	    	if (_day >= 0)
	    	{
	    		day_ = _day;
	    	}
	    };
	    /*void print()
	    {
	    	std::cout << "year = " << year_;
	    }*/
};
class ne_dateperiod : public ne_non_trans {
public:
	    uint16_t centrary_;
	    uint16_t decade_;
	    uint16_t dateperiod_;
	    ne_dateperiod():ne_non_trans(ET_NE_DATE),dateperiod_(0),centrary_(0),decade_(0){};
	    ne_dateperiod(const uint16_t& _start, const uint16_t& _len, const int _centrary, const int _decade):
	    	ne_non_trans(_start, _len, ET_NE_DATE)
	    {
	    	if (_centrary >= 0)
	    	{
	    		centrary_ = _centrary;
	    	}
	    	if (_decade >= 0)
	    	{
	    		decade_ = _decade;
	    	}
	    	if(_centrary >= 0||_decade >= 0)
	    	{
	    		dateperiod_=centrary_*100+decade_;
	    	}

	    }
};

class ne_time : public ne_non_trans {
public:
	 	uint16_t hour_;
		uint16_t minute_;
		float second_;
	    ne_time():ne_non_trans(ET_NE_TIME),hour_(0), minute_(0), second_(0.0f){};
	    ne_time(const uint16_t& _start, const uint16_t& _len,const int _hour, const int _min, const float _sec):
	    	ne_non_trans(_start, _len, ET_NE_TIME)//感觉有问题
	    {
	    	if (_hour >= 0 )
	    	{
	    		hour_ = _hour;
	    	}
	    	if (_min >= 0)
	    	{
	    		minute_=_min;
	    	}
	    	if (_sec >= 0)
	    	{
	    		second_=_sec;
	    	}
	    };
private:

};

class ne_currency: public ne_non_trans {
public:
	    float amount_;
	    ne_currency_type_name currency_type_;
	    ne_currency() : ne_non_trans(ET_NE_CURRENCY), amount_(0.0f), currency_type_(ET_NE_CUR_CNY){};
};

//for length capacity and weight
class ne_lcw : public ne_non_trans {
public:
	   uint16_t unit_start_;
	   uint16_t uint_length_;
	   float amount_;
	   ne_lcw() : ne_non_trans(ET_NE_LCW), amount_(0.0f), unit_start_(0), uint_length_(0){};

};
#pragma pack(pop)
}/*end of namespace eai*/
}/*end of namespace huawei*/



#endif /* SRC_MAIN_CPP_PREPROCESS_NETRANS_NE_TYPES_HPP_ */
