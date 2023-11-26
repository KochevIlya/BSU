package com.example.newyear;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Objects;

public class DBConnector {
    static Connection co;
    static ArrayList<DBFactory> factoryList = new ArrayList<>();
    static int count;
    public static void read() {

            String query = "SELECT * FROM products ORDER BY factoryName ASC";
            try(Statement statement = co.createStatement();
                ResultSet resultSet = statement.executeQuery(query)
            )
            {
                resultSet.next();
                String factoryName = resultSet.getString("factoryName");

                count = 0;
                DBFactory tempFactory = new DBFactory();
                DBGift tempGift = new DBGift();

                tempFactory.giftsAmount = 1;
                tempFactory.name = factoryName;

                tempGift.readGift(resultSet);
                tempFactory.giftsList.add(tempGift);

                while (resultSet.next()) {
                    if(!Objects.equals(factoryName, resultSet.getString("factoryName")))
                    {
                        DBConnector.factoryList.add(tempFactory);
                        DBConnector.count++;
                        tempFactory = new DBFactory();
                        tempFactory.giftsAmount = 0;
                    }
                    tempFactory.giftsAmount++;
                    tempGift = new DBGift();
                    tempGift.readGift(resultSet);
                    tempFactory.giftsList.add(tempGift);
                    factoryName = resultSet.getString("factoryName");
                    tempFactory.name = factoryName;
                }
                DBConnector.factoryList.add(tempFactory);
                DBConnector.count++;
            }
            catch (Exception e) {
                System.out.println("Unrelated problem");
            }
    }
    void connect()
    {
        try
        {
            co = DriverManager.getConnection("jdbc:sqlite:DBProducts.db");
            System.out.println("connected");
        }
        catch(Exception e)
        {
            System.out.println(e.getMessage());
        }
    }
    void close()
    {
        try {
            co.close();
            System.out.println("Closed");
        }
        catch(Exception e)
        {
            System.out.println(e.getMessage());
        }
    }

}
