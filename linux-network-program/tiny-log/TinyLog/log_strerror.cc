
#include <TinyLog/log_strerror.h>

#include <string.h>

#include <cerrno>

namespace TinyLog { 

/************************************
 *                                  *
 *              log_strerror        *
 *                                  *
 ************************************/

thread_local char error_buf[1024];

const char* log_strerror() {  
#if (_POSIX_C_SOURCE >= 200112L) && !  _GNU_SOURCE
  ::strerror_r(errno, error_buf, sizeof(error_buf));
  return errno_buf;
#else
  return ::strerror_r(errno, error_buf, sizeof(error_buf));
#endif
}

} // TinyLog
