# flags and libaries
CFLAGS   := $(shell root-config --cflags)
RLIBS     := $(shell root-config --libs) -lXMLIO -lRooFitCore -lRooFit -lRooStats -lTMVA -lHistFactory -lTreePlayer 
#-lRooGaussExp -lRooGaussDoubleSidedExp -lHggTwoSidedCBPdf
# Programs
CC          = LC_ALL=en_US g++
CFLAGS      += -g -Wall -L ./lib 
LFLAGS      = -g 

# directories
IDIR      = -Isrc -Iinc
LDIR      = lib
BDIR      = bin

# Add variables
CFLAGS    += $(ROOTCFLAGS)
CFLAGS    += $(IDIR)

# Direct to make the directories with the sources:
VPATH  = ./lib / ./bin ./src ./inc

############################################################################
# General rules.

#$@ and $^ are the left and right sides of the :, respectively
#$< is the first item in the dependencies list

############################################################################
%.o : %.cxx %.h
	@echo "compiling $<"
	@$(CC) $(CFLAGS) -c $<

%.o : %.cxx
	@echo "compiling $<"
#	@echo "CFLAGS: $(CFLAGS)" 
#	@echo "RLIBS: $(RLIBS)"
	@$(CC) $(CFLAGS) -c $< 

%    : %.o
	@echo "compiling and linking $@"
	@$(CC) $(CFLAGS) $^ \
	        $(RLIBS)  -o $@
	@if [ `ls | grep "\.o"$  | wc -l` != 0 ]; then mv *.o  $(LDIR)/; fi
	@mv $@ $(BDIR)


MyDict.cxx: $(HEADERS) Linkdef.h 
	@rootcling -f $@ -c $(CXXFLAGS) -p $^
 
libMyLib.so: MyDict.cxx $(SOURCES)
	@g++ -shared -o$@ `root-config --ldflags` $(CXXFLAGS) -I$(ROOTSYS)/include $^
############################################################################
# Phony rules
############################################################################

.PHONY: clean

clean :
	@rm -f $(BDIR)/* $(LDIR)/* ./*.o 
