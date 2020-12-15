// OS Lab 5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "Process.h"
#include "Task.h"
#include <random>
#include <ctime>

int main()
{
    srand(time(NULL));
    std::vector<Process> processes;

    double even_all_time=0, even_time_loss=0, even_reactivity=0, even_loss = 0;

    int processes_amount;
    int time_limit;
    int user_choice;
    bool end = 0;
    int quarks = 0;

    do
    {
        std::cout << "Enter amount of processes\n";
        std::cin >> processes_amount;
    } while (processes_amount<1||processes_amount>100);

    do
    {
        std::cout << "Enter time limit for processes\n";
        std::cin >> time_limit;
    } while (time_limit < 1 || time_limit>1000);

    for (int i=0;i<processes_amount;i++) 
        processes.push_back(Process(rand() % (time_limit*2), rand() % (time_limit)+1));

    for (auto i = processes.begin(); i != processes.end(); i++)
        (*i).print(std::cout);

    do
    {
        std::cout << "1.Use HPRN\n2.Use RR\n";
        std::cin >> user_choice;
    } while (user_choice < 0 || user_choice>2);

    while (!end)
    {
        end = 1;
        for (auto i = processes.begin(); i != processes.end(); i++)
        {
            if ((*i).get_state() != Process::stat::end) end = 0;
            if ((*i).get_appear_time() == quarks) (*i).activate();
        }
        if (end == 1) break;

        switch (user_choice)
        {
        case 1:
            HPRN(processes);
            break;
        case 2:
            RR(processes);
            break;
        }

        std::cout << quarks<<":";
        for (auto i = processes.begin(); i != processes.end(); i++)
            std::cout <<" "<< (*i).get_state();
        std::cout << std::endl;
        quarks++;
    }
    for (int i = 0; i < processes.size(); i++)
    {
        even_all_time += processes[i].get_system_time();
        even_time_loss += processes[i].get_lost_time();
        even_reactivity += (double(processes[i].get_system_time()) - processes[i].get_lost_time()) / processes[i].get_system_time();
        even_loss += (double(processes[i].get_system_time())) / (double(processes[i].get_system_time())-processes[i].get_lost_time());
        std::cout << "Process " << i << ": " << processes[i]<<std::endl;
    }
    std::cout << "Even time for process " << even_all_time / processes.size() << " Even time loss " << even_time_loss / processes.size() << " Even reactivity " << even_reactivity / processes.size() << " Even loss " << even_loss / processes.size()<<std::endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
