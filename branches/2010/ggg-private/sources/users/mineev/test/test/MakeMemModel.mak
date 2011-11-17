 
source_dirs := . Editor TextLine

    search_wildcards := $(addsuffix /*.cpp,$(source_dirs)) 

    iEdit: $(notdir $(patsubst %.cpp,%.o,$(wildcard $(search_wildcards))))
        gcc $^ -o $@ 

    VPATH := $(source_dirs)
     
    %.o: %.cpp
        gcc -c -MD $(addprefix -I,$(source_dirs)) $<

    include $(wildcard *.d) 