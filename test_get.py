import subprocess
import time

output = open("output.csv", "a")
output.seek(2, 0)

output.write("\n\n , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10\n")

args = []
exe = ["bin/recognizer", "-get"]
output.write("\n")

for test in range(1, 41):
    output.write("test " + str(test))
    for k in range(0, 11):
        for ref in range(1, 41):
            args.append("img/patterns/s" + str(ref) + "/p" + str(k) + ".pat")
        args.append("img/orl_faces/s" + str(test) + "/10.pgm")
        
        start = time.time()
        subprocess.call(exe + args)
        end = time.time()
        output.write(";" + str(end-start).replace(".", ","));

        # for i in (exe+args):
        #     print(i, end = ' ')
        # print("")
        args = []

output.close()