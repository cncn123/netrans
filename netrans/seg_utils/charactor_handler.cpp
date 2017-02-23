/*
 * charactor_handler.cpp
 *
 *  Created on: Jan 13, 2017
 *      Author: parallels
 */
/*
 * charactor_handler.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: wyd
 */


#include  "charactor_handler.h"
#include  <math.h>

namespace huawei {
namespace eai{

bool charactor_handler::is_all_chn_digit(const wchar_t* _beg, const int len)
{
	int i;
	for( i = 0; i< len; i++)
	{
		if( _beg[i]!= L'零'|| L'一'|| L'壹'|| L'二'|| L'贰'|| L'两'|| L'三'|| L'叁'|| L'四'|| L'肆'||
				L'五'|| L'伍'|| L'六'|| L'陆'|| L'七'|| L'柒'|| L'八'|| L'捌'|| L'九'|| L'玖')
		{
			break;
		}
	}
	if(i == len)
		return true;
	else
		return false;
}
bool charactor_handler::is_all_digit(const wchar_t* _beg, const int len)
{
	int i = 0, j = 0;
	for( i = 0; i< len; i++)
	{
		if( _beg[i]!= L'0'|| L'1'|| L'2'|| L'3'|| L'4'|| L'5'|| L'6'|| L'7'|| L'8'|| L'9'|| L','|| L'.')
		{
			break;
		}
		else if(_beg[i] ==  L'.')
		{
			j++;
		}
	}
	if(i == len && j<=1)
		return true;
	else
		return false;
}
int convhan(wchar_t a)                           //汉语转成int型
{
	switch (a){
	case L'零': return 0; break;
	case L'一':
	case L'壹': return 1; break;
	case L'二':
	case L'贰':
	case L'两': return 2; break;
	case L'三':
	case L'叁': return 3; break;
	case L'四':
	case L'肆': return 4; break;
	case L'五':
	case L'伍': return 5; break;
	case L'六':
	case L'陆': return 6; break;
	case L'七':
	case L'柒': return 7; break;
	case L'八':
	case L'捌': return 8; break;
	case L'九':
	case L'玖': return 9; break;
	default: return 11; break;
	}
}
int conv_chn(const wchar_t *w, const int len)
{
	int total;
	int a = 0, b = 0;
	for (int i = 0; i < len; i++)
	{
		a = convhan(w[i]);
		total = total * 10 + a;
	}
	return total;

}
int charactor_handler::get_chn_value(const wchar_t *_beg, const int len)
{
	 return conv_chn(_beg, len);
}

int hmpoint(const wchar_t *s,const int len)                 //多少个'.'
{
	int j = 0;
	for (int i = 0; i < len; i++)
	{
		if (s[i] ==  L'.')
			j++;
	}
	return j;
}

int findpoint(const wchar_t *s,const int len) //'.'的位置
{
	int i = 0, j = 0;
	for (i = 0; i < len; i++)
	{
		if ((s[i]) ==  L'.')
		{
			j = i;
			break;
		}
	}
	return j;
}

double conv(const wchar_t *w, const int len)
{
	int a = 0, b = 0;
	long double total1 = 0, total=0;
	int num_of_point, pos_of_point;
	num_of_point = hmpoint( w, len );
	pos_of_point = findpoint( w, len );
	int c = 0;
	if (num_of_point)
	{
		for (int i = 0; i < len; i++)
		{
			if (w[i] !=  L'.' ||  L',')
				total1 = total1 * 10 + (w[i] - '0');
		}
		total = total1 / pow(10, len - (pos_of_point + 1));
	}
	else
	{
		for (int i = 0; i < len; i++)
				total1 = total1 * 10 + (w[i] - '0');
		total = total1;
	}
	return total;
}

double charactor_handler::get_value(const wchar_t* _beg, const int len)
{
	return conv(_beg, len);
}

}/*namespace eai */
}/*namespace huawei */








