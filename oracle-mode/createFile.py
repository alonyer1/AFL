if __name__ == "__main__":
    with open("dwall.s", "w") as asmfile:
        asmfile.write('''.global dwall\n.section .text\n\ndwall:\n''')
        for lineno in range(10000):
            asmfile.write('''jmp .label''' + str(lineno) + "\n.label"+ str(lineno) + ":\n")
        asmfile.write('''ret\n''')
    