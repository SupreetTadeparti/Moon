#include "Window.hpp"
#include "Renderer.hpp"

namespace Moon
{
	GLFWwindow* Window::s_Window;
	Uint Window::s_Width = 640;
	Uint Window::s_Height = 360;
	String Window::s_Title = "Moon Application";
	Vec3 Window::s_BackgroundColor(0, 0, 0);

	Int Window::Init()
	{
		if (!glfwInit())
		{
			return -1;
		}
		return 0;
	}

	const Char* Window::GetKeyName(Int key) {
		const Char* str = glfwGetKeyName(key, 0);
		if (str) return str;
		switch (key) {
			case GLFW_KEY_SPACE: return " ";
			case GLFW_KEY_LEFT_SHIFT: return "LSHIFT";
			case GLFW_KEY_RIGHT_SHIFT: return "RSHIFT";
			case GLFW_KEY_ESCAPE: return "ESCAPE";
			case GLFW_KEY_ENTER: return "ENTER";
			default: return "(UNKNOWN)";
		}
	}

	void Window::KeyCallback(GLFWwindow* window, Int key, Int scancode, Int action, Int mods)
	{
		EventHandler::Push(new Event((action == GLFW_PRESS ? EventType::KeyDown : action == GLFW_REPEAT ? EventType::KeyRepeat : EventType::KeyUp), static_cast<void*>(new String(GetKeyName(key)))));
	}

	void Window::MessageCallback(Uint source, Uint type, Uint id, Uint severity, Int length, const Char* message, const void* data)
	{
		MoonLogError(message);
	}

	Int Window::Create()
	{
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		s_Window = glfwCreateWindow(s_Width, s_Height, s_Title.c_str(), NULL, NULL);

		if (!s_Window)
		{
			Close();
			return -1;
		}

		glfwMakeContextCurrent(s_Window);

		if (glewInit() != GLEW_OK)
		{
			Close();
			return -2;
		}

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, NULL);

		glfwSetKeyCallback(s_Window, KeyCallback);

		return 0;
	}
	
	void Window::Close()
	{
		glfwTerminate();
	}

	void Window::Update()
	{
		glfwSwapBuffers(s_Window);
		glfwPollEvents();
		if (glfwWindowShouldClose(s_Window))
		{
			EventHandler::Push(new Event(EventType::WindowClose, (EventData)nullptr));
			return;
		}
	}

	void Window::SetBackgroundColor(Float r, Float g, Float b)
	{
		Renderer::SetBackgroundColor(Vec3(r / 255, g / 255, b / 255));
	}

	void Window::SetTitle(const String& title)
	{
		s_Title = title;
	}

	void Window::SetDimensions(Uint width, Uint height)
	{
		s_Width = width;
		s_Height = height;
	}
}