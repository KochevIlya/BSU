package com.example.newyear;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class HelloController {

    @FXML
    private ComboBox<String> manufacturerComboBox;
    @FXML
    private ComboBox<String> giftComboBox;
    @FXML
    private Label costLabel;
    @FXML
    private CheckBox regularCustomerCheckBox;
    private double wholeCost = 0;
    private double kof = 1;
    private int index = 0;
    @FXML
    private void handleCustomer()
    {
        boolean isConcert = regularCustomerCheckBox.isSelected();

        if(isConcert)
        {
            kof = 0.9;
            wholeCost = wholeCost * kof;
        }
        else
        {
            kof = 1;
            wholeCost = wholeCost * 1 / 0.9;
        }
        costLabel.setText(Double.toString(wholeCost));
    }

    public void initialize()
    {
        List<String> factoryNames = new ArrayList<>();
        for(int i = 0; i < DBConnector.factoryList.size(); i++)
            factoryNames.add(DBConnector.factoryList.get(i).name);
        ObservableList<String> factoryNamesList = FXCollections.observableArrayList(factoryNames);
        manufacturerComboBox.setItems(factoryNamesList);
        manufacturerComboBox.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> updateGiftComboBox(newValue));
        giftComboBox.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> updateLabelGift(newValue, oldValue, index));
    }

    private void updateGiftComboBox(String selectedManufacturer)
    {

        List<String> giftsNames = new ArrayList<>();
        int indexNew = 0;
        for(int i = 0; i < DBConnector.count; i++)
        {
            if(Objects.equals(DBConnector.factoryList.get(i).name, selectedManufacturer))
                indexNew = i;
        }
       index = indexNew;

        for(int i = 0; i < DBConnector.factoryList.get(indexNew).giftsAmount; i++)
        {
            giftsNames.add(DBConnector.factoryList.get(indexNew).giftsList.get(i).name);
        }

        ObservableList<String> updatedGiftOptions = FXCollections.observableArrayList(giftsNames);
        giftComboBox.setItems(updatedGiftOptions);
        wholeCost = 0;
        costLabel.setText("0.0");
    }
    private void updateLabelGift(String selectedGift, String oldGift, int newIndex)
    {
        if (wholeCost != 0.0 || selectedGift == null)
        {
            for(int i = 0; i < DBConnector.count; i++)
            {
                if(Objects.equals(DBConnector.factoryList.get(newIndex).giftsList.get(i).name, oldGift))
                    wholeCost -= DBConnector.factoryList.get(newIndex).giftsList.get(i).cost * kof;
            }
        }
        for(int i = 0; i < DBConnector.count; i++)
        {
            if(Objects.equals(DBConnector.factoryList.get(newIndex).giftsList.get(i).name, selectedGift))
                wholeCost += DBConnector.factoryList.get(newIndex).giftsList.get(i).cost * kof;
        }
        costLabel.setText(Double.toString(wholeCost));
    }
}
