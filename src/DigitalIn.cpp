#include <mruby.h>
#include <mruby/class.h>
#include <mruby/value.h>
#include <mruby/data.h>
#include "mbed.h"

#ifndef MRBMBED_DISABLE_DIGITAL_IN

mrb_value mrb_digital_in_initialize(mrb_state* mrb, mrb_value self);
mrb_value mrb_digital_in_read(mrb_state* mrb, mrb_value self);
mrb_value mrb_digital_in_mode(mrb_state* mrb, mrb_value self);

void define_digital_in(mrb_state* mrb, struct RClass* mbed_mod) {
  // creating class DigitalIn
  struct RClass *digital_in_class = mrb_define_class_under(mrb, mbed_mod, "DigitalIn", NULL);
  MRB_SET_INSTANCE_TT(digital_in_class, MRB_TT_DATA);
  mrb_define_method(mrb, digital_in_class, "initialize", mrb_digital_in_initialize, ARGS_REQ(1) | ARGS_OPT(1));
  mrb_define_method(mrb, digital_in_class, "read", mrb_digital_in_read, ARGS_NONE());
  mrb_define_method(mrb, digital_in_class, "mode", mrb_digital_in_mode, ARGS_REQ(1));
}

void digital_in_free(mrb_state* mrb, void* pointer) {
  DigitalIn* obj = static_cast<DigitalIn*>(pointer);
  delete obj;
}

const struct mrb_data_type mrb_digital_in_type = { "DigitalIn", digital_in_free };

mrb_value mrb_digital_in_initialize(mrb_state* mrb, mrb_value self) {
  DigitalIn* obj;
  int pin;
  int mode;
  int n_args = mrb_get_args(mrb, "i", &pin, &mode);
  if (n_args == 2) {
    obj = new DigitalIn((PinName)pin, (PinMode)mode);
  } else {
    obj = new DigitalIn((PinName)pin);
  }
  DATA_TYPE(self) = &mrb_digital_in_type;
  DATA_PTR(self) = obj;
  return self;
}

mrb_value mrb_digital_in_read(mrb_state* mrb, mrb_value self) {
  DigitalIn* obj = static_cast<DigitalIn*>(DATA_PTR(self));
  int value;
  value = obj->read();
  return mrb_fixnum_value(value);
}

mrb_value mrb_digital_in_mode(mrb_state* mrb, mrb_value self) {
  DigitalIn* obj = static_cast<DigitalIn*>(DATA_PTR(self));
  int pull;
  mrb_get_args(mrb, "i", &pull);
  obj->mode((PinMode)pull);
  return mrb_nil_value();
}

#endif
