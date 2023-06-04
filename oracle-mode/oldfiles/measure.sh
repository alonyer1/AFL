for ((cpu=0; cpu<8; cpu++)); do
        G=/sys/devices/system/cpu/cpu$cpu/cpufreq/scaling_governor
        [ -f $G ] && echo 'performance' | sudo tee $G
done
echo '77' | sudo tee /proc/irq/default_smp_affinity
echo '-1' | sudo tee /proc/sys/kernel/perf_event_paranoid
grep 'cpu MHz' /proc/cpuinfo