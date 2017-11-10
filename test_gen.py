import subprocess
import time

output = open("output.csv", "a")
output.seek(2, 0)

output.write(" ; 0; 1; 2; 3; 4; 5; 6; 7; 8; 9; 10\n")

args = []
exe = ["bin/recognizer", "-gen"]

for person in range(1, 41):
    output.write("s" + str(person))
    for k in range(0, 11):
        for photo in range(1, 10):
            args.append("img/orl_faces/s" + str(person) + "/" + str(photo) + ".pgm")
        args.append(str(k))
        args.append("img/patterns/s" + str(person) + "/p" + str(k) + ".pat")

        for i in (exe+args):
            print(i, end = ' ')
        print("")

        start = time.time()
        subprocess.call(exe + args)
        end = time.time()
        output.write(";" + str(end-start).replace(".", ","));

        args = []
    output.write("\n")

output.close()