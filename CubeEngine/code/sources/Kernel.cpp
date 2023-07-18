

// Laura Rosas


#include "../headers/Kernel.hpp"
#include "../headers/RenderSystem.hpp"


Kernel::Kernel()
{
}

void Kernel::Run()
{
	while (!exit) 
	{
		for (auto task: tasks) 
		{
			task->Run();
		}
	}
}

void Kernel::AddTask(std::shared_ptr<Task> newTask)
{
	tasks.emplace_back(newTask);
}

void Kernel::StopLoop()
{
	exit = true;
}
