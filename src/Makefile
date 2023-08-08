GLAD_SRC := glad.cpp

CXX := g++
CXXFLAGS := -std=c++11 -I/usr/include/imgui -I/usr/include/imgui/backends -g -Wall -Wformat
LDFLAGS := -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl && ./main

all: main

main: main.o imgui.o imgui_demo.o imgui_draw.o imgui_tables.o imgui_widgets.o imgui_impl_glfw.o imgui_impl_opengl3.o $(GLAD_SRC)
	$(CXX) -o main main.o imgui.o imgui_demo.o imgui_draw.o imgui_tables.o imgui_widgets.o imgui_impl_glfw.o imgui_impl_opengl3.o $(GLAD_SRC) $(CXXFLAGS) $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp

imgui.o: /usr/include/imgui/imgui.cpp
	$(CXX) $(CXXFLAGS) -c -o imgui.o /usr/include/imgui/imgui.cpp

imgui_demo.o: /usr/include/imgui/imgui_demo.cpp
	$(CXX) $(CXXFLAGS) -c -o imgui_demo.o /usr/include/imgui/imgui_demo.cpp

imgui_draw.o: /usr/include/imgui/imgui_draw.cpp
	$(CXX) $(CXXFLAGS) -c -o imgui_draw.o /usr/include/imgui/imgui_draw.cpp

imgui_tables.o: /usr/include/imgui/imgui_tables.cpp
	$(CXX) $(CXXFLAGS) -c -o imgui_tables.o /usr/include/imgui/imgui_tables.cpp

imgui_widgets.o: /usr/include/imgui/imgui_widgets.cpp
	$(CXX) $(CXXFLAGS) -c -o imgui_widgets.o /usr/include/imgui/imgui_widgets.cpp

imgui_impl_glfw.o: /usr/include/imgui/imgui_impl_glfw.cpp
	$(CXX) $(CXXFLAGS) -c -o imgui_impl_glfw.o /usr/include/imgui/imgui_impl_glfw.cpp

imgui_impl_opengl3.o: /usr/include/imgui/imgui_impl_opengl3.cpp
	$(CXX) $(CXXFLAGS) -c -o imgui_impl_opengl3.o /usr/include/imgui/imgui_impl_opengl3.cpp

clean:
	rm -f main *.o
