#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdint.h>

#define AINFO LOG(INFO)
#define AWARN LOG(WARNING)
#define AERROR LOG(ERRORS)
#define AFATAL LOG(FATAL)

typedef enum log_rank {
   INFO,
   WARNING,
   ERRORS,
   FATAL
}log_rank_t;


void initLogger(const std::string&info_log_filename,
                const std::string&warn_log_filename,
                const std::string&error_log_filename);


class Logger {
   friend void initLogger(const std::string& info_log_filename,
                           const std::string& warn_log_filename,
                           const std::string& erro_log_filename);

public:

   Logger(log_rank_t log_rank) : m_log_rank(log_rank) {}

   ~Logger();

   static std::ostream& start(log_rank_t log_rank,
                               const int32_t line,
                               const std::string& function);

private:

   static std::ostream& getStream(log_rank_t log_rank);

   static std::ofstream m_info_log_file;                 
   static std::ofstream m_warn_log_file;                  
   static std::ofstream m_error_log_file;                  
   log_rank_t m_log_rank;                             
};



#define LOG(log_rank)   \
Logger(log_rank).start(log_rank, __LINE__,__FUNCTION__)


#define CHECK(a)                                            \
   if(!(a)) {                                              \
        LOG(ERRORS) << " CHECK failed " << std::endl              \
                   << #a << "= " << (a) << std::endl;          \
       abort();                                            \
   }                                                      \

#define CHECK_NOTNULL(a)                                    \
   if( NULL == (a)) {                                      \
       LOG(ERRORS) << " CHECK_NOTNULL failed "              \
                   << #a << "== NULL " << std::endl;           \
       abort();                                            \
    }

#define CHECK_NULL(a)                                       \
   if( NULL != (a)) {                                      \
       LOG(ERRORS) << " CHECK_NULL failed " << std::endl         \
                   << #a << "!= NULL " << std::endl;           \
       abort();                                            \
    }


#define CHECK_EQ(a, b)                                      \
   if(!((a) == (b))) {                                     \
       LOG(ERRORS) << " CHECK_EQ failed "  << std::endl          \
                   << #a << "= " << (a) << std::endl           \
                   << #b << "= " << (b) << std::endl;          \
       abort();                                            \
    }

#define CHECK_NE(a, b)                                      \
   if(!((a) != (b))) {                                     \
       LOG(ERRORS) << " CHECK_NE failed " << std::endl           \
                   << #a << "= " << (a) << std::endl           \
                   << #b << "= " << (b) << std::endl;          \
       abort();                                            \
    }

#define CHECK_LT(a, b)                                      \
   if(!((a) < (b))) {                                      \
       LOG(ERRORS) << " CHECK_LT failed "                   \
                   << #a << "= " << (a) << std::endl           \
                   << #b << "= " << (b) << std::endl;          \
       abort();                                            \
    }

#define CHECK_GT(a, b)                                      \
   if(!((a) > (b))) {                                      \
       LOG(ERRORS) << " CHECK_GT failed "  << std::endl          \
                  << #a <<" = " << (a) << std::endl            \
                   << #b << "= " << (b) << std::endl;          \
       abort();                                            \
    }

#define CHECK_LE(a, b)                                      \
   if(!((a) <= (b))) {                                     \
       LOG(ERRORS) << " CHECK_LE failed "  << std::endl          \
                   << #a << "= " << (a) << std::endl           \
                   << #b << "= " << (b) << std::endl;          \
       abort();                                            \
    }

#define CHECK_GE(a, b)                                      \
   if(!((a) >= (b))) {                                     \
       LOG(ERRORS) << " CHECK_GE failed "  << std::endl          \
                   << #a << " = "<< (a) << std::endl            \
                   << #b << "= " << (b) << std::endl;          \
       abort();                                            \
    }

#define CHECK_DOUBLE_EQ(a, b)                               \
   do {                                                    \
       CHECK_LE((a), (b)+0.000000000000001L);              \
       CHECK_GE((a), (b)-0.000000000000001L);              \
    }while (0)
