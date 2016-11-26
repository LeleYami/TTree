CFLAGS=$(shell root-config --cflags)
LDFLAGS=-L /home/luole/root/root/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic -L. -lMymath 
all:libMymath.so read_write

read_write:read_write.o Mymath.o
	g++ -L. -o $@ $^ $(LDFLAGS)

libMymath.so:Mymath.o MymathDict.o
	g++ -shared -o $@ $^ $(LDFLAGS)

Mymath.cpp:Mymath.h

MymathDict.cpp:Mymath.h LinkDef.h
	rootcint -f $@ -c $^

%.o:%.cpp
	g++ -c -fPIC -o $@ $^ $(CFLAGS)

#######################################
#Run the command
#######################################
run_read_write:read_write
       @LD_LIBRARAY_PATH=.:${LD_LIBRARY_PATH} ./read_write
