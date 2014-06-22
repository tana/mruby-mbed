#include <mruby.h>
#include <mruby/class.h>
#include <mruby/value.h>
#include <mruby/data.h>
#include "mbed.h"

#ifndef MRBMBED_DISABLE_PWM_OUT

mrb_value mrb_pwm_out_initialize(mrb_state* mrb, mrb_value self);
mrb_value mrb_pwm_out_write(mrb_state* mrb, mrb_value self);
mrb_value mrb_pwm_out_read(mrb_state* mrb, mrb_value self);
mrb_value mrb_pwm_out_period(mrb_state* mrb, mrb_value self);
mrb_value mrb_pwm_out_period_ms(mrb_state* mrb, mrb_value self);
mrb_value mrb_pwm_out_period_us(mrb_state* mrb, mrb_value self);
mrb_value mrb_pwm_out_pulsewidth(mrb_state* mrb, mrb_value self);
mrb_value mrb_pwm_out_pulsewidth_ms(mrb_state* mrb, mrb_value self);
mrb_value mrb_pwm_out_pulsewidth_us(mrb_state* mrb, mrb_value self);

void define_pwm_out(mrb_state* mrb, struct RClass* mbed_mod) {
  // creating class PwmOut
  struct RClass *pwm_out_class = mrb_define_class_under(mrb, mbed_mod, "PwmOut", NULL);
  MRB_SET_INSTANCE_TT(pwm_out_class, MRB_TT_DATA);
  mrb_define_method(mrb, pwm_out_class, "initialize", mrb_pwm_out_initialize, ARGS_REQ(1));
  mrb_define_method(mrb, pwm_out_class, "write", mrb_pwm_out_write, ARGS_REQ(1));
  mrb_define_method(mrb, pwm_out_class, "read", mrb_pwm_out_read, ARGS_NONE());
  mrb_define_method(mrb, pwm_out_class, "period", mrb_pwm_out_period, ARGS_REQ(1));
  mrb_define_method(mrb, pwm_out_class, "period_ms", mrb_pwm_out_period_ms, ARGS_REQ(1));
  mrb_define_method(mrb, pwm_out_class, "period_us", mrb_pwm_out_period_us, ARGS_REQ(1));
  mrb_define_method(mrb, pwm_out_class, "pulsewidth", mrb_pwm_out_pulsewidth, ARGS_REQ(1));
  mrb_define_method(mrb, pwm_out_class, "pulsewidth_ms", mrb_pwm_out_pulsewidth_ms, ARGS_REQ(1));
  mrb_define_method(mrb, pwm_out_class, "pulsewidth_us", mrb_pwm_out_pulsewidth_us, ARGS_REQ(1));
}

void pwm_out_free(mrb_state* mrb, void* pointer) {
  PwmOut* obj = static_cast<PwmOut*>(pointer);
  delete obj;
}

const struct mrb_data_type mrb_pwm_out_type = { "PwmOut", pwm_out_free };

mrb_value mrb_pwm_out_initialize(mrb_state* mrb, mrb_value self) {
  PwmOut* obj;
  int pin;
  mrb_get_args(mrb, "i", &pin);
  obj = new PwmOut((PinName)pin);
  DATA_TYPE(self) = &mrb_pwm_out_type;
  DATA_PTR(self) = obj;
  return self;
}

mrb_value mrb_pwm_out_write(mrb_state* mrb, mrb_value self) {
  PwmOut* obj = static_cast<PwmOut*>(DATA_PTR(self));
  mrb_float value;
  mrb_get_args(mrb, "f", &value);
  obj->write((float)value);
  return mrb_nil_value();
}

mrb_value mrb_pwm_out_read(mrb_state* mrb, mrb_value self) {
  PwmOut* obj = static_cast<PwmOut*>(DATA_PTR(self));
  float value;
  value = obj->read();
  return mrb_float_value(mrb, (mrb_float)value);
}

mrb_value mrb_pwm_out_period(mrb_state* mrb, mrb_value self){
  PwmOut* obj = static_cast<PwmOut*>(DATA_PTR(self));
  mrb_float seconds;
  mrb_get_args(mrb, "f", &seconds);
  obj->period((float)seconds);
  return mrb_nil_value();
}

mrb_value mrb_pwm_out_period_ms(mrb_state* mrb, mrb_value self){
  PwmOut* obj = static_cast<PwmOut*>(DATA_PTR(self));
  int milliseconds;
  mrb_get_args(mrb, "i", &milliseconds);
  obj->period_ms(milliseconds);
  return mrb_nil_value();
}

mrb_value mrb_pwm_out_period_us(mrb_state* mrb, mrb_value self){
  PwmOut* obj = static_cast<PwmOut*>(DATA_PTR(self));
  int microseconds;
  mrb_get_args(mrb, "i", &microseconds);
  obj->period_us(microseconds);
  return mrb_nil_value();
}

mrb_value mrb_pwm_out_pulsewidth(mrb_state* mrb, mrb_value self){
  PwmOut* obj = static_cast<PwmOut*>(DATA_PTR(self));
  mrb_float seconds;
  mrb_get_args(mrb, "f", &seconds);
  obj->pulsewidth((float)seconds);
  return mrb_nil_value();
}

mrb_value mrb_pwm_out_pulsewidth_ms(mrb_state* mrb, mrb_value self){
  PwmOut* obj = static_cast<PwmOut*>(DATA_PTR(self));
  int milliseconds;
  mrb_get_args(mrb, "i", &milliseconds);
  obj->pulsewidth_ms(milliseconds);
  return mrb_nil_value();
}

mrb_value mrb_pwm_out_pulsewidth_us(mrb_state* mrb, mrb_value self){
  PwmOut* obj = static_cast<PwmOut*>(DATA_PTR(self));
  int microseconds;
  mrb_get_args(mrb, "i", &microseconds);
  obj->pulsewidth_us(microseconds);
  return mrb_nil_value();
}

#endif
