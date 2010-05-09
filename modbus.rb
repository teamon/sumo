require "rubygems"
require "serialport"

sp = SerialPort.open("/dev/cu.usbserial-FTSXYJMG", 9600)

Thread.new do
  loop do
    puts ">>> " + sp.readline
  end
end 

while cmd = readline
    sp.write "$" + cmd.chomp.split(/ +/).join.ljust(5) + "\r\n"
end
