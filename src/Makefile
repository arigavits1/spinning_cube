GLAD_SRC := glad.c

CXX := g++
CXXFLAGS := -std=c++11 -I/usr/include/imgui -I/usr/include/imgui/backends -g -Wall -Wformat
LDFLAGS := -lglfw -lGL -lX11 -lpthread -lXrandr -ldl && ./main

all: main

main: main.o shaders.o imgui_obj/imgui.o imgui_obj/imgui_demo.o imgui_obj/imgui_draw.o imgui_obj/imgui_tables.o imgui_obj/imgui_widgets.o imgui_obj/imgui_impl_glfw.o imgui_obj/imgui_impl_opengl3.o $(GLAD_SRC)
	$(CXX) -o main objects/main.o objects/shaders.o imgui_obj/imgui.o imgui_obj/imgui_demo.o imgui_obj/imgui_draw.o imgui_obj/imgui_tables.o imgui_obj/imgui_widgets.o imgui_obj/imgui_impl_glfw.o imgui_obj/imgui_impl_opengl3.o $(GLAD_SRC) $(CXXFLAGS) $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o objects/main.o main.cpp

shaders.o: shaders.cpp
	$(CXX) $(CXXFLAGS) -c -o objects/shaders.o shaders.cpp

clean:
	rm -f main objects/*.o
