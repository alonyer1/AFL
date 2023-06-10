if __name__ == "__main__":
    nums = [0, 1, 3, 6, 7, 10, 14, 20, 22, 28, 31, 47, 50]
    for i in range(len(nums)):
        print(hex(nums[i]*64+i*4096))