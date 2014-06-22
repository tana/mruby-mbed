#include <mruby.h>
#include <mruby/class.h>
#include <mruby/value.h>
#include <mruby/data.h>
#include "mbed.h"
#include "declarations.h"

extern "C" void mrb_mruby_mbed_gem_init(mrb_state* mrb) {
  struct RClass *mbed_mod = mrb_define_module(mrb, "Mbed");
#ifndef MRBMBED_DISABLE_DIGITAL_OUT
  define_digital_out(mrb, mbed_mod);
#endif
#ifndef MRBMBED_DISABLE_DIGITAL_IN
  define_digital_in(mrb, mbed_mod);
#endif
#ifndef MRBMBED_DISABLE_PWM_OUT
  define_pwm_out(mrb, mbed_mod);
#endif
#ifndef MRBMBED_DISABLE_I2C
  define_i2c(mrb, mbed_mod);
#endif
#ifndef MRBMBED_DISABLE_ENUMERATORS
  define_enumerators(mrb, mbed_mod);
#endif
#ifndef MRBMBED_DISABLE_MISC_FUNCS
  define_misc_funcs(mrb, mbed_mod);
#endif
}

extern "C" void mrb_mruby_mbed_gem_final(mrb_state* mrb) {
}
