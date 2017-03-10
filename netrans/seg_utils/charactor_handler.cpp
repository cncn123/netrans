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
#include "utils/unicode_converter.h"
#include <iostream>
namespace huawei {
namespace eai{

bool charactor_handler::is_all_chn_digit(const wchar_t* _beg, const int len)
{
	int i;
	int j;
	wchar_t chn_digit[]={L'零', L'一', L'壹', L'二', L'贰', L'两', L'三', L'叁', L'四', L'肆', L'五', L'伍', L'六', L'陆', L'七', L'柒', L'八', L'捌', L'九', L'玖',L'十',L'拾',L'百' ,L'佰',L'千', L'仟', L'万', L'亿', L'半', L'刻'};
	for( i = 0; i< len; i++)
	{
//		std::cout<<"wcslen="<<wcslen(chn_digit)<<std::endl;
		for(j=0; j<wcslen(chn_digit); j++){
			if(chn_digit[j]==_beg[i]){

				break;
			}
		}
		if(j==wcslen(chn_digit)){
			break;
		}

//		if( _beg[i]!= L'零' || L'一' ||  L'壹'|| L'二'|| L'贰'|| L'两'|| L'三'|| L'叁'|| L'四'|| L'肆'||
//				L'五'|| L'伍'|| L'六'|| L'陆'|| L'七'|| L'柒'|| L'八'|| L'捌'|| L'九'|| L'玖')
//		{
//			break;
//		}
	}
	if(i == len){
		std::cout<< "all chn"<<std::endl;
		return true;
	}
	else
		return false;
}
bool charactor_handler::is_all_digit(const wchar_t* _beg, const int len)
{

	int i = 0, j = 0;
	string _s;
	unicode_converter uc;
	uc.wchar_to_utf8(_beg,_s);
	for( i = 0; i< len; i++)
	{
		std::cout<<"sss "<<_s[i]<<"\n";
		if(!isdigit(_s[i]) && _s[i]!=',' && _s[i]!='.'){
			break;
		}
		else if(_s[i] == '.'){
			j++;
		}
//		if( _beg[i]!= L'0'|| L'1'|| L'2'|| L'3'|| L'4'|| L'5'|| L'6'|| L'7'|| L'8'|| L'9'|| L','|| L'.')
//		{
//			break;
//		}
//		else if(_beg[i] ==  L'.')
//		{
//			j++;
//		}
	}
	if(i == len && j<=1)
		return true;
	else
		return false;
}
int Chinese_to_integer(wchar_t a)                           //汉语转成int型
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
	case L'十':
	case L'拾': return 10; break;
	case L'百':
	case L'佰': return 100; break;
	case L'千':
	case L'仟': return 1000; break;
	case L'万': return 10000; break;
	case L'亿': return 100000000; break;
	case L'半': return 30; break;
	case L'刻': return 15; break;
	default: return 11; break;
	}
}


int Position_of_zero( const wchar_t *w, const int l)                  //零的位置（第一位不为零前提下）
{
	int i = 0;
	for (i = 0; i < l + 1; i++)
	{
		if (Chinese_to_integer(*(w + i)) == 0)
			break;
	}
	return i;
}

int Position_of_yi(const wchar_t *w, const int len2)                    //亿的位置（第一位不为亿前提下）
{
	int j = 0;
	for (int i = 0; i < len2; i++)
	{
		if (Chinese_to_integer(*(w + i)) == 100000000)
		{
			j=i;
			break;
		}
	}
	return j;
}

int Position_of_wan( const wchar_t *w, const int len)                     //万的位置（第一位不为万前提下）
{
	int j = 0;
	for (int i = 0; i < len + 1; i++)
	{
		if (Chinese_to_integer(*(w + i)) == 10000)
		{
			j=i;
			break;
		}
	}
	return j;
}

int Number_of_yi(const wchar_t *s, const int l)                             //多少个'亿'
{
	int j = 0;
	for (int i = 0; i < l; i++)
	{
		if (Chinese_to_integer(*(s + i)) == 100000000)
			j++;
	}
	return j;
}

int Number_of_wan(const wchar_t *s, const int l)                              //多少个'万'
{
	int j = 0;
	for (int i = 0; i < l + 1; i++)
	{
		if (Chinese_to_integer(*(s + i)) == 10000)
			j++;
	}
	return j;
}

int Number_of_zero(const wchar_t *s, const int l)                 //多少个'零'
{
	int j = 0;
	for (int i = 0; i < l + 1; i++)
	{
		if (Chinese_to_integer(*(s + i)) == 0)
			j++;
	}
	return j;
}

int Number_of_units_digit(const wchar_t *s, const int l)               //多少个个位数(1-9)
{
	int j = 0;
	for (int i = 0; i < l + 1; i++)
	{
		if (Chinese_to_integer(*(s + i)) <10 && Chinese_to_integer(*(s + i)) != 0)
			j++;
	}
	return j;
}

int Number_of_decimal_multiple( const wchar_t *s, const int l)            //多少个倍数
{
	int j = 0;
	for (int i = 0; i < l + 1; i++)
	{
		if (Chinese_to_integer(*(s + i)) >9)
			j++;
	}
	return j;
}

int Is_thousand_or_hundred(const wchar_t s)                           //是不是千或百
{
	if (Chinese_to_integer(s) == 1000 || Chinese_to_integer(s) == 100)
		return 1;
	else
		return 0;
}

int Is_decimal_multiple(const wchar_t s)                              //是不是倍数
{
	if(Chinese_to_integer(s)%10 == 0)
		return 1;
	else
		return 0;
}

int Is_units_digit(const wchar_t s)                                     //是不是1-9
{
	if (Chinese_to_integer(s) < 10 && Chinese_to_integer(s) != 0)
		return 1;
	else
		return 0;
}

int Decimal_multiple_continuous(const wchar_t *s, const int l)             //是否连续倍数
{
	int j = 0;
	for (int i = 0; i < l; i++)
	{
		if (Is_decimal_multiple(*(s + i)))
		{
			if (Is_decimal_multiple(*(s + i + 1)))
			{
				j = 1;
				break;
			}
		}
	}
	return j;
}

int Units_digit_continuous(const wchar_t *s, const int l)        //是否连续个数
{
	int j = 0;
	for (int i = 0; i < l; i++)
	{
		if (Is_units_digit(*(s + i)))
		{
			if (Is_units_digit(*(s + i + 1)))
			{
				j = 1;
				break;
			}
		}
	}
	return j;
}

int Multiple_continuous_from_large_to_small( const wchar_t *s, const int l)             //倍数顺序是否从大到小
{
	int j = 1;

	for (int i = 1; i < l - 1; i = i + 2)
	{
		int a = Chinese_to_integer(*(s + i));
		int b = Chinese_to_integer(*(s + i + 2));
		if (a < b)
		{
			j = 0;
			break;
		}
	}
	return j;
}

void Drop_zero(const wchar_t *w, wchar_t w1[], const int len)
{
	int i = 0, j = 0;
	for (i = 0; i < len + 1; i++)                 // 将w中不是0的中文数，按顺序存放在w3中
	{
		if (Chinese_to_integer(*(w + i)))
		{
			w1[j] = *(w + i);
			j++;
		}
	}
}

int Calcu1( const wchar_t *w1, const int len)                 //计算万以下的汉语数字
{

	int result = 0 , i = 0, j = 0;
	int	w2[10] = { 0 };
	int	w3[10] = { 0 };
	if (len < 0 || !*w1 )
		return 0;
	else
	{
		for (i = 0; i < len + 1; i++)           // 将每一位中文数字转换成int存放数组w2中
			w2[i] = Chinese_to_integer(*(w1 + i));
		for (i = 0; i < len + 1; i++)             // 将w2中不是0的数，按顺序存放在w3中
		{
			if (w2[i])
			{
				w3[j] = w2[i];
				j++;
			}
		}
		if (w3[0] == 10)                    //如果第一位是十
			result = 10 + w3[1];            //两种可能：十或十几——>如果是十，w3[1]=0  ——>得到result
		else                                //第一位不是十
		{
			for (i = 0; i < len + 2; i++)        //将w3中无用位，全部从0变成1
			{
				if (w3[i] == 0)
					w3[i] = 1;
			}
			for (i = 0; i < j; i = i + 2)   //所有位，从前到后两两配对（即个数乘以倍数），当个位存在时，个位与其后一位配对，个位后一位为1，即倍数为1
			{
				result = result + w3[i] * w3[i + 1]; //两两配对，结果相加
			}
		}
		return result;
	}
}

int Calcu2(const wchar_t *w1, const int len, const int i2)   //计算万以下的汉语数字(可包含三千三类型的倍数省略）
{
	int t = 0;
	if ( len <0 || !*w1)
		return 0;
	else if (len == 0)                                //只有一位（三万三）
	    if (i2)
			return Chinese_to_integer(*w1)*1000;
		else
			return Chinese_to_integer(*w1)*10000;
	else
	{
		if (Is_decimal_multiple(*(w1 + len)))                         //最后一位是倍数
			return Calcu1(w1, len);
		else if (Chinese_to_integer(*(w1 + len - 1)) == 0)      //最后一位不是倍数且倒数第二位为零
			return Calcu1(w1, len );
		else                                         //最后一位不是倍数且倒数第二位不为零
		{
			t = Chinese_to_integer(*(w1 + len))*Chinese_to_integer(*(w1 + len - 1)) / 10;
			int t1 = Calcu1(w1, len - 1);
			return t + t1;
		}
	}
}

bool No_zero_judge(const wchar_t *s, const int l)               //无零判断是否符合标准
{
	if (Is_decimal_multiple(*s))                           //如果第一位是倍数
	{
		if (l == 1 && Chinese_to_integer(*s) == 10)  //十
			return true;
		else if (l == 2 && Chinese_to_integer(*s) == 10 && Is_units_digit(*(s + 1)))//十几
			return true;
		else
			return false;
	}
	else                                    //第一位为1-9
	{
		int b1 = Number_of_units_digit(s, l);
		int b2 = Number_of_decimal_multiple(s, l);
		if (b1 == b2 || b1 == (b2 + 1))//数的个数要等于倍数额个数或等于倍数个数加一
		{
			if (Decimal_multiple_continuous(s, l))               //倍数连续
				return false;
			else if (Units_digit_continuous(s, l))          //数连续
				return false;
			else if (Multiple_continuous_from_large_to_small(s, l))          //倍数从大到小顺序
				return true;
			else
				return false;
		}
		else
			return false;
	}
}

bool One_zero_judge(const wchar_t *s, const int l)            //一个零判断是否符合标准
{
	int b = Position_of_zero(s, l);
	if (l == 1)                            //单个数字零
		return true;
	else
	{
		if (b == 0)                       //第一位数字为零
		{
			const wchar_t *s1 = s + 1;
			return No_zero_judge(s1, 1 - 1);
		}
		else                                  //第一位数不为零
		{
			if ((l-b)>1)                     //零后面第二位存在
			{
				if (Is_decimal_multiple(*(s + b - 1)) && Is_decimal_multiple(*(s + b + 2))                     //零的前一位是倍数，后面第二位也是倍数
					&& (Chinese_to_integer(*(s + b - 1)) / Chinese_to_integer(*(s + b + 2)) > 10)) //而且前面倍数要是后面倍数100倍或更高
				{
					wchar_t w[10] = L"";
					Drop_zero(s, w, l);
					return No_zero_judge(w, l - 1);
				}
				else if (Is_decimal_multiple(*(s + b - 1)) && Chinese_to_integer(*(s + b + 1)) == 10 && Is_units_digit(*(s + b + 2)))        //零的前一位是倍数，后面一位是十，后第二位是1-9
					return true;
				else
					return false;
			}
			else if (l-b)                       //零后面第二位不存在,但是第一位存在
			{
				if (Chinese_to_integer(*(s + b - 1)) > 10 && Chinese_to_integer(*(s + b + 1)) < 10 )   //零几，零前一位要为百以上
				{
					wchar_t w[10] = L"";
					Drop_zero(s, w, l);
					return No_zero_judge(w, l - 1);
				}
				else
					return false;
			}
			else                                         //其他情况
				return false;
		}
	}

}

bool Two_zero_judge(const wchar_t *s, const int l)
{
	const wchar_t *s1 = s;
	if (Chinese_to_integer(*s) != 0)           //第一位一定是零
		return false;
	else
	{
		s1++;                        //将第一位零去掉，判断后面的是否正确
		return One_zero_judge(s1, l - 1);
	}
}

bool Judge1(const wchar_t *s, int l)               //判断w11w12w21是否符合标准
{
	if (l<0 || !*s)
		return true;
	else
	{
		int a = Number_of_zero(s, l);                       //多少零
		if (a > 2)                            //大于2个零，格式错误
			return false;
		else if (a == 2)                      //两个零
			return Two_zero_judge(s, l);
		else if (a == 1)                      //只有一个零
			return One_zero_judge(s, l);
		else                                  //没有零
		{
			if (l > 1 && Is_units_digit(*(s + l)))      //最后一位为个数
			{
				if (Chinese_to_integer(*(s + l - 1)) == 10) //无零且最为一位为个位情况下，倒数第二位必须为十, （三百三万不对，必须三百零三万）
					return No_zero_judge(s, l);
				else
					return false;
			}
			else
				return No_zero_judge(s, l);
		}
	}
}

bool Judge2(const wchar_t *s, const int l)               //判断w22是否符合标准
{
	if (l<0 || !*s)
		return true;
	else
	{
		int a = Number_of_zero(s, l);                       //多少零
		if (a > 2)                            //大于2个零，格式错误
			return false;
		else if (a == 2)                      //两个零
			return Two_zero_judge(s, l);
		else if (a == 1)                      //只有一个零
			return One_zero_judge(s, l);
		else                                  //没有零
			return No_zero_judge(s, l);
	}
}

bool Convert_to_integer(const wchar_t *w, const int len1, long long int *total) //将一个一亿亿以下的汉语数字转成long long型整数，思路：将其分割成A万B亿C万D的形式
{                                                                  //这样A,B,C,D都为万以下的汉语数字
	int i = 0, i1 = 0, i2 = 0;
	int u = 0;
	long long int a = 0, b = 0, c = 0, d = 0;
	bool a1, b1, c1, d1;
	const wchar_t *w1 = NULL;        //存放亿左边的汉语数字
	const wchar_t *w2 = NULL;         //存放亿右边的汉语数字
	const wchar_t *w11 = NULL;        //存放A首地址
	const wchar_t *w12 = NULL;        //存放B首地址
	const wchar_t *w21 = NULL;        //存放C首地址
	const wchar_t *w22 = NULL;        //存放D首地址
	int lw1 = -1, lw2 = -1, lw11 = -1, lw12 = -1, lw21 = -1, lw22 = -1;
	for (int p0 = 0; p0<len1; p0++)//是否有无用汉字
	{
		if (Chinese_to_integer(*(w + p0)) == 11)
		{
			u++;
			break;
		}
	}
	std::cout<<"len1= "<< len1<<std::endl;
	std::cout<<"u= "<< u<< std::endl;
	if (u)                                     // 出现无用汉字
		return false;
	else if ((wcscmp((w+len1-1),L"刻"))==0){
		std::cout<<"deal with 刻"<<std::endl;
		std::cout<<"size= "<<
		std::cout<<"Chinese_to_integer(*w)= "<<Chinese_to_integer(*w)<<std::endl;
		*total = Chinese_to_integer(*w)*15;
		return true;
	}
	else if (len1 == 1)                                    // 无无用汉字，只有一位
	{
		std::cout<<"deal with 半"<<std::endl;
		// deal with 半
		std::cout<<"cmp= "<<wcscmp(w,L"半")<<std::endl;
		if(wcscmp(w,L"半")==0){
			std::cout<<"123123"<<std::endl;
			*total = 30;
			std::cout<<"total123= "<<*total<<std::endl;
		}else{
			std::cout<<"no 半"<<std::endl;
			*total = Chinese_to_integer(*w);
		}
		std::cout<<"no 123"<<std::endl;
		std::cout<<"total= "<<*total<<std::endl;
		return true;
	}
	else
	{	                                             // 几个'亿'在字符串中
		if (Number_of_yi(w, len1) > 1)                            // 出现多于1个'亿',不符合标准
			return false;
		else
		{
			i = Position_of_yi(w, len1);
			if (i)                             // 只有1个'亿' 存在，且不在第一位
			{
				w1 = w;             // get w1
				lw1 = i - 1;           //w1可以往后加几位
				w2 = w + (i + 1);           // get w2
				lw2 = len1 - 1 - (i + 1);
				int p2 = Number_of_wan(w1, lw1);            // 几个'万'在w1中
				int p3 = Number_of_wan(w2, lw2);            // 几个'万'在w2中
				if (p2 > 1 || p3 > 1)          // w1或w2出现多于1个'万'，不符合标准
					return false;
				else
				{
					i1 = Position_of_wan(w1, i);           // find '万' in w1
					if (i1)                     // w1 存在'万',且不在第一位
					{
						w11 = w; // get w11
						lw11 = i1 - 1;
						w12 = w + (i1 + 1); // get w12
						lw12 = i - 1 - (i1 + 1);  //w[i]是亿，亿位去除，再减去指针指向位置，可得到指针能加几位
					}
					else
					{
						w12 = w;      // no'万'，get w12
						lw12 = lw1;    //
					}
					i2 = Position_of_wan(w2, lw2);// find'万' in w2
					if (i2)
					{
						w21 = w12 + (lw12 + 2);          // get w21
						lw21 = i2 - 1;
						w22 = w12 + (lw12 + 2 + i2 + 1); // get w22
						lw22 = (len1 - 1 - i - (lw21+2)-1);
					}
					else
					{
						w22 = w2;      // no'万'，get w22
						lw22 = lw2;
					}
				}
			}
			else                               // '亿' 不存在
			{
				w2 = w;                          // get w2
				lw2 = len1 - 1;
				int p4 = Number_of_wan(w2, lw2);            // 几个'万'在w2中
				if (p4 > 1)                    // w2出现2个'万'，不符合标准
					return false;
				else
				{
					i2 = Position_of_wan(w2, lw2);
					if (i2)
					{
						w21 = w2;                    // get w21
						lw21 = i2 - 1;
						w22 = w21 + i2 + 1;         // get w22
						lw22 = ((len1 - 1) - i2 - 1);
					}
					else
					{
						w22 = w2;      // no'万'，get w22
						lw22 = lw2;
					}
				}

			}
			a1 = Judge1(w11, lw11);
			b1 = Judge1(w12, lw12);
			c1 = Judge1(w21, lw21);
			d1 = Judge2(w22, lw22);
			if (a1 && b1 && c1 && d1)
			{
				a = Calcu1(w11, lw11);
				b = Calcu1(w12, lw12);
				c = Calcu1(w21, lw21);
				d = Calcu2(w22, lw22, i2);
				*total = (a * 10000 + b) * 100000000 + c * 10000 + d;
				return true;
			}
			else
				return false;
		}

	}
}

//integer to regular integer

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

bool charactor_handler::get_chn_value(const wchar_t *_beg, const int len, long long int* result)
{
	 std::cout<<"convert_to_integer"<<std::endl;
	 std::cout<<"len= "<<len<<std::endl;
	 return Convert_to_integer(_beg, len, result);
}

double charactor_handler::get_value(const wchar_t* _beg, const int len)
{
	return conv(_beg, len);
}

}/*namespace eai */
}/*namespace huawei */








