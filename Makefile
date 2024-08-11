.PHONY: clean all ti92p

all: ti92p

ti92p:
	$(MAKE) -C bin/ti92p

clean:
	$(MAKE) -C bin/ti92p clean
