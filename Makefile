CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -I.
TARGET = college_erp
TEST_TARGET = test_runner

SRCS = main.cpp \
       modules/Authentication.cpp \
       modules/Award.cpp \
       modules/AwardManager.cpp \
       modules/Bill.cpp \
       modules/BillingManager.cpp \
       modules/Course.cpp \
       modules/Faculty.cpp \
       modules/FacultyManager.cpp \
       modules/Fee.cpp \
       modules/FeeManager.cpp \
       modules/ReportManager.cpp \
       modules/SearchManager.cpp \
       modules/Student.cpp \
       modules/StudentManager.cpp \
       utils/Logger.cpp \
       utils/Utilities.cpp \
       utils/Validator.cpp \
       storage/Deserializer.cpp \
       storage/FileManager.cpp \
       storage/Serializer.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): tests/test_datastructures.cpp
	$(CXX) $(CXXFLAGS) tests/test_datastructures.cpp -o $(TEST_TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(TEST_TARGET)

.PHONY: all clean test
