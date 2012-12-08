OS = ${shell uname}
HTSENGINE_DIR = ${shell pwd}/lib/hts_engine_API-1.06/
OPENJTALK_DIR = ${shell pwd}/lib/open_jtalk-1.05/

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
	cp $(OPENJTALK_DIR)/bin/open_jtalk bin/.

