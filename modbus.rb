require "rubygems"
require "serialport"

def hex(s,n)
  i = s.to_i
  if i > 0
    i.to_s(16).rjust(n, '0')
  else
    ((-i).to_s(2).rjust(n*4, '0').split(//).map {|e| e == '0' ? '1' : '0' }.join.to_i(2) + 1).to_s(16)
  end.upcase
end

sp = SerialPort.open("/dev/cu.usbserial-FTSXYJMG", 9600)

Thread.new do
  loop do
    puts sp.readline
  end
end 


while cmd = readline
  parts = cmd.chomp.split(/ +/)
  
  fun = parts[0] ? parts[0].to_s.upcase : "00"
  args = case fun
  when "E0" then [hex(parts[1],2)]
  when "E1" then [hex(parts[1],2)]
  when "Q" then
    fun = "A0"
    [hex(parts[1],2), hex(parts[2],2), hex(parts[3],4)]
  end
  
  args ||= []
  cmd = "$" + fun + args.join.ljust(8, '0') + "\r\n"
  puts "   sending: " + cmd
  sp.write cmd
end
