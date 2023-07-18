

// Laura Rosas


#include <iostream>

#include "../headers/InputTask.hpp"
#include "../headers/Keyboard.hpp"

using namespace engine;


InputTask::InputTask()
{
	window = nullptr;
	messageDispatcher = nullptr;
}

InputTask::InputTask(Window* win)
{
	window = win;
	messageDispatcher = nullptr;
}

void InputTask::Run()
{
	Window::Event event;

	while (window->poll(event)) 
	{
		switch (event.type)
		{
		case Window::Event::CLOSE:
		{
			Message mes = Message("Close");
			messageDispatcher->Send(mes);
			break;
		}
		case Window::Event::KEY_PRESSED:
		{
			if (event.data.keyboard.key_code == Keyboard::KEY_W)
			{
				Message mes = Message("Player");
				mes.action = 'u';
				messageDispatcher->Send(mes);
			}
			else if (event.data.keyboard.key_code == Keyboard::KEY_A)
			{
				Message mes = Message("Player");
				mes.action = 'l';
				messageDispatcher->Send(mes);
			}
			else if (event.data.keyboard.key_code == Keyboard::KEY_S)
			{
				Message mes = Message("Player");
				mes.action = 'd';
				messageDispatcher->Send(mes);
			}
			else if (event.data.keyboard.key_code == Keyboard::KEY_D)
			{
				Message mes = Message("Player");
				mes.action = 'r';
				messageDispatcher->Send(mes);
			}

			break;
		}
		case Window::Event::KEY_RELEASED: 
		{
			if (event.data.keyboard.key_code == Keyboard::KEY_W ||
				event.data.keyboard.key_code == Keyboard::KEY_S)
			{
				Message mes = Message("Player");
				mes.action = 'z';
				messageDispatcher->Send(mes);
			}
			else if (event.data.keyboard.key_code == Keyboard::KEY_A ||
				event.data.keyboard.key_code == Keyboard::KEY_D)
			{
				Message mes = Message("Player");
				mes.action = 'x';
				messageDispatcher->Send(mes);
			}

			break;
		}
	}
	
	}
}

void InputTask::SetMessageDispatcher(std::shared_ptr<MessageDispatcher> mDispatcher)
{
	messageDispatcher = mDispatcher;
}

