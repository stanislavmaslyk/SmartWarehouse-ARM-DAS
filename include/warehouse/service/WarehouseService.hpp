#pragma once
#include <unordered_map>
#include <string>
#include <string_view>
#include <warehouse/core/Product.hpp>
#include <memory>

namespace warehouse::service 
{

class WarehouseService
{
private:
    std::unordered_map<std::string, std::unique_ptr<warehouse::core::Product>> m_stock;

public:
    WarehouseService() = default;
    WarehouseService(WarehouseService&&) noexcept = default;
    WarehouseService& operator=(WarehouseService&&) noexcept = default;
    
    void addProduct(std::unique_ptr<warehouse::core::Product> product);
    
    [[nodiscard]] warehouse::core::Product* findProduct(std::string_view sku) const noexcept;

    [[nodiscard]] bool removeProduct(std::string_view sku);
};

}