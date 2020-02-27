require "serialport"

sample_file = 'Makeblock-pencil G-code examples.cnc'

port_str = "/dev/tty.usbmodem1421"  #may be different for you
baud_rate = 115200
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE

sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)

file = File.open(sample_file)

begin
  file.each do |line|
    sp.write(line)
    puts "#{line}\n\r"
    sleep 0.1
  end
rescue Exception => e
  puts e
  sp.close
  return
end

sp.close
