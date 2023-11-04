package com.example.demo;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.text.Text;

public class Controller{

    @FXML
    private Text output;
    private long num1 = 0;
    private String operator = "";
    private boolean start = true;
    private Model model = new Model();

    @FXML
    private void workWithNumbers(ActionEvent event)
    {
        if(start) {
            output.setText("");
            start = false;
        }
        String value = ((Button) event.getSource()).getText();
        output.setText(output.getText()+value);
    }
    @FXML
    private void workWithOperators(ActionEvent event)
    {
        String value = ((Button) event.getSource()).getText();
        if(!"=".equals(value))
        {
            if(!operator.isEmpty()) return;
            operator = value;
            num1 = Long.parseLong(output.getText());
            output.setText("");

        }
        else {
            if(operator.isEmpty()) return;
            output.setText(String.valueOf(model.calculation(num1, Long.parseLong(output.getText()), operator)));
            operator = "";
            start = true;
        }
    }

}