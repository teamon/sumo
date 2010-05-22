require "socket"

s = TCPSocket.open("10.0.0.105", 30_000)

while line = readline
  s.write(line)
end

s.close
