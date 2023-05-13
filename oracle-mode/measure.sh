for ((cpu=0; cpu<8; cpu++)); do
        G=/sys/devices/system/cpu/cpu$cpu/cpufreq/scaling_governor
        [ -f $G ] && echo 'performance' | sudo tee $G
done
grep 'cpu MHz' /proc/cpuinfo