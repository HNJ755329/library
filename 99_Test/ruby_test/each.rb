# frozen_string_literal: true

(0..10).reverse_each do |i|
  print i
end
puts
(0..10).reverse_each { |x| print x }
puts
('a'..'z').each { |c| print c }
puts
