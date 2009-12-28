desc "TODO"
task :todo do
  a = Dir["src/**/*"].map { |f|
    File.open(f, "r").readlines.map.with_index { |l, i|
      l =~ /\/\/ ?TODO: ?(.+)/ && [f, i+1, $1]
    }
  }.flatten(1).select{|e| e}
  max = a.map {|e| "#{e[0]}#{e[1]}".length }.max
  a.each {|f,l,t|
    puts "#{"#{f}:#{l}".ljust(max+1)} #{t}"
  }
end