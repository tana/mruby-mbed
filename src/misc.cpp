#include <mruby.h>
#include <mruby/class.h>
#include <mruby/value.h>
#include <mruby/data.h>
#include "mbed.h"

#ifndef MRBMBED_DISABLE_MISC_FUNCS

mrb_value mrb_mbed_wait(mrb_state* mrb, mrb_value self);
mrb_value mrb_mbed_wait_ms(mrb_state* mrb, mrb_value self);
mrb_value mrb_mbed_wait_us(mrb_state* mrb, mrb_value self);

void define_misc_funcs(mrb_state* mrb, struct RClass* mbed_mod) {
  mrb_define_method(mrb, mbed_mod, "wait", mrb_mbed_wait, ARGS_REQ(1));
  mrb_define_method(mrb, mbed_mod, "wait_ms", mrb_mbed_wait_ms, ARGS_REQ(1));
  mrb_define_method(mrb, mbed_mod, "wait_us", mrb_mbed_wait_us, ARGS_REQ(1));
}

mrb_value mrb_mbed_wait(mrb_state* mrb, mrb_value self) {
  float seconds;
  mrb_get_args(mrb, "f", &seconds);
  wait(seconds);
  return mrb_nil_value();
}

mrb_value mrb_mbed_wait_ms(mrb_state* mrb, mrb_value self) {
  int milliseconds;
  mrb_get_args(mrb, "i", &milliseconds);
  wait_ms(milliseconds);
  return mrb_nil_value();
}

mrb_value mrb_mbed_wait_us(mrb_state* mrb, mrb_value self) {
  int microseconds;
  mrb_get_args(mrb, "i", &microseconds);
  wait_ms(microseconds);
  return mrb_nil_value();
}

#endif
