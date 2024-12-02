#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>


std::atomic<int> client_count{ 0 };
const int max_clients = 10;

void client_function() {
    for (int i = 0; i < max_clients; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        client_count++;
        std::cout << "Клиент пришел. Всего клиентов: " << client_count.load() << std::endl;
    }
}

void operator_function() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (client_count > 0) {
            client_count--;
            std::cout << "Клиент ушел. Осталось: " << client_count.load() << std::endl;
        }
        else {
            std::cout << "Нет клиентов." << std::endl;
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::thread client_thread(client_function);
    std::thread operator_thread(operator_function);

    client_thread.join();
    operator_thread.join();

    std::cout << "Конец." << std::endl;
    return 0;
}
