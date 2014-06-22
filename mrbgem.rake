MBED_DIR = "/path/to/mbed"
CTAGS_BIN = "/path/to/ctags"
MRuby::Gem::Specification.new('mruby-mbed') do |spec|
  require dir + "/generate_enum_defs"
  spec.license = "hoge"
  spec.author = "tana"
  spec.version = "0.1"

  mbed_include_dir = MBED_DIR + "/libraries"

  spec.cxx.include_paths += %w(mbed mbed/api mbed/common mbed/hal mbed/targets mbed/targets/cmsis mbed/targets/cmsis/TARGET_STM mbed/targets/cmsis/TARGET_STM/TARGET_NUCLEO_F401RE mbed/targets/cmsis/TARGET_STM/TARGET_NUCLEO_F401RE/TOOLCHAIN_GCC_ARM mbed/targets/hal mbed/targets/hal/TARGET_STM mbed/targets/hal/TARGET_STM/TARGET_NUCLEO_F401RE).map {|relpath| mbed_include_dir + "/" + relpath }
  float_abi = "softfp"
  cpu = %w(-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16) + ["-mfloat-abi=" + float_abi]
  spec.cxx.flags += cpu + %w(-c -g -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections)
  spec.cxx.flags += %w(-DTARGET_NUCLEO_F401RE -DTARGET_M4 -DTARGET_STM -DTARGET_STM32F -DTARGET_STM32F401RE -DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC -D__CORTEX_M4 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DMBED_BUILD_TIMESTAMP=1402726702.6 -D__MBED__=1 -DTARGET_FF_ARDUINO -DTARGET_FF_MORPHO)
  spec.linker.library_paths << MBED_DIR + "/build/mbed/TARGET_NUCLEO_F401RE/TOOLCHAIN_GCC_ARM"
  spec.linker.libraries << "mbed"

  # Generating constant definitions for pins
  ctags = CTAGS_BIN
  pin_names = MBED_DIR + "/libraries/mbed/targets/hal/TARGET_STM/TARGET_NUCLEO_F401RE/PinNames.h"
  `#{ctags} -f #{dir + "/tags"} --c-kinds=e #{pin_names}`
  generate_enum_defs(dir + "/tags", dir + "/src/enum_defs.cpp")
end
