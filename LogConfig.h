  #define ENABLE_ERROR_LOG
  #ifdef ENABLE_ERROR_LOG
  #define ERROR_LOG(msg,args...) fprintf(stderr,msg,args...);
  #else
  #define ERROR_LOG(msg,args...)
  #endif

  #define ENABLE_LOG
  #ifdef ENABLE_LOG
  #define DEBUG_LOG(msg,args...) printf(msg,args...);
  #else
  #define DEBUG_LOG(msg,args...)
  #endif
