desc "TODO"
task :todo do
  Dir["**/*.cpp"].each do |f|
    File.open(f, "r").readlines.each_with_index do |l, i|
      puts "[#{f}:#{i+1}] #{$1}" if l =~ /\/\/ ?TODO: ?(.+)/
    end
  end
end