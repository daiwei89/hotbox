# Assuming this Makefile lives in project root directory
PROJECT := $(shell readlink $(dir $(lastword $(MAKEFILE_LIST))) -f)

include $(PROJECT)/config.mk

#BUILD := $(PROJECT)/build
BUILD :=build

SRC_DIR:=$(PROJECT)/src

LIB = $(BUILD)/lib

NEED_MKDIR = $(BUILD) $(LIB)

all: proto hotbox_lib test

path: $(NEED_MKDIR)

$(NEED_MKDIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD)
	rm -r db_testbed

.PHONY: all path clean

CXX = g++
CXXFLAGS += -O2 \
           -std=c++11 \
           -Wall \
					 -Wno-sign-compare \
           -fno-builtin-malloc \
           -fno-builtin-calloc \
           -fno-builtin-realloc \
           -fno-builtin-free \
           -fno-omit-frame-pointer \
					 -DDMLC_USE_GLOG=1 \
	   -fPIC 

THIRD_PARTY = $(PROJECT)/third_party
THIRD_PARTY_SRC = $(THIRD_PARTY)/src
THIRD_PARTY_INCLUDE = $(THIRD_PARTY)/include
THIRD_PARTY_LIB = $(THIRD_PARTY)/lib
THIRD_PARTY_BIN = $(THIRD_PARTY)/bin
BOOST_INC = /usr/include
BOOST_LIB = /usr/lib

#INCFLAGS =  -Isrc/ -I$(THIRD_PARTY_INCLUDE)
INCFLAGS =  -I$(SRC_DIR) -I$(THIRD_PARTY_INCLUDE)
INCFLAGS += -Ibuild/ # include generated *pb.h
INCFLAGS += -I$(JAVA_HOME)/include # include java for HDFS/DMLC access
INCFLAGS += $(HDFS_INCFLAGS)
PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)
INCFLAGS += -I$(PYTHON_INCLUDE)
INCFLAGS += -I$(BOOST_INC)
INCFLAGS += -L$(BOOST_LIB)

LDFLAGS = -Wl,-rpath,$(THIRD_PARTY_LIB) \
		  -Wl,-rpath=$(LIBJVM) \
          -L$(THIRD_PARTY_LIB) \
          -L$(LIBJVM) -ljvm \
          -lpthread -lrt -lnsl \
          -lzmq \
          -lglog \
          -lgflags \
          -ltcmalloc \
					-lprotobuf \
					-D_GLIBCXX_USE_NANOSLEEP \
					-lboost_filesystem \
					-lboost_system \
					-lpthread \
					-lyaml-cpp \
					-lsnappy \
          -ldmlc \
          -lhdfs \
          -lrocksdb 

HB_SRC = $(shell find src -type f -name "*.cpp")
HB_PROTO = $(shell find src -type f -name "*.proto")
HB_HEADERS = $(shell find src -type f -name "*.hpp")

###
PROTO_HDRS = $(patsubst src/%.proto, build/%.pb.h, $(HB_PROTO))
PROTO_OBJS = $(patsubst src/%.proto, build/%.pb.o, $(HB_PROTO))
HB_OBJS = $(patsubst src/%.cpp, build/%.o, $(HB_SRC))

PROTOC = $(THIRD_PARTY_BIN)/protoc

$(PROTO_HDRS): $(BUILD)/%.pb.h: $(SRC_DIR)/%.proto
	@mkdir -p $(@D)
	LD_LIBRARY_PATH=$(THIRD_PARTY_LIB) \
	$(PROTOC) --cpp_out=$(BUILD) --python_out=$(BUILD) --proto_path=$(SRC_DIR) $<
	
$(HB_LIB): $(PROTO_OBJS) $(HB_OBJS)
	@echo HB_LIB_
	mkdir -p $(@D)
	LD_LIBRARY_PATH=$(THIRD_PARTY_LIB) \
	ar csrv $@ $(filter %.o, $?)
	# Make $(BUILD)/ into a python module.
	python $(PROJECT)/python/util/modularize.py $(BUILD)
	
$(PROTO_OBJS): %.pb.o: %.pb.cc
	@echo PROTO_OBJS_
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

$(HB_OBJS): $(BUILD)/%.o: $(SRC_DIR)/%.cpp
	@echo HB_OBJS_
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

proto:$(PROTO_HDRS)

$PY_CLIENT_SRC=$(shell find src/client/py_client -type f -name "*.cpp")
py_hb_client: $(HB_LIB)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS) -shared -Wl,--export-dynamic $(PY_CLIENT_SRC) -L./build/lib -lhotbox -lboost_python -L/usr/lib/python2.7/config -lpython2.7 -o py_hb_client.so
spark_exp_server: experiment/spark_exp/server/spark_exp.pb.cc experiment/spark_exp/server/spark_exp.pb.h experiment/spark_exp/server/server.cpp $(HB_LIB)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) experiment/spark_exp/server/server.cpp experiment/spark_exp/server/spark_exp.pb.cc experiment/spark_exp/server/spark_exp.pb.h $(HB_LIB) $(LDFLAGS) -o spark_exp_server
hotbox_lib: path proto $(HB_LIB)

include $(PROJECT)/test/test.mk
