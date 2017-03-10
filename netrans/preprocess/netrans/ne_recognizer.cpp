/*
 * ne_recognizer.cpp
 *
 *  Created on: Dec 28, 2016
 *      Author: wyd
 */

#include "ne_recognizer.h"
#include<iostream>
using namespace std;
namespace huawei {
namespace eai{

ne_recognizer::ne_recognizer() : ne_res_(NULL)
{


}


ne_recognizer::~ne_recognizer()
{

}

ne_recognizer::ne_recognizer(ne_recognizer_dual_resource* _ne_res) : ne_res_(_ne_res)
{

}

bool ne_recognizer::recognize(const wchar_t* _sent, const int& _sent_len,
		                      ne_non_trans** _ne_output, int& _unit_left_in_output)
{
	ne_recognizer_resource& res = ne_res_-> get_ne_res();
	ne_non_trans** output_base = _ne_output;
	for(int i=0; i<res.get_recognizers().size(); ++i)
	{
		cout<<"get_recognizers= "<<res.get_recognizers()[i].size()<< "\n";

		if(res.get_recognizers()[i].size()<=0)
		{
			continue;
		}
		cout<<"_unit_left_in_output= "<<_unit_left_in_output<< "\n";

		int unit_left =_unit_left_in_output;
		//recognizer one type of ne
		res.get_recognizers()[i].recognize_sent(_sent, _sent_len, output_base, _unit_left_in_output);
		cout<<"after _unit_left_in_output= "<<_unit_left_in_output<< "\n";
		output_base += (unit_left - _unit_left_in_output);
	}
}




}/*namespace eai */
}/*namespace huawei */


