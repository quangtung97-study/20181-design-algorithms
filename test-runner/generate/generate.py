import numpy as np
import os

for test_case in range(20, 30):
    n = 200000
    min_value = -1000000000
    max_value = 1000000001
    x = np.random.randint(min_value, max_value)
    rand = np.random.randint(min_value, max_value, size=n)
    rand = map(lambda a: str(a), rand)
    s = " ".join(rand)

    path = "../test/" + str(test_case)
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

    os.system("./program < " + input_path + " > " + output_path)
