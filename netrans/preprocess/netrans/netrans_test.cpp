/*
 * netrans_test.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: parallels
 */
#include "../../api/decoder_json.h"
//#include "seg/utils/unicode_converter.h"
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <utils/unicode_converter.h>
#include "ne_recognizer.h"
#include <string>
#include <iostream>


using namespace huawei::eai;
//using namespace huawei::lips;
using namespace std;
using namespace boost;

void wregex_text()
{	wstring cnDigit = L"一|二|三|四|五|六|七|八|九|十|零";
	wstring wstr_regex = L"([\\d|#InCnDigit#]{2,4})\\s*年\\s*([\\d|#InCnDigit#]{1,2})\\s*月\\s*([\\d|#InCnDigit#]{1,3})\\s*[日|号]";
	boost::replace_all(wstr_regex, "#InCnDigit#", cnDigit);
	unicode_converter uc;
	string tempstr;
	//uc.wchar_to_utf8(wstr_regex, tempstr, "UTF-8");
	uc.wchar_to_utf8(wstr_regex, tempstr);
	cout << tempstr << endl;

	const wchar_t* sent = L"明天是2016年4月28日星期五。昨天是二零一五年八月三十一日晴天。";
	boost::wregex data_pattern(wstr_regex);
	const wchar_t* match_start = sent;
	const wchar_t* match_end = sent + wcslen(sent);//wide char strlen
	boost::match_results<const wchar_t*> wmatch;
	while (boost::regex_search(match_start, match_end, wmatch, data_pattern))
	{
		for (size_t i = 0; i < wmatch.size(); ++i)
		{
			if(i == 1 || i == 2 || i == 3)
			{
				wstring grp(wmatch[i].first, wmatch[i].second);//why first second
				uc.wchar_to_utf8(grp, tempstr);
				cout << tempstr << endl;
			}
		}
		match_start = wmatch[0].second;
	}
	//duplicate for check
	match_start = sent ;
	match_end = sent + wcslen(sent);
	while (boost::regex_search(match_start, match_end, wmatch, data_pattern))
	{
		for (int i = 0; i < wmatch.size(); ++i)
		{
			if(i == 1 || i == 2 || i == 3)
			{
				wstring grp(wmatch[i].first, wmatch[i].second);
				uc.wchar_to_utf8(grp, tempstr);
				cout << tempstr << endl;
			}
		}
		match_start = wmatch[0].second;
	}
}

void print_date(ne_non_trans* _val)
{
	ne_date* pdate = reinterpret_cast<ne_date*>(_val);
	std::cout <<"year:"<<pdate->year_<<endl;
	std::cout <<"month:"<<pdate->month_<<endl;
	std::cout <<"day:"<<pdate->day_<<endl;
}

/*void print_time(ne_non_trans* _val)
{
	ne_time* ptime = reinterpret_cast<ne_time*>(_val);
	std::cout <<"hour:"<<ptime->hour_<<endl;
	std::cout <<"minute:"<<ptime->minute_<<endl;
	std::cout <<"second:"<<ptime->second_<<endl;
}*/


int main(int argc, char* argv[])
{
	using namespace huawei::eai;

	ne_recognizer_dual_resource* ne_res = (ne_recognizer_dual_resource*) ne_recognizer_dual_resource::
			                             create_ne_dual_resource("resources","zh");
	ne_res->reload_resource();
	ne_recognizer* ne_rec = new ne_recognizer(ne_res);

	const wchar_t* sent = L"明天是2017年11月28日星期五。";
	const int sent_len = wcslen(sent);
	ne_non_trans** output_buf = (ne_non_trans **) calloc(128, sizeof(ne_non_trans*));
	int buf_unit_left = 128;
	ne_rec->recognize(sent, sent_len, output_buf, buf_unit_left);
	int output_len = 128 - buf_unit_left;
	std::cout << "output len = " << output_len;
	for (int i = 0; i < output_len; ++i)
	{
		cout<<output_buf[i]->type_<<endl;
		if (output_buf[i]->type_ == ET_NE_DATE)
		{
			cout << (int)(output_buf[i]->type_) <<endl;
			print_date(output_buf[i]);
		}
		else if (output_buf[i]->type_ == ET_NE_TIME)
		{
			//print_time(output_buf[i]);
		}
	}
	return 0;
}



