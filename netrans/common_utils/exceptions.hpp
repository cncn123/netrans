/*
 * exceptions.hpp
 *
 *  Created on: Jan 5, 2017
 *      Author: wyd
 */

#ifndef COMMON_UTILS_EXCEPTIONS_HPP_
#define COMMON_UTILS_EXCEPTIONS_HPP_


#include <cassert>
#include <limits>
#include <stdint.h>
#ifdef __GNUC__
#define __HW_LOG_FUNC_NAME__ __FILE__<<":"<<__LINE__<<":("<<__PRETTY_FUNCTION__<<")"
#else
#ifdef _WIN32
#define __HW_LOG_FUNC_NAME__ __FUNCTION__
#else
#define __HW_LOG_FUNC_NAME__ NULL
#endif
#endif

namespace huawei
{
namespace eai
{
inline std::size_t uint64_overflow(uint64_t value){
	assert(value <= static_cast<uint64_t>(std::numeric_limits<std::size_t>::max()));
			return value;
}
}
}

#endif /* COMMON_UTILS_EXCEPTIONS_HPP_ */
