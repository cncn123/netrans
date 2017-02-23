/*
 * ne_recognizer.h
 *
 *  Created on: Dec 28, 2016
 *      Author: wyd
 */

#ifndef PREPROCESS_NETRANS_NE_RECOGNIZER_H_
#define PREPROCESS_NETRANS_NE_RECOGNIZER_H_

#include "preprocess/netrans/ne_recognizer_resource.h"
namespace huawei {
namespace eai {

class ne_recognizer {
public:
	ne_recognizer();
	ne_recognizer(ne_recognizer_dual_resource* _ne_res);
	virtual ~ne_recognizer();
	bool recognize(const wchar_t* _send, const int& _sent_len, ne_non_trans** _ne_output, int& _unit_left_in_output);
private:
	ne_recognizer_dual_resource* ne_res_;
};

}/*namespace eai */
}/*namespace huawei */



#endif /* PREPROCESS_NETRANS_NE_RECOGNIZER_H_ */
