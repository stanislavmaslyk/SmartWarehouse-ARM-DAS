#include <warehouse/service/WarehouseService.hpp>

namespace warehouse::service
{
    void WarehouseService::addProduct(std::unique_ptr<warehouse::core::Product> product)
    {
        if(!product) throw std::invalid_argument("Товар не может быть пустым");
        std::string key(product->getSku());
        if(m_stock.contains(key))
            throw std::invalid_argument("Этот товар уже лежит на складе");
        m_stock.emplace(key, std::move(product));
    }
    
    [[nodiscard]] warehouse::core::Product* WarehouseService::findProduct(std::string_view sku) const noexcept
    {

    }

    [[nodiscard]] bool WarehouseService::removeProduct(std::string_view sku)
    {

    }
}