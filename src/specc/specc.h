#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define SPECC

typedef struct spec_t {
  int failing;
  size_t num_failed;
  size_t num_passed;
} spec_t;

typedef void (*__function)(spec_t*);

struct __spec {
  __function f;
  const char* name;
  const char* filename;
};

struct __fun_list { 
  struct __fun_list* next; 
  struct __spec named_fn;
};

typedef struct __fun_list __fun_list;

extern __fun_list* __head; 
extern __fun_list* __tail;

void __fun_list_add(__function f, const char* name);
void __printf_color_and_nest(size_t nest_level, const char* color,const char * format, ...);
const char* __type_to_fmt(const char* type);

void static print_summary(spec_t *spec);
void static call_flist(__fun_list* head, spec_t *spec);
void static free_flist(__fun_list* head);

#define SPECC_COLOR_GREEN "\033[0;32m"
#define SPECC_COLOR_RED "\033[1;31m"
#define SPECC_COLOR_CLEAR "\033[0m"

#define spec(name)\
  static void _##name##_spec(spec_t*);\
  static void __attribute__((constructor)) __construct_##name##_spec(void) {\
    __fun_list_add(_##name##_spec, #name);\
  }\
  static void _##name##_spec

#define __inline_specc_fail(spec_ptr)\
  spec_ptr->failing = 1;\
  spec_ptr->num_failed++;\
  printf("%sFAIL%s\n", SPECC_COLOR_RED, SPECC_COLOR_CLEAR);\
  printf("    %s:%d", __FILE__,__LINE__);

#define spec_fail(spec_ptr) \
  __inline_specc_fail(spec_ptr);\
  printf("\n");\
  return;

#define specc_fail_message(spec_ptr, fmt, ...) \
  __inline_specc_fail(spec_ptr);\
  printf("\n    ");\
  printf(fmt,__VA_ARGS__); \
  printf("\n"); \
  return;\

#define should(spec_ptr, assertion) if (!(assertion)) {spec_fail(spec_ptr);}

#define should_not(assertion) should(!(assertion))

#define should_eq(spec_ptr, expected, actual, type) \
  if (!((expected) == (actual))) { \
    specc_fail_message(spec_ptr, (char*)__type_to_fmt(#type),expected,actual)\
  }

#define should_not_eq(spec_ptr, expected, actual, type) \
  if (((expected) == (actual))) { \
    specc_fail_message(spec_ptr, (char*)__type_to_fmt(#type),expected,actual)\
  }

#define should_str_eq(spec_ptr, expected, actual) \
  if (strcmp(expected,actual) != 0) { \
    specc_fail_message(spec_ptr, "> Expected: \"%s\" Actual: \"%s\"",expected,actual)\
  }

#define should_str_not_eq(spec_ptr, expected, actual) \
  if (strcmp(expected,actual) == 0) { \
    specc_fail_message(spec_ptr, "> Expected strings to be different: \"%s\"",expected)\
  }

#define should_double_eq(spec_ptr, expected, actual, err)\
  if (!(expected+err >= actual && expected-err <= actual)) {\
    specc_fail_message(spec_ptr, "> Expected: %lf Actual: %lf With Error: %lf",expected,actual,err)\
  }

#define should_double_not_eq(spec_ptr, expected,actual,err)\
  if (expected+err >= actual && expected-err <= actual) {\
    specc_fail_message(spec_ptr, "> Expected: %lf Actual: %lf With Error: %lf",expected,actual,err)\
  }

#define should_float_eq(spec_ptr, expected,actual,err)\
  if (!(expected+err >= actual && expected-err <= actual)) {\
    specc_fail_message(spec_ptr, "> Expected: %f Actual: %f With Error: %f",expected,actual,err)\
  }

#define should_float_not_eq(spec_ptr, expected,actual,err)\
  if (expected+err >= actual && expected-err <= actual) {\
    specc_fail_message(spec_ptr, "> Expected: %f Actual: %f With Error: %f",expected,actual,err)\
  }
  
