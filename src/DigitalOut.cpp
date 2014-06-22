#include <mruby.h>
#include <mruby/class.h>
#include <mruby/value.h>
#include <mruby/data.h>
#include "mbed.h"

#ifndef MRBMBED_DISABLE_DIGITAL_OUT

mrb_value mrb_digital_out_initialize(mrb_state* mrb, mrb_value self);
mrb_value mrb_digital_out_write(mrb_state* mrb, mrb_value self);
mrb_value mrb_digital_out_read(mrb_state* mrb, mrb_value self);

void define_digital_out(mrb_state* mrb, struct RClass* mbed_mod) {
  // creating class DigitalOut
  struct RClass *digital_out_class = mrb_define_class_under(mrb, mbed_mod, "DigitalOut", NULL);
  MRB_SET_INSTANCE_TT(digital_out_class, MRB_TT_DATA);
  mrb_define_method(mrb, digital_out_class, "initialize", mrb_digital_out_initialize, ARGS_REQ(1) | ARGS_OPT(1));
  mrb_define_method(mrb, digital_out_class, "write", mrb_digital_out_write, ARGS_REQ(1));
  mrb_define_method(mrb, digital_out_class, "read", mrb_digital_out_read, ARGS_NONE());
}

void digital_out_free(mrb_state* mrb, void* pointer) {
  DigitalOut* obj = static_cast<DigitalOut*>(pointer);
  delete obj;
}

const struct mrb_data_type mrb_digital_out_type = { "DigitalOut", digital_out_free };

mrb_value mrb_digital_out_initialize(mrb_state* mrb, mrb_value self) {
  DigitalOut* obj;
  int pin;
  int value;
  int n_args = mrb_get_args(mrb, "i", &pin, &value);
  if (n_args == 2) {
    obj = new DigitalOut((PinName)pin, value);
  } else {
    obj = new DigitalOut((PinName)pin);
  }
  DATA_TYPE(self) = &mrb_digital_out_type;
  DATA_PTR(self) = obj;
  return self;
}

mrb_value mrb_digital_out_write(mrb_state* mrb, mrb_value self) {
  DigitalOut* obj = static_cast<DigitalOut*>(DATA_PTR(self));
  int value;
  mrb_get_args(mrb, "i", &value);
  obj->write(value);
  return mrb_nil_value();
}

mrb_value mrb_digital_out_read(mrb_state* mrb, mrb_value self) {
  DigitalOut* obj = static_cast<DigitalOut*>(DATA_PTR(self));
  int value;
  value = obj->read();
  return mrb_fixnum_value(value);
}

#endif
