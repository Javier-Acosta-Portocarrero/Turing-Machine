CXX = g++
CXXFLAGS = -std=c++23
TARGET = build/turing_machine

SOURCES = src/instantaneous_description.cc \
          src/transition_function.cc \
          src/turing_machine_string.cc \
          src/turing_machine.cc \
          src/turing_machine_load/turing_machine_loader.cc \
          src/turing_machine_load/turing_machine_loader_plain_text_strategy.cc \
          src/main.cc \
		  src/main_functions.cc

OBJECTS = $(SOURCES:%.cc=build/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

build/%.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build/*

cleano:
	rm -rf build/src

.PHONY: all clean cleano