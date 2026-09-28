#include <warehouse/core/PerishableProduct.hpp>
#include <stdexcept>

namespace warehouse::core 
{

PerishableProduct::PerishableProduct(std::string_view sku,
                                     std::string_view name,
                                     double basePrice,
                                     int quantity,
                                     unsigned minThreshold,
                                     int expiryDays)
    : Product(sku, name, basePrice, quantity, minThreshold),
      m_expiryDays(expiryDays)
{
    if (m_expiryDays < 0)
        throw std::invalid_argument("Срок годности не может быть отрицательным.");
}

double PerishableProduct::discountFactor() const noexcept
{
    constexpr int DISCOUNT_THRESHOLD_DAYS = 3;
    constexpr double DISCOUNT_MULTIPLIER = 0.5;

    return (m_expiryDays <= DISCOUNT_THRESHOLD_DAYS) ? DISCOUNT_MULTIPLIER : 1.0;
}

[[nodiscard]] int PerishableProduct::getExpiryDays() const noexcept { return m_expiryDays; }

std::string_view PerishableProduct::getCategoryName() const noexcept 
{
    return "Скоропортящийся";
}

void PerishableProduct::printInfo() const 
{
    Product::printInfo();
    std::cout << " | Срок: " << m_expiryDays << " дн."
              << " | Итог партии: " << calculateTotalCost() << " руб.\n";
}

} // namespace warehouse::core