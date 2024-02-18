.PHONY : all clean test
#target setup
target_name = fibonacciHeap
headers_name = fibonacciHeap

#dirs setup
src_dir := sources/
header_dir := headers/
build_dir := bin/
test_dir := tests/

#CC setup
CC := clang++
debug_flags := #-fsanitize=address -fsanitize=undefined -fsanitize=leak
	

target := $(addprefix $(src_dir), $(target_name)) 
target := $(addsuffix .cpp, $(target))

objects := $(addprefix $(build_dir), $(target_name))
objects := $(addsuffix .o, $(objects))

headers := $(addprefix $(header_dir), $(headers_name)) 
headers := $(addsuffix .h, $(headers)) 



all : $(build_dir) $(objects)

$(build_dir) : 
	mkdir $(build_dir)

$(objects) : $(target) $(headers) 
	$(CC) -c $(target) -o $(objects) $(debug_flags) 


#test setup
test_files := $(wildcard $(test_dir)*.cpp)
# TODO
test_files := $(test_files:.cpp=.out)


test : $(test_files) 
	@echo "All test passed"

$(test_files) : %.out: $(target) $(headers) $(objects)
	$(CC) $*.cpp $(objects) -o $*.out -lgtest -lgtest_main $(debug_flags)
	$*


clean : 
	rm -f $(objects)
	rm -f $(test_files)