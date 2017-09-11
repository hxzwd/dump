In = open("suz_24_23_1.txt", "r")
In2 = open("dkv_30_21_1.txt", "r")
In_ = open("suz_24_23_1.txt", "r")
In2_ = open("dkv_30_21_1.txt", "r")

Out = open("In_.txt", "w+")
Out2 = open("Out_.txt", "w+")

cnt = 0
flag = 0

In_.readline()
In2_.readline()
while cnt < 600:
	In.readline()
	In2.readline()
	In_.readline()
	In2_.readline()
	cnt = cnt + 1
while cnt < 1300:
	x = In.readline().strip()
	y = In2.readline().strip()
	Out.write(x + " " + y + "\n")
	a = In_.readline().strip()
	b = In2_.readline().strip()
	Out2.write(a + " " + b + "\n")
	cnt = cnt + 1

In.close()
Out.close()
In2.close()
Out2.close()
In2_.close()
In_.close()
