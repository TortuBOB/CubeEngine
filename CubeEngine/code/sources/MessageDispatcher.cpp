

// Laura Rosas


#include "../headers/MessageDispatcher.hpp"


void MessageDispatcher::Register(std::string id, std::shared_ptr<MessageObserver> observer)
{
	observers.insert(std::pair<std::string, std::shared_ptr<MessageObserver>>(id, observer));
}

void MessageDispatcher::Send(Message message)
{
	messages.push(message);
}

void MessageDispatcher::Run()
{
	while (!messages.empty()) 
	{
		//El primer mensaje
		Message message = messages.front();

		//Se busca el observer al que va dirigido
		auto target = observers.find(message.target)->second;

		//Si hay que ejecute su acción
		if (target) 
		{
			target->Handle(message);
		}

		//Se elimina el mensaje
		messages.pop();

	}
}
