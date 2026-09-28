#pragma once

#include <warehouse/core/Product.hpp>

namespace warehouse::core
{
class ElectronicsProduct : public Product
{
private:
    int m_guarantee{0};

private:
public:
    ElectronicsProduct(std::string_view sku,
                       std::string_view name,
                       double basePrice,
                       int quantity,
                       unsigned minThreshold,
                       int guarantee);
    
    [[nodiscard]] int getGuarantee() const noexcept;
    [[nodiscard]] std::string_view getCategoryName() const noexcept override;
    [[nodiscard]] double insuranceCost() const noexcept override;

    // Переопределение вывода
    void printInfo() const override;
};
}