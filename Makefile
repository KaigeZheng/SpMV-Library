CXX		 = g++
# To be modified
INCLUDE_DIR	 = /home/kambri/SpMV/LibSpMV
SRC		 = test_demo.cpp
TARGET		 = test_demo
OPTIMIZATION 	 = -O3 -march=native -fopenmp
CXXFLAGS	 = $(OPTIMIZATION) -I$(INCLUDE_DIR)

all:$(TARGET)

$(TARGET):$(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
