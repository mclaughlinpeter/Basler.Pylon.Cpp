PROG = pylon_example
SRCS = main.cpp camerabasler.cpp
OBJS = $(SRCS:.cpp=.o)

CLEANFILES = $(PROG)
INSTALL_DIR = ./install_artifact/usr/local/bin

CXXFLAGS += -Wall -Wl,-rpath,/opt/pylon/lib -std=c++17
CXXFLAGS += -I$(SDKTARGETSYSROOT)/usr/include/opencv4 -I$(SDKTARGETSYSROOT)/opt/pylon/include -DVERBOSE
LDFLAGS += -L$(SDKTARGETSYSROOT)/usr/lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui
LDFLAGS += -L$(SDKTARGETSYSROOT)/opt/pylon/lib -lpylonbase -lpylonutility -lGenApi_gcc_v3_1_Basler_pylon -lGCBase_gcc_v3_1_Basler_pylon

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(PROG)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(PROG)
 
clean:
	rm -f $(CLEANFILES) $(patsubst %.cpp,%.o, $(SRCS)) *~

install: $(PROG)
	mkdir -p $(INSTALL_DIR)
	install $(PROG) $(INSTALL_DIR)
