.PHONY: clean all ti92p

all: ti92p ti89 ti83p

ti92p:
	$(MAKE) -C bin/ti92p

ti89:
	$(MAKE) -C bin/ti89

ti83p:
	$(MAKE) -C bin/ti83p

clean:
	$(MAKE) -C bin/ti92p clean
	$(MAKE) -C bin/ti89 clean
