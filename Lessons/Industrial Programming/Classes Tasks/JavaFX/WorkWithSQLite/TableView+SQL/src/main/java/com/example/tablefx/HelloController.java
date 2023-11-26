package com.example.tablefx;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import java.sql.*;

public class HelloController {
    @FXML
    private Label welcomeText;
    @FXML
    private TableView<Product> tableView;
    @FXML
    private TableColumn<Product, String> factoryName;
    @FXML
    private TableColumn<Product, String> productName;
    @FXML
    private TableColumn<Product, String> productPrice;

    public void initialize() throws SQLException {

        Connection connection = DriverManager.getConnection("jdbc:sqlite:DBProducts.db");
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery("SELECT * FROM products");

        ObservableList<Product> products = FXCollections.observableArrayList();
        factoryName = new TableColumn<>("Factory name");
        factoryName.setCellValueFactory(new PropertyValueFactory<>("factoryName"));

        productName = new TableColumn<>("Product Name");
        productName.setCellValueFactory(new PropertyValueFactory<>("productName"));

        productPrice = new TableColumn<>("Price");
        productPrice.setCellValueFactory(new PropertyValueFactory<>("price"));

        tableView.getColumns().add(factoryName);
        tableView.getColumns().add(productName);
        tableView.getColumns().add(productPrice);

        while (resultSet.next()) {

            String factroyName = resultSet.getString("factoryName");
            String name = resultSet.getString("productName");
            double price = resultSet.getDouble("productCost");
            products.add(new Product(factroyName, name, price));
        }
        tableView.setItems(products);

    }

    public void setData(ObservableList<Product> products) {
        tableView.setItems(products);
    }
}