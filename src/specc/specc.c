#include "specc.h"

__fun_list* __head = NULL; 
__fun_list* __tail = NULL;

void __fun_list_add(__function f, const char* name) {
  if (!__head) {
    __head = (__fun_list*)malloc(sizeof(__fun_list));
    __head->named_fn = (struct __spec){.f = f, .name = name};
    __head->next = NULL;
    __tail = __head;
  } else {
    __tail->next = (__fun_list*)malloc(sizeof(__fun_list));
    __tail->next->named_fn = (struct __spec){.f = f, .name = name};
    __tail->next->next = NULL;
    __tail = __tail->next;
  }
}

void __printf_color_and_nest(size_t nest_level, const char* color, const char * format, ...) {
  va_list args;
  va_start(args,format);
  for (size_t i = 0; i < nest_level; i++) {
    printf("  ");
  }
  printf("%s",color);
  vprintf(format,args);
  printf(SPECC_COLOR_CLEAR);
}

const char* __type_to_fmt(const char* type) {
  if      (strcmp("char",type) == 0)
    return "> Expected: \'%c\' Actual: \'%c\'";
  else if (strcmp("int",type) == 0)
    return "> Expected: %d Actual: %d";
  else if (strcmp("float",type) == 0)
    return "> Expected: %f Actual: %f";
  else if (strcmp("unsigned int",type) == 0)
    return "> Expected: %i Actual: %i";
  else if (strcmp("short",type) == 0)
    return "> Expected: %hi Actual: %hi";
  else if (strcmp("unsigned short",type) == 0)
    return "> Expected: %hu Actual: %hu";
  else if (strcmp("long",type) == 0)
    return "> Expected: %ld Actual: %ld";
  else if (strcmp("long double",type) == 0)
    return "> Expected: %Lf Actual: %Lf";
  else if (strcmp("double",type) == 0)
    return "> Expected: %lf Actual: %lf";
  else if (strcmp("unsigned long",type) == 0)
    return "> Expected: %lu Actual: %lu";
  else if (strcmp("unsigned long long",type) == 0)
    return "> Expected: %hu Actual: %hu";
  else 
    return "> Expected: %p Actual: %p";
}

void static print_summary(spec_t *spec) {
  size_t total = spec->num_passed + spec->num_failed;
  printf("\nSpec Summary:\n");
  __printf_color_and_nest(0, SPECC_COLOR_GREEN,"- %lu Passed\n",spec->num_passed);
  __printf_color_and_nest(0, SPECC_COLOR_RED,"- %lu Failed\n",spec->num_failed);
  printf("- %lu Total\n",total);
}

void static call_flist(__fun_list* head, spec_t *spec) {
  __fun_list* cur = NULL; 
  for(cur = head; cur; cur = cur->next) {
    printf("%s ", cur->named_fn.name);
    spec->failing = 0;
    cur->named_fn.f(spec);
    if (spec->failing == 0) {
      spec->num_passed++;
      printf("%sPASS%s\n", SPECC_COLOR_GREEN, SPECC_COLOR_CLEAR);
    }
  }
}

void static free_flist(__fun_list* head) {
  __fun_list* current = head;
  while (current) {
    __fun_list* temp = current;
    current = current->next;
    free(temp);
  }
}

int main() {
  spec_t spec = {};
  call_flist(__head, &spec);
  free_flist(__head);
  print_summary(&spec);
  return spec.num_failed > 0 ? 1 : 0;
}