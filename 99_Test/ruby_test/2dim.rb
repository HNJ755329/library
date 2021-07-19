h = 5
w = 3
# arr = [[0] * h] * w
# arr[1][0] = 5
# p arr
# -> [[5, 0, 0, 0, 0], [5, 0, 0, 0, 0], [5, 0, 0, 0, 0]]
# すべて中身が同じになるのでよくない
arr = Array.new(h) { Array.new(w, 0) }
arr[0][2] = 5
p arr
h.times do |i|
  w.times do |j|
    arr[i][j] = i * j
  end
end
p arr
