# mruby-mbed: mruby binding of mbed library

## about
mruby-mbed is a mruby binding of mbed library.
It currently supports only STM32 Nucleo F401RE board.

## examples
### LED blink
```ruby
led = Mbed::DigitalOut.new(Mbed::LED1)
while true
  led.write 1
  wait 1
  led.write 0
  wait 1
end
```

## how to build
1. clone and build [mbed-sdk](https://github.com/mbedmicro/mbed)
2. edit mrbgem.rake
  1. change MBED_DIR variable (``/path/to/mbed``) into your mbed-sdk directory
  2. change CTAGS_BIN variable (``/path/to/ctags``) into the path of your Exuberant Ctags binary
3. add ``conf.gem "/path/to/mruby-mbed"`` into your mruby directory
4. ``make``

## TODO
* documentation
