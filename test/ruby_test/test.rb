# frozen_string_literal: true

t = gets.chomp.gsub(/\*/, '[a-z]')
t = /^#{t}$/
puts t
