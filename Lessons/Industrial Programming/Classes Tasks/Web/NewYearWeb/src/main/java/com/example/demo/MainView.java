package com.example.demo;

import com.vaadin.flow.component.Composite;
import com.vaadin.flow.component.Text;
import com.vaadin.flow.component.checkbox.Checkbox;
import com.vaadin.flow.component.combobox.ComboBox;
import com.vaadin.flow.component.orderedlayout.HorizontalLayout;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.component.textfield.*;
import com.vaadin.flow.data.provider.DataProvider;
import com.vaadin.flow.data.provider.ListDataProvider;
import com.vaadin.flow.router.Route;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@Route("/hello")
public class MainView extends VerticalLayout {
    public MainView()
    {
        var checkBox = new Checkbox("Постоянный клиент");
        add(new HorizontalLayout(checkBox));
        var labelFabric = new Text("Производитель");
        var comboBoxFabric = new ComboBox<String>("Выберите производителя");
        add(new HorizontalLayout(labelFabric, comboBoxFabric));
        List<String> items = new ArrayList<>(List.of());

        DBFactory factory = new DBFactory();
        factory.setName("Коммунарка");
    List<DBFactory> allFactories = new ArrayList<>();
    DBFactory factory1 = new DBFactory();
    factory1.setName("Спартак");

    ArrayList<DBGift> list1 = new ArrayList<>();

    DBGift gift1 = new DBGift();
    gift1.cost = 34.0;
    gift1.name = "Кросcовки";

    DBGift gift2 = new DBGift();
    gift2.cost = 55.0;
    gift2.name = "Пушка";

    list1.add(gift1);
    list1.add(gift2);

    factory.giftsAmount = 2;
    factory.giftsList = list1;

        ArrayList<DBGift> list2 = new ArrayList<>();
        DBGift gift3 = new DBGift();
        gift3.cost = 1000.0;
        gift3.name = "Сгущёное молоко";

        DBGift gift4 = new DBGift();
        gift4.cost = 59.0;
        gift4.name = "Батончик Сигма эдишон";
        list2.add(gift3);
        list2.add(gift4);

        factory1.giftsAmount = 2;
        factory1.giftsList = list2;

        items.add(factory.name);
        items.add(factory1.name);
        comboBoxFabric.setItems(items);
        allFactories.add(factory);
        allFactories.add(factory1);
        var labelProducts = new Text("Продукты");
        var comboBoxProducts = new ComboBox<String>("Выберите продукт");




        add(new HorizontalLayout(labelProducts, comboBoxProducts));
        List<String> itemsProduct = Arrays.asList(
                new String("Item 1"),
                new String("Item 2"),
                new String("Item 3")
        );
        comboBoxProducts.setItems(itemsProduct);
        comboBoxProducts.setAutofocus(true);
        List<String> forComboboxSpartak = new ArrayList<>();
        forComboboxSpartak.add(gift1.name);
        forComboboxSpartak.add(gift2.name);
        List<String> forCommunarka = new ArrayList<>();
        forCommunarka.add(gift3.name);
        forCommunarka.add(gift4.name);
        comboBoxFabric.addValueChangeListener(event -> {
            String selectedValue = event.getValue();
            if(selectedValue == "Спартак")
            {
                comboBoxProducts.setItems(forComboboxSpartak);
            }
            else {
                comboBoxProducts.setItems(forCommunarka);
            }

        });


        var labelCost = new Text("Цена за товар");
        var cost = new Text("0");
        double koef = 1;
        add(new HorizontalLayout(labelCost, cost));
        comboBoxProducts.addValueChangeListener(event ->{
            String selectedValue = event.getValue();
            for(int i = 0; i < allFactories.size(); i++)
            {
                for(int j = 0; j < allFactories.get(i).giftsAmount;j++)
                {
                    if (selectedValue == allFactories.get(i).giftsList.get(j).name && checkBox.getValue())
                    {
                        labelCost.setText(Double.toString(allFactories.get(i).giftsList.get(j).cost * 0.9));
                    }
                    else if(selectedValue == allFactories.get(i).giftsList.get(j).name)
                    {
                        labelCost.setText(Double.toString(allFactories.get(i).giftsList.get(j).cost));
                    }
                }
            }
        });
    }
}
