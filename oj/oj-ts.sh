# online-judgement-toolをまとめる
function oj-s-cpp() {
    tmp_file="submit.cpp"
    path_library="/home/yasu/Documents/library"
    submit_file=$1
    echo "--- oj submit cpp ---"
    echo "$(pwd)/"$submit_file
    echo "--- oj submit cpp ---"
    oj-bundle -I $path_library $submit_file > $tmp_file
    oj s $tmp_file -y --no-open -w 0
    rm $tmp_file
    echo $(oj-bundle -I $path_library $submit_file >$tmp_file)
    echo $(oj s $tmp_file -y --no-open -w 0)
    echo $(rm $tmp_file)

    echo "--- oj submit cpp ---"
    echo "$(pwd)/"$submit_file
    echo "--- oj submit cpp ---"
}

function oj-t-cpp() {
    test_file=$1
    echo "--- oj test cpp ---"
    echo "$(pwd)/"$test_file
    echo "--- oj test cpp ---"
    g++ -std=c++17 -O2 -Wall -Wextra -DONLINE_JUDGE $test_file
    timeout 3 oj t -c ./a.out
    echo $(g++ -std=c++17 -O2 -Wall -Wextra -DONLINE_JUDGE -I $path_library $test_file)
    echo $(timeout 3 oj t -c ./a.out)

    echo "--- oj test cpp ---"
    echo "$(pwd)/"$test_file
    echo "--- oj test cpp ---"
}
