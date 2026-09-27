#pragma once
#include <unordered_map>
#include <string>
#include "warehouse/core/Product.hpp"
#include <memory>

namespace warehouse::core {

class WarehouseService
{
private:
    std::unordered_map<std::string, std::unique_ptr<Product>> m_stock;

public:
    WarehouseService() = default;
    WarehouseService(const WarehouseService&) = delete;
    WarehouseService& operator=(const WarehouseService&) = delete;
    
    void addProduct(std::unique_ptr<Product> product);
    
    Product* findProduct(std::string_view sku) const noexcept;

    bool removeProduct(std::string_view sku);
};
}




