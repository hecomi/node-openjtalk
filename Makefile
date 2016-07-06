OS = ${shell uname}
MODULE_DIR = ${shell pwd}
HTSENGINE_DIR = $(MODULE_DIR)/lib/hts_engine_API-1.10/
OPENJTALK_DIR = $(MODULE_DIR)/lib/open_jtalk-1.09/

all: htsengine openjtalk

htsengine:
	cd $(HTSENGINE_DIR) && \
	./configure && \
	make

openjtalk:
	cd $(OPENJTALK_DIR) && \
	./configure --with-charset=UTF-8 \
		--with-hts-engine-header-path=$(HTSENGINE_DIR)/include \
		--with-hts-engine-library-path=$(HTSENGINE_DIR)/lib && \
	make
	mkdir -p $(MODULE_DIR)/bin
	cp $(OPENJTALK_DIR)/bin/open_jtalk $(MODULE_DIR)/bin/.

clean:
	rm -rf $(MODULE_DIR)/node_modules
	rm -rf $(MODULE_DIR)/build
	rm -rf $(MODULE_DIR)/bin
	cd $(OPENJTALK_DIR) && make distclean
	cd $(HTSENGINE_DIR) && make distclean
