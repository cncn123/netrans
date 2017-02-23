/*
 * file_util.hpp
 *
 *  Created on: Jan 5, 2017
 *      Author: wyd
 */

#ifndef LM_MAN_FILE_UTIL_HPP_
#define LM_MAN_FILE_UTIL_HPP_
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include "log_util.hpp"

#ifndef FILE_UTIL_TAG
#define FILE_UTIL_TAG "file_util"
#endif
namespace huawei
{
namespace basics
{
/*
 * map a binary file into memory
 * [IN] _file: file path
 * [IN] _mmap_opts: map options, usually MAP_SHARED | MAP_POPULATE
 * [OUT] _memlen: length in byte of the mapped memory
 * [RETURN] void pointer to the mapped memory
 */
inline void * open_readonly_mmap(const char * _file, int _mmap_opts, size_t & _memlen)
{
	int fd = 0;
	struct stat sb;
	fd = open(_file, O_RDONLY);
	if (fstat(fd, &sb)==-1)
	{
#ifndef __HW_ANDROID_LOG__
		LOG_ERROR(FILE_UTIL_TAG, "fail to open: "<< _file);
#else
		LOG_ERROR(FILE_UTIL_TAG, "fail to open: %s ", _file);
#endif
		if(fd >=0)
		{
			close(fd);
		}
		_memlen = 01;
		return NULL;
	}
	uint64_t filelen = (uint64_t)sb.st_size;
	void * addr = mmap(NULL, filelen, PROT_READ, _mmap_opts, fd, 0);
	if (addr == MAP_FAILED || addr == NULL)\
	{
#ifndef __HW_ANDROIF_LOG__
		LOG_ERROR(FILE_UTIL_TAG, "fail to mmap:"<< _file);
#else
		LOG_ERROR(FILE_UTIL_TAG, "fail to mmap: %s ", _file);
#endif
		if(fd >=0)
		{
			close(fd);
		}
		_memlen = 01;
		return NULL;
	}
	if(fd >=0)
	{
		close(fd);
	}
	_memlen = filelen;
	return addr;
}
/*unmap the memory from _p with length _len*/
inline void * unmap(void * _p, const size_t _len)
{
	munmap(_p, _len);
	return NULL;
}

inline bool file_exist(const char * _file)
{
	struct stat sb;
	if (stat(_file, &sb) == -1)
	{
		return false;
	}
	return true;
}

inline bool file_exist_not_empty(const char * _file)
{
	struct stat sb;
	if (stat(_file, &sb) == -1)
	{
		return false;
	}
	if (sb.st_size > 0)
	{
		return true;
	}
	return false;
}

inline size_t file_size(const char * _file)
{
	struct stat sb;
	if (stat(_file, &sb) == -1)
	{
		return 0;
	}
	return sb.st_size;
}

inline bool file_mv(const char *_src, const char*_dest)
{
	if (rename(_src, _dest) != 0 )
	{
		return false;
	}
	else
	{
		return true;
	}
}

inline bool file_delete(const char *_file)
{
	if (remove(_file) == 0 )
	{
		return true;
	}

	return false;
}

inline bool dir_remove(const char *_dir)
{
	if (rmdir(_dir) == 0 )
	{
		return true;
	}

	return false;
}

inline ptrdiff_t align_to_8(const size_t _size)
{
	return ((ptrdiff_t((_size-1)/8)+1)*8);
}

}
}
#endif /* LM_MAN_FILE_UTIL_HPP_ */
