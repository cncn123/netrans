/*
 * charactor_handler.h
 *
 *  Created on: Jan 13, 2017
 *      Author: parallels
 */

/*
 * charactor_handler.h
 *
 *  Created on: Jan 10, 2017
 *      Author: wyd
 */

#ifndef SRC_MAIN_CPP_SEG_UTILS_CHARACTOR_HANDLER_H_
#define SRC_MAIN_CPP_SEG_UTILS_CHARACTOR_HANDLER_H_

namespace huawei {
namespace eai {

class charactor_handler {
public:
	bool is_all_chn_digit(const wchar_t* _beg, const int len);
	bool is_all_digit(const wchar_t* _beg, const int len);
	int get_chn_value(const wchar_t* _beg, const int len);
	double get_value(const wchar_t* _beg, const int len);
};

}/*namespace eai */
}/*namespace huawei */




#endif /* SRC_MAIN_CPP_SEG_UTILS_CHARACTOR_HANDLER_H_ */

