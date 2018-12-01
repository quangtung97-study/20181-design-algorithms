import numpy as np
import os

test_case = 7
n = 20000
x = 1
A = np.full([n], 3)
A = map(lambda a: str(a), A)
s = " ".join(A)

path = "../test/0" + str(test_case)
try:
    os.mkdir(path)
except FileExistsError:
    pass
input_path = path + "/input"
output_path = path + "/output"

with open(input_path, "w") as f:
    f.write("%d %d\n" % (n, x))
    f.write(s)
    f.write("\n")

A = np.full([n + 1], 0)
A[0] = int(n * (n + 1) / 2)

A = map(lambda a: str(a), A)
s = " ".join(A)
with open(output_path, "w") as f:
    f.write(s)
    f.write("\n")
