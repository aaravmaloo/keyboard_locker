CXX = x86_64-w64-mingw32-g++
TARGET = klock.exe
SRC = klock.cpp

RELEASE_FLAGS = -O3 -march=native -flto -ffunction-sections -fdata-sections \
                -fno-exceptions -fno-rtti -fno-stack-protector \
                -mwindows -s -DNDEBUG

LDFLAGS = -Wl,--gc-sections -Wl,--strip-all -static -luser32 -ladvapi32

release:
	$(CXX) $(RELEASE_FLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
