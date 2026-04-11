# Solver script for the C symexec challenge, you can use angr as well but Z3 works fine here since it does not require actively looking for correct branches, rather the correct/applicable input for the challenge.
from z3 import *
s = Solver()

# create password representation, each index is just a character/u8
passw = [BitVec(f'c{i}', 8) for i in range(17)]

# add constraints, bitvector is basically a u8 type, so you can only compare with integers
s.add(passw[0] == ord('R'))
s.add(passw[5] == ord('_'))
s.add(passw[5] == passw[10])
s.add(passw[1] == passw[7]+1)
s.add(passw[2] == (passw[1] + 69))
s.add(passw[3] == (passw[1] + 2))
s.add(passw[4] == ord('n'))
s.add(passw[6] == passw[1])
s.add(passw[7] == ((1 << 5)+16))
s.add(passw[8] == passw[7])
s.add(passw[9] == passw[8])
s.add(passw[11]^10 == 92)
s.add(passw[12] == 79)
s.add(passw[12] - passw[13] == 6)
s.add(passw[14] == 67)
s.add(passw[15] == 69)
s.add(passw[16]*passw[15] == 5727)

# at this point, passw has a bunch of u8 values with the right character, we just have to print them all out now
s.check()
sol = s.model()
flag = [sol[c].as_long() for c in passw]
flag = ''.join(chr(f) for f in flag)
print(flag)
