
all:
	make -C WebServer/
	make -C test/

clean:
	make -C WebServer/ clean
	make -C test/ clean

re:	clean all

