files=("DanSingle" "DanMulti")
for str in ${files[@]}; do
    perf stat -o perf-$str-large.txt -e branches:u,branch-misses:u -C 3 -- ./$str in1.txt $str-large.txt 100000
done