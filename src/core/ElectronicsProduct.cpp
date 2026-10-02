#include <warehouse/core/ElectronicsProduct.hpp>
#include <stdexcept>

namespace warehouse::core 
{

ElectronicsProduct::ElectronicsProduct(std::string_view sku,
                                       std::string_view name,
                                       double basePrice,
                                       int quantity,
                                       unsigned minThreshold,
                                       int guarantee)
    : Product(sku, name, basePrice, quantity, minThreshold),
      m_guarantee(guarantee)
{
    if (m_guarantee < 0)
        throw std::invalid_argument("Гарантия не может быть отрицательной.");
}

double ElectronicsProduct::insuranceCost() const noexcept
{
    constexpr double INSURANCE_RATE_PER_MONTH = 0.03;
    return baseCost() * INSURANCE_RATE_PER_MONTH * m_guarantee;
}

[[nodiscard]] int ElectronicsProduct::getGuarantee() const noexcept { return m_guarantee; }
[[nodiscard]] std::string_view ElectronicsProduct::getCategoryName() const noexcept { return "Электронный товар"; }

void ElectronicsProduct::printInfo() const
{
    Product::printInfo();
    std::cout << " | Итог партии c учетом страховки(0.03 месяц): " << calculateTotalCost() << " руб.\n"
              << " | Гарантия на продукт: " << m_guarantee << " месяцев. /" << std::endl;
}
}