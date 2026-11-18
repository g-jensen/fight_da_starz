#include "../specc/specc.h"

spec(passing_spec)(spec_t *s) {
  should(s, 1 == 1);
}

spec(failing_spec)(spec_t *s) {
  should(s, 1 == 0);
}