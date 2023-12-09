package com.example.demo;

import java.sql.ResultSet;
import java.sql.SQLException;

public class DBGift {
    String name;
    double cost;
    public void readGift(ResultSet resultSet) throws SQLException {
        String productName = resultSet.getString("productName");
        double productCost = resultSet.getDouble("productCost");
        name = productName;
        cost = productCost;
    }

}
