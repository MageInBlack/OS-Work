#pragma once
#include <iostream>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>
namespace PAC
{
	std::queue<int> buffer;
	static const unsigned int bufferSize = 5;

	class Producer_And_Consumer
	{
	private:

		std::mutex mtx;
		std::condition_variable condition;
		bool isWorking = true;
		void Consumer();
		void Producer(unsigned int);
	public:
		void Invoke();
	};

}

void PAC::Producer_And_Consumer::Producer(unsigned int operations)
{
	for (unsigned int i = operations; i > 0; i--)
	{
		std::unique_lock<std::mutex> lock(this->mtx);//Оборотка Мьютекса
		this->condition.wait(lock, []() {return bufferSize != buffer.size(); });//Ожидать освобождения буфера
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); //%Enter_Work_Here%
		buffer.push(i);//Добавить элемент
		std::cout << "Operative " << i << " is available\n";
		lock.unlock();//Освободить Мьютекс
		this->condition.notify_one();//Сообщить потоку
	}
	this->isWorking = false;//Закончить работу производителя
	std::cout << "Worker thread finished working\n";
}

void PAC::Producer_And_Consumer::Consumer()
{
	while (this->isWorking||buffer.size()>0)
	{
		std::unique_lock<std::mutex> lock(this->mtx);//Оборотка мьютекса
		this->condition.wait(lock, []() {return buffer.size() != 0; });//Ожидать наличия
		int operative = buffer.front();//считать передний элемента
		buffer.pop();
		std::cout << "Operative " << operative << " is consumed\n";
		lock.unlock();//Освободить мьютекс
		this->condition.notify_one();//Сообщить потоку
	}
	std::cout << "Consumer thread eliminated\n";
}

void PAC::Producer_And_Consumer::Invoke()
{
	std::thread Producer(&Producer_And_Consumer::Producer, &(*this), 100);
	std::thread Consumer(&Producer_And_Consumer::Consumer, &(*this));

	Producer.join();
	Consumer.join();
}