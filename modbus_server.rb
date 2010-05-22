include Modbus

init

# socket
require 'socket'               

server = TCPServer.open(30_000)  
loop do                 
  client = server.accept
  
  while line = client.readline
    puts "got: #{line}"
    args = line.split()
    fun = args.shift
    send(fun, *args.map{|e| e.to_i}) rescue nil
  end
  
  client.puts "Closing the connection. Bye!"
  client.close
end
