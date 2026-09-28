#include <warehouse/core/PerishableProduct.hpp>
#include <stdexcept>

namespace warehouse::core {

PerishableProduct::PerishableProduct(std::string_view sku,
                                     std::string_view name,
                                     double basePrice,
                                     int quantity,
                                     unsigned minThreshold,
                                     int expiryDays)
    : Product(sku, name, basePrice, quantity, minThreshold),
      m_expiryDays(expiryDays)
{
    if (m_expiryDays < 0) {
        throw std::invalid_argument("Срок годности не может быть отрицательным.");
    }
}

double PerishableProduct::calculateTotalCost() const {
    double total = getBasePrice() * getQuantity();

    // Бизнес-правило: если до конца срока <= 3 дней, дисконт 50%
    if (m_expiryDays <= 3) {
        total *= 0.5;
    }
    return total;
}

std::string_view PerishableProduct::getCategoryName() const noexcept {
    return "Скоропортящийся";
}

void PerishableProduct::printInfo() const {
    Product::printInfo();
    std::cout << " | Срок: " << m_expiryDays << " дн."
              << " | Итог партии: " << calculateTotalCost() << " руб.\n";
}

} // namespace warehouse::core