In = open("suz_24_23.txt", "r")
Out = open("suz_24_23_1.txt", "w+")


for lines in In:
	Out.write(lines.split()[3] + "\n")

In.close()
Out.close()
