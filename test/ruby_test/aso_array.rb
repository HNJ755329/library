# frozen_string_literal: false

# associative array
# in Ruby, associative array is called hash.

cnt = {}
('a'..'z').to_a.each do |c|
  cnt[c] = 0
end
cnt['b'] += 1
puts cnt['b']
puts cnt
