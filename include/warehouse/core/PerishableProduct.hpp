#pragma once

#include <warehouse/core/Product.hpp>

namespace warehouse::core 
{

class PerishableProduct : public Product
{
private:
    int m_expiryDays{0}; // Дней до окончания срока годности

public:
    PerishableProduct(std::string_view sku,
                      std::string_view name,
                      double basePrice,
                      int quantity,
                      unsigned minThreshold,
                      int expiryDays);

    [[nodiscard]] int getExpiryDays() const noexcept;

    // Реализация чисто виртуальных контрактов
    [[nodiscard]] std::string_view getCategoryName() const noexcept override;
    [[nodiscard]] double discountFactor() const noexcept override;
        
    // Переопределение вывода
    void printInfo() const override;
};

} // namespace warehouse::core