package com.example.tablefx;

public class Product {
    String factoryName;
    String productName;
    double price;

    public Product(String factoryName, String productName, double cost)
    {
        this.factoryName = factoryName;
        this.productName = productName;
        this.price = cost;
    }

    public String getFactoryName() {
        return factoryName;
    }

    public void setFactoryName(String factoryName) {
        this.factoryName = factoryName;
    }

    public String getProductName() {
        return productName;
    }

    public void setProductName(String productName) {
        this.productName = productName;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }
}
