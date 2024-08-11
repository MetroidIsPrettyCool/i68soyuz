.PHONY: clean all ti92p

all: ti92p ti89

ti92p:
	$(MAKE) -C bin/ti92p

ti89:
	$(MAKE) -C bin/ti89

clean:
	$(MAKE) -C bin/ti92p clean
	$(MAKE) -C bin/ti89 clean
