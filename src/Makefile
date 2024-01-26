GLAD_SRC := glad.c

CXX := g++
CXXFLAGS := -std=c++11 -I/usr/include/imgui -I/usr/include/imgui/backends -g -Wall -Wformat
LDFLAGS := -lglfw -lGL -lX11 -lpthread -lXrandr -ldl && ./main

all: main

main: main.o shaders.o vao.o vbo.o ebo.o window.o texture.o UserInterface.o Entity.o imgui_obj/imgui.o imgui_obj/imgui_demo.o imgui_obj/imgui_draw.o imgui_obj/imgui_tables.o imgui_obj/imgui_widgets.o imgui_obj/imgui_impl_glfw.o imgui_obj/imgui_impl_opengl3.o $(GLAD_SRC)
	$(CXX) -o main objects/main.o objects/shaders.o objects/vao.o objects/vbo.o objects/ebo.o objects/window.o objects/texture.o objects/UserInterface.o objects/Entity.o imgui_obj/imgui.o imgui_obj/imgui_demo.o imgui_obj/imgui_draw.o imgui_obj/imgui_tables.o imgui_obj/imgui_widgets.o imgui_obj/imgui_impl_glfw.o imgui_obj/imgui_impl_opengl3.o $(GLAD_SRC) $(CXXFLAGS) $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o objects/main.o main.cpp

shaders.o: shaders.cpp
	$(CXX) $(CXXFLAGS) -c -o objects/shaders.o shaders.cpp

vao.o: VAO.cpp
	$(CXX) $(CXXFLAGS) -c -o objects/vao.o VAO.cpp

vbo.o: VBO.cpp
	$(CXX) $(CXXFLAGS) -c -o objects/vbo.o VBO.cpp

ebo.o: EBO.cpp
	$(CXX) $(CXXFLAGS) -c -o objects/ebo.o EBO.cpp

window.o: window.cpp
	$(CXX) $(CXXFLAGS) -c -o objects/window.o window.cpp

texture.o: texture.cpp
	$(CXX) $(CXXFLAGS) -c -o objects/texture.o texture.cpp

UserInterface.o: UserInterface.cpp
	$(CXX) $(CXXFLAGS) -c -o objects/UserInterface.o UserInterface.cpp

Entity.o : Entity.cpp
	$(CXX) $(CXXFLAGS) -c -o objects/Entity.o Entity.cpp

clean:
	rm -f main objects/*.o
