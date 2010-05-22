require "rubygems"
require "serialport"

module Modbus
  def init
    @sp = SerialPort.open("/dev/cu.usbserial-FTSXYJMG", 9600)
    
    Thread.new do
      loop do
        line = @sp.readline
        (line =~ /INFO/ ? STDOUT : STDERR).puts line
      end
    end
  end
  
  def front(time)
    q(20, 20, time)
  end
  alias_method :f, :front
  
  def back(time)
    q(-20, -20, time)
  end
  alias_method :b, :back
  
  def left(time)
    q(-20, 20, time)
  end
  alias_method :l, :left
  
  def right(time)
    q(20, -20, time)
  end
  alias_method :r, :right
  
  def e0(power)
    write("E0", hex(power, 2))
  end
  
  def e1(power)
    write("E1", hex(power, 2))
  end
  
  def q(e0, e1, time)
    write("A0", hex(e0, 2), hex(e1, 2), hex(time, 4))
  end
    
  def write(fun, *args)
    cmd = "$" + fun + args.join.ljust(8, '0') + "\r\n"
    @sp.write(cmd)
    cmd
  end
  
  def hex(i, n)
    # i = s.to_i
    if i >= 0
      i.to_s(16).rjust(n, '0')
    else
      ((-i).to_s(2).rjust(n*4, '0').split(//).map {|e| e == '0' ? '1' : '0' }.join.to_i(2) + 1).to_s(16)
    end.upcase
  end
end




