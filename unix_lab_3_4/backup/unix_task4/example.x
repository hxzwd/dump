/* example.x: remote message printing protocol */
program EXAMPLEPROG {
	version EXAMPLEPROGVERS {
		int PRINTMSG(string) = 1;
		} = 1;
} = 0x20000001;
