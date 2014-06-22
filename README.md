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

## TODO
* documentation
