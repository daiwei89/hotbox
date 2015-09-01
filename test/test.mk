

TEST_DIR = $(BUILD)/test
TEST_SRC = $(shell find test -type f -name "*.cpp")
TEST_BIN = $(patsubst test/%.cpp, $(TEST_DIR)/%, $(TEST_SRC))
TEST_INCFLAGS = -I$(PROJECT)

$(TEST_DIR)/%: test/%.cpp $(MLDB_LIB)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS) $(HDFS_INCFLAGS) \
		$(TEST_INCFLAGS) $(HDFS_LDFLAGS)  $< -lgtest $(MLDB_LIB) -o $@

test: $(TEST_BIN) transform_test one_hot_transform_test datum_util_test

transform_test: $(TEST_BIN)
	$(TEST_DIR)/transform/schema_util_test

one_hot_transform_test: $(TEST_BIN)
	$(TEST_DIR)/transform/one_hot_transform_test

datum_util_test: $(TEST_BIN)
	$(TEST_DIR)/transform/datum_util_test
