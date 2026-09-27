#pragma once

#include <string>
#include <string_view>
#include <iostream>

namespace warehouse::core {

class Product {
private:
    std::string m_sku;       // Артикул товара (SKU)
    std::string m_name;      // Наименование
    double m_basePrice{0.0}; // Базовая стоимость за единицу
    int m_quantity{0};       // Текущий остаток на складе

public:
    // Конструктор: строковые параметры принимаются по std::string_view
    Product(std::string_view sku, std::string_view name, double basePrice, int quantity);

    // Виртуальный деструктор - фундамент полиморфной иерархии
    virtual ~Product() = default;

    // Геттеры (не изменяют состояние объекта -> const, noexcept)
    [[nodiscard]] std::string_view getSku() const noexcept { return m_sku; }
    [[nodiscard]] std::string_view getName() const noexcept { return m_name; }
    [[nodiscard]] double getBasePrice() const noexcept { return m_basePrice; }
    [[nodiscard]] int getQuantity() const noexcept { return m_quantity; }

    // Бизнес-методы изменения количества
    void increaseQuantity(int count);
    void decreaseQuantity(int count);

    // ЧИСТО ВИРТУАЛЬНЫЙ ИНТЕРФЕЙС
    // 1. Полиморфный расчет общей стоимости партии с учетом специфики категории
    [[nodiscard]] virtual double calculateTotalCost() const = 0;
    
    // 2. Идентификатор типа продукта
    [[nodiscard]] virtual std::string_view getCategoryName() const noexcept = 0;

    // Виртуальная печать карточки товара
    virtual void printInfo() const;
};

} // namespace warehouse::core