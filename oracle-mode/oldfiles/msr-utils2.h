#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#define MSR_IA32_SPEC_CTRL 0x00000048
#define MSR_IA32_PRED_CMD  0x00000049

static inline void write_msr(int msr_fd, uint32_t msr, uint64_t value) {
    if (pwrite(msr_fd, &value, sizeof(value), msr) != sizeof(value)) {
        perror("Failed to write to MSR");
    }
}

void prediction_wall() {
    int msr_fd = open("/dev/cpu/0/msr", O_WRONLY);
    if (msr_fd < 0) {
        perror("Failed to open /dev/cpu/0/msr");
        exit(1);
    }
    // Enable IBRS
    write_msr(msr_fd, MSR_IA32_SPEC_CTRL, 1);
    // Execute IBPB
    write_msr(msr_fd, MSR_IA32_PRED_CMD, 1);
    close(msr_fd);
}