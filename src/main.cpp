#include <iostream>
#include <vector>
#include <memory> // std::unique_ptr
#include <warehouse/core/PerishableProduct.hpp>
#ifdef _WIN32
#include <windows.h> // Нужно только для Windows
#endif
int main() {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "=== SmartWarehouse-ARM-DAS: Core Engine v0.1.0 ===\n\n";

    try {
        // Создаем скоропортящиеся товары
        warehouse::core::PerishableProduct milk("MILK-101", "Молоко 3.2%", 2.50, 40, 10);
        warehouse::core::PerishableProduct yogurt("YOG-202", "Йогурт Греческий", 3.00, 20, 2);

        milk.printInfo();
        yogurt.printInfo();

        std::cout << "\n Тестирование операции списания...\n";
        milk.decreaseQuantity(15);
        std::cout << "После списания 15 шт. молока:\n";
        milk.printInfo();

        std::cout << "\n Проверка перехвата бизнес-ошибки (попытка списать 1000 шт.):\n";
        milk.decreaseQuantity(1000); // Бросит исключение!

    } catch (const std::exception& ex) {
        std::cerr << "Уведомление системы: " << ex.what() << '\n';
    }

    return 0;
}