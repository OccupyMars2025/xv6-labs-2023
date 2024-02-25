
def check_pte(pte: int):
    print("bit[63:54]: {}".format(pte >> 54))
    print("PPN(44bits): {}".format(hex((pte & (2**54 - 1)) >> 10)))
    flags = pte & (2**10 - 1)
    print("flags(10bits): {}".format(bin(flags)))
    
    RSW = (flags & (3 << 8)) >> 8
    D = (flags & (1 << 7)) >> 7
    A = (flags & (1 << 6)) >> 6
    G = (flags & (1 << 5)) >> 5
    U = (flags & (1 << 4)) >> 4
    X = (flags & (1 << 3)) >> 3
    W = (flags & (1 << 2)) >> 2
    R = (flags & (1 << 1)) >> 1
    V = flags & 1
    print("RSW:{} D:{} A:{} G:{} U:{} X:{} W:{} R:{} V:{}".format(RSW, D, A, G, U, X, W, R, V))
    print("\n\n")




if __name__ == "__main__":
    """
    https://pdos.csail.mit.edu/6.1810/2023/lec/l-QA1.txt

     page table 0x0000000087f6b000
       ..0: pte 0x0000000021fd9c01 pa 0x0000000087f67000
       .. ..0: pte 0x0000000021fd9801 pa 0x0000000087f66000
       .. .. ..0: pte 0x0000000021fda01b pa 0x0000000087f68000  (text)
       .. .. ..1: pte 0x0000000021fd9417 pa 0x0000000087f65000  (data)
       .. .. ..2: pte 0x0000000021fd9007 pa 0x0000000087f64000  (guard)
       .. .. ..3: pte 0x0000000021fd8c17 pa 0x0000000087f63000  (stack)

       one interesting thing:
       for the pte of the guard page, we have 
       RSW:0 D:0 A:0 G:0 U:0 X:0 W:1 R:1 V:1
       Just clear "U" bit !  but "V" bit is set !
    """
    pte_list = [0x0000000021fda01b, 0x0000000021fd9417, 0x0000000021fd9007, 0x0000000021fd8c17]
    for pte in pte_list:
        check_pte(pte)


    """
       ..255: pte 0x0000000021fda801 pa 0x0000000087f6a000
       .. ..511: pte 0x0000000021fda401 pa 0x0000000087f69000
       .. .. ..509: pte 0x0000000021fdcc13 pa 0x0000000087f73000  (usyscall)
       .. .. ..510: pte 0x0000000021fdd007 pa 0x0000000087f74000  (trapframe)
       .. .. ..511: pte 0x0000000020001c0b pa 0x0000000080007000  (trampoline)
    """
    pte_list_002 = [0x0000000021fdcc13, 0x0000000021fdd007, 0x0000000020001c0b]
    for pte in pte_list_002:
        check_pte(pte)