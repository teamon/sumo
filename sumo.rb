require "modbus"

include Modbus

init

while line = readline
  args = line.split
  fun = args.shift
  begin
    send(fun, *args.map{|e| e.to_i})
  rescue Exception => e
    puts e
  end
end