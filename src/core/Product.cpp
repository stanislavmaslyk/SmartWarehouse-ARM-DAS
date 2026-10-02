#include <warehouse/core/Product.hpp>
#include <stdexcept>

namespace warehouse::core {

Product::Product(std::string_view sku, std::string_view name, double basePrice, int quantity, unsigned minThreshold)
    : m_sku(sku), m_name(name), m_basePrice(basePrice), m_quantity(quantity), m_minThreshold(minThreshold)
{
    // Валидация инвариантов класса при создании
    if (m_sku.empty())
        throw std::invalid_argument("Артикул (SKU) не может быть пустым.");
    if (m_name.empty())
        throw std::invalid_argument("Название товара не может быть пустым.");
    if (m_basePrice < 0.0)
        throw std::invalid_argument("Базовая цена не может быть отрицательной.");
    if (m_quantity < 0)
        throw std::invalid_argument("Количество на складе не может быть отрицательным.");
    if (m_minThreshold < 0)
        throw std::invalid_argument("Порог дифицита не может быть отрицательной.");
        
    // m_minThreshold is unsigned, so it can never be negative - no validation needed
}

[[nodiscard]] double Product::baseCost() const noexcept
{
    return m_basePrice;
}

void Product::increaseQuantity(int count) 
{
    if (count <= 0)
        throw std::invalid_argument("Количество для оприходования должно быть больше нуля.");
    m_quantity += count;
}

void Product::decreaseQuantity(int count) 
{
    if (count <= 0)
        throw std::invalid_argument("Количество для списания должно быть больше нуля.");
    if (count > m_quantity)
        // Исключение времени выполнения бизнес-логики
        throw std::runtime_error("Ошибка списания: недостаточно товара на складе.");
    m_quantity -= count;
}

double Product::calculateTotalCost() const
{
    return baseCost() * discountFactor() + insuranceCost();
}

void Product::printInfo() const 
{
    std::cout << "[" << getCategoryName() << "] "
              << "SKU: " << m_sku << " | "
              << "Наименование: " << m_name << " | "
              << "Цена: " << m_basePrice << " руб. | "
              << "Остаток: " << m_quantity << " шт." 
              << "Дифицит: " << getMinThreshold();
}

} // namespace warehouse::core