
HOME = /home/geet
NOWARN= -Wno-deprecated

#myincludes = -I $(HOME)/library/ -I $(HOME)/RobustFlow/src/ -I $(HOME)/RobustFlow/src/
myincludes = -I $(HOME)/scsi/cpeg/ -I $(HOME)/scsi/opflow/ -I $(HOME)/lib/  $(NOWARN)
SRCDIR = ./
LIBPATH = -L$(HOME)/scsi/cpeg -L$(HOME)/lib -L./ $(NOWARN)

LIBS = -L/usr/lib/X11 -L/usr/X11R6/lib -lXext -lX11 -lm -lmpeg -limg 

OBJDIR = ./.dshelf


SRC =  
	
	
OTHEROBJs1 = $(OTHERSRCs1:%.cpp=$(OBJDIR)/%.o)
	
	
MAINS = viewColor.cpp	colorConv.cpp	binRead.cpp
MAINOBJS = $(MAINS:%.cpp=$(OBJDIR)/%.o)
OBJS = $(SRC:%.cpp=$(OBJDIR)/%.o)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp 
		
	@echo " Target _______________ $@ "
	@echo " Changed dependencies = $? " 
		
	g++ -g -c $<  $(myincludes) $(NOWARN) -o $@ 
		
		
	
libimg : imgutil.cpp imgutil1.cpp imgutil2.cpp imgutil.h 
		
		g++ -g -c imgutil.cpp -Wno-deprecated
		ar ruv libimg.a imgutil.o
	
xmlParser.o:		xmlParser.cpp
		g++ -g -c	xmlParser.cpp	-o xmlParser.o 

schemaParser.o:		schemaParser.cpp
		g++ -g -c schemaParser.cpp  -o schemaParser.o 

libxml.a: xmlParser.cpp schemaParser.cpp

		g++ -g -c	xmlParser.cpp		-o 	xmlParser.o  $(NOWARN)
		g++ -g -c 	schemaParser.cpp  	-o 	schemaParser.o $(NOWARN)
		ar ruv libxml.a xmlParser.o schemaParser.o 
clean: 
	rm -Rf ./*.o
	rm -Rf ./libxml.a
	rm -Rf ./libimg.a
