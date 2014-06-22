def generate_enum_defs(input, output)
  in_file = File.open(input, "r")
  out_file = File.open(output, "w")
  enumerators = []
  while (line = in_file.gets) != nil
    if /^[a-zA-Z0-9_]+/ =~ line
      enumerators << $&
    end
  end

  out_file.puts <<EOF
#include <mruby.h>
#include <mruby/value.h>
#include "mbed.h"

void define_enumerators(mrb_state* mrb, struct RClass* klass) {
EOF

  enumerators.each do |name|
    upcase_name = name.dup
    upcase_name[0] = name[0].upcase
    out_file.puts "  mrb_define_const(mrb, klass, \"#{upcase_name}\", mrb_fixnum_value(#{name}));"
  end

  out_file.puts "}"
  in_file.close
  out_file.close
end
