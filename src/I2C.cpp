#include <mruby.h>
#include <mruby/class.h>
#include <mruby/value.h>
#include <mruby/data.h>
#include "mbed.h"

#ifndef MRBMBED_DISABLE_I2C

mrb_value mrb_i2c_initialize(mrb_state* mrb, mrb_value self);
mrb_value mrb_i2c_frequency(mrb_state* mrb, mrb_value self);
mrb_value mrb_i2c_read_string(mrb_state* mrb, mrb_value self);
mrb_value mrb_i2c_read(mrb_state* mrb, mrb_value self);
mrb_value mrb_i2c_write_string(mrb_state* mrb, mrb_value self);
mrb_value mrb_i2c_write(mrb_state* mrb, mrb_value self);
mrb_value mrb_i2c_start(mrb_state* mrb, mrb_value self);
mrb_value mrb_i2c_stop(mrb_state* mrb, mrb_value self);

void define_i2c(mrb_state* mrb, struct RClass* mbed_mod) {
  // creating class I2C
  struct RClass *i2c_class = mrb_define_class_under(mrb, mbed_mod, "I2C", NULL);
  MRB_SET_INSTANCE_TT(i2c_class, MRB_TT_DATA);
  mrb_define_method(mrb, i2c_class, "initialize", mrb_i2c_initialize, ARGS_REQ(2));
  mrb_define_method(mrb, i2c_class, "frequency", mrb_i2c_frequency, ARGS_REQ(1));
  // String read_string(Fixnum address, Fixnum length, Bool repeated=false)
  // if failure it returns nil
  mrb_define_method(mrb, i2c_class, "read_string", mrb_i2c_read_string, ARGS_REQ(2) | ARGS_OPT(1));
  mrb_define_method(mrb, i2c_class, "read", mrb_i2c_read, ARGS_REQ(1));
  // Fixnum write_string(Fixnum address, String data,  Bool repeated=false)
  // returns 0 on success, non-0 on fail (same as mbed)
  mrb_define_method(mrb, i2c_class, "write_string", mrb_i2c_write_string, ARGS_REQ(2) | ARGS_OPT(1));
  mrb_define_method(mrb, i2c_class, "read", mrb_i2c_read, ARGS_REQ(1));
  mrb_define_method(mrb, i2c_class, "start", mrb_i2c_start, ARGS_NONE());
  mrb_define_method(mrb, i2c_class, "stop", mrb_i2c_stop, ARGS_NONE());
}

void i2c_free(mrb_state* mrb, void* pointer) {
  I2C* obj = static_cast<I2C*>(pointer);
  delete obj;
}

const struct mrb_data_type mrb_i2c_type = { "I2C", i2c_free };

mrb_value mrb_i2c_initialize(mrb_state* mrb, mrb_value self) {
  I2C* obj;
  int sda, scl;
  mrb_get_args(mrb, "ii", &sda, &scl);
  obj = new I2C((PinName)sda, (PinName)scl);
  DATA_TYPE(self) = &mrb_i2c_type;
  DATA_PTR(self) = obj;
  return self;
}

mrb_value mrb_i2c_frequency(mrb_state* mrb, mrb_value self) {
  I2C* obj = static_cast<I2C*>(DATA_PTR(self));
  int freq;
  mrb_get_args(mrb, "i", &freq);
  obj->frequency(freq);
  return mrb_nil_value();
}

mrb_value mrb_i2c_read_string(mrb_state* mrb, mrb_value self) {
  // this func allocates memory and copies a string
  I2C* obj = static_cast<I2C*>(DATA_PTR(self));
  int addr, length;
  mrb_bool repeated;
  int nargs = mrb_get_args(mrb, "ii|b", &addr, &length, &repeated);
  char* data = (char*)mrb_malloc(mrb, length);
  if (nargs == 3) {
    obj->read(addr, data, length, repeated);
  } else {
    obj->read(addr, data, length);
  }
  mrb_free(mrb, data);
  return mrb_str_new(mrb, data, length);
}

mrb_value mrb_i2c_read(mrb_state* mrb, mrb_value self) {
  I2C* obj = static_cast<I2C*>(DATA_PTR(self));
  int ack;
  int data;
  mrb_get_args(mrb, "i", &ack);
  data = obj->read(ack);
  return mrb_fixnum_value(data);
}

mrb_value mrb_i2c_write_string(mrb_state* mrb, mrb_value self) {
  I2C* obj = static_cast<I2C*>(DATA_PTR(self));
  int addr;
  char* data;
  int length;
  mrb_bool repeated;
  int result;
  int nargs = mrb_get_args(mrb, "is|b", &addr, &data, &length, &repeated);
  if (nargs == 3) {
    result = obj->write(addr, data, length, repeated);
  } else {
    result = obj->write(addr, data, length);
  }
  return mrb_fixnum_value(result);
}

mrb_value mrb_i2c_write(mrb_state* mrb, mrb_value self) {
  I2C* obj = static_cast<I2C*>(DATA_PTR(self));
  int data, result;
  mrb_get_args(mrb, "i", &data);
  result = obj->write(data);
  return mrb_fixnum_value(result);
}

mrb_value mrb_i2c_start(mrb_state* mrb, mrb_value self) {
  I2C* obj = static_cast<I2C*>(DATA_PTR(self));
  obj->start();
  return mrb_nil_value();
}

mrb_value mrb_i2c_stop(mrb_state* mrb, mrb_value self) {
  I2C* obj = static_cast<I2C*>(DATA_PTR(self));
  obj->stop();
  return mrb_nil_value();
}

#endif
