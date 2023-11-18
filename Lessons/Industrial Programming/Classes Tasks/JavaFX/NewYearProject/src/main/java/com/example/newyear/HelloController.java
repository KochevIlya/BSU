package com.example.newyear;

import javafx.beans.value.ObservableValue;
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
    private CheckBox concertCheckBox;
    @FXML
    private CheckBox regularCustomerCheckBox;
    private double wholeCost = 0;
    private double koef = 1;
    private int index = 0;
    @FXML
    private void handleCustumer()
    {
        boolean isConcert = regularCustomerCheckBox.isSelected();

        if(isConcert)
        {
            koef = 0.9;
            wholeCost = wholeCost * koef;
        }
        else
        {
            koef = 1;
            wholeCost = wholeCost * 1 / 0.9;
        }
        costLabel.setText(Double.toString(wholeCost));
    }

    public void initialize()
    {
        List<String> factoryNames = new ArrayList<>();
        for(int i = 0; i < MyFileReader.factoryList.size(); i++)
        {
            factoryNames.add(MyFileReader.factoryList.get(i).name);
        }
        ObservableList<String> factoryNamesList = FXCollections.observableArrayList(factoryNames);
        manufacturerComboBox.setItems(factoryNamesList);
        manufacturerComboBox.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            updateGiftComboBox(newValue);
        });
        giftComboBox.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            updateLabelGift(newValue, oldValue, index);
        });
    }

    private void updateGiftComboBox(String selectedManufacturer)
    {

        List<String> giftsNames = new ArrayList<>();
        int indexNew = 0;
        for(int i = 0; i < MyFileReader.count; i++)
        {
            if(MyFileReader.factoryList.get(i).name == selectedManufacturer)
                indexNew = i;
        }
       index = indexNew;

        for(int i = 0; i < MyFileReader.factoryList.get(indexNew).giftsAmmount; i++)
        {
            giftsNames.add(MyFileReader.factoryList.get(indexNew).giftsList.get(i).name);
        }

        ObservableList<String> updatedGiftOptions = FXCollections.observableArrayList(giftsNames);
        giftComboBox.setItems(updatedGiftOptions);
        wholeCost = 0;
        costLabel.setText("0.0");
    }
    private void updateLabelGift(String selectedGift, String oldGift, int newIndex)
    {
        System.out.println(wholeCost);
        System.out.println(selectedGift);
        System.out.println(oldGift);

        if (wholeCost != 0.0 || selectedGift == null)
        {
            for(int i = 0; i < MyFileReader.count; i++)
            {
                if(Objects.equals(MyFileReader.factoryList.get(newIndex).giftsList.get(i).name, oldGift))
                    wholeCost -= MyFileReader.factoryList.get(newIndex).giftsList.get(i).cost * koef;
            }
        }
        for(int i = 0; i < MyFileReader.count; i++)
        {
            if(Objects.equals(MyFileReader.factoryList.get(newIndex).giftsList.get(i).name, selectedGift))
                wholeCost += MyFileReader.factoryList.get(newIndex).giftsList.get(i).cost * koef;
        }
        costLabel.setText(Double.toString(wholeCost));
    }
}
