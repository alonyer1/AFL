inputs=("in0.txt" "in1.txt" "in2.txt" "in3.txt" "in4.txt" "in5.txt" "in6.txt" "in7.txt" "in8.txt" "in9.txt" "in10.txt" "in11.txt")
nums=("00" "0" "1" "2" "3" "4" "5" "6" "7" "8" "9" "10" "11")
for i in ${nums[@]}; do
    #perf record -o perfresults/perf-$i.data --exclude-perf -e branch-misses:u,branches:u -- ./oracle inputs/in$i.txt results/nocpuid-$i.txt 100000
    ./oracle inputs/in$i.txt results/cache3-$i.txt 100000
    echo "File $i done"
done

#perf record -o perfresults/perf-cache.data -g --freq=max -e cache-misses,branches -- ./oracle inputs/in10.txt results/outtmp.txt 100000
#perf record -o perf.data -e branch-misses:u,branches:u -- ./oracle in0.txt huge.txt 100