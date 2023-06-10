#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#define MSR_IA32_SPEC_CTRL 0x00000048
#define MSR_IA32_PRED_CMD  0x00000049
#define MSR_IA32_PREFETCHER 0x1A4
static inline void write_msr(int msr_fd, uint32_t msr, uint64_t value) {
    if (pwrite(msr_fd, &value, sizeof(value), msr) != sizeof(value)) {
        perror("Failed to write to MSR");
    }
}

int disable_prefetching() {
    int msr_fd = open("/dev/cpu/3/msr", O_RDWR);
    uint64_t data = 0;
    // Read the current value of the MSR
    if (msr_fd < 0) {
        perror("Failed to open /dev/cpu/3/msr");
        exit(1);
    }

    if (pread(msr_fd, &data, sizeof(data), MSR_IA32_PREFETCHER) != sizeof(data)) {
        perror("pread");
        return 1;
    }
    data = data | (1ULL << 3);
    write_msr(msr_fd, MSR_IA32_PREFETCHER, data);
}

void prediction_wall() {
    int msr_fd = open("/dev/cpu/3/msr", O_WRONLY);
    if (msr_fd < 0) {
        perror("Failed to open /dev/cpu/3 /msr");
        exit(1);
    }
    // Enable IBRS
    write_msr(msr_fd, MSR_IA32_SPEC_CTRL, 1);
    // Execute IBPB
    write_msr(msr_fd, MSR_IA32_PRED_CMD, 1);
    close(msr_fd);
}