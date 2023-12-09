package com.example.demo;

import com.vaadin.flow.component.ClickEvent;
import com.vaadin.flow.component.ComponentEventListener;
import com.vaadin.flow.component.button.Button;
import com.vaadin.flow.component.notification.Notification;
import com.vaadin.flow.component.orderedlayout.HorizontalLayout;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.component.textfield.TextArea;
import com.vaadin.flow.component.textfield.TextField;
import com.vaadin.flow.router.Route;

import java.util.*;

@Route("")
public class MainView extends VerticalLayout {
    public MainView() {
        TextArea textInput = new TextArea("Enter your text");
        TextArea resultTextArea = new TextArea("Result after procedure");
        TextField countOfWords = new TextField("Count of words");

        TextArea textInput1 = new TextArea("Enter your text");
        TextArea resultTextArea1 = new TextArea("Result after procedure");
        TextField countOfWords1 = new TextField("Count of words");

        Button button1 = new Button("Take Result");
        Button button = new Button("Take Result");

        Map<String, Integer> firstDictionary = new HashMap<>();
        Map<String, Integer> secondDictionary = new HashMap<>();
        Map<String, Integer> resultMap = new HashMap<>();

        button1.addClickListener((onClickedButton(textInput1, resultTextArea1, countOfWords1, firstDictionary)));
        button.addClickListener(onClickedButton(textInput, resultTextArea, countOfWords, secondDictionary));
        VerticalLayout layout1 = new VerticalLayout(textInput, button, resultTextArea, countOfWords);
        VerticalLayout layout2 = new VerticalLayout(textInput1, button1, resultTextArea1, countOfWords1);

        Button InterceptButton = new Button("Click to Intercept");
        TextArea resultDictionary = new TextArea();
        InterceptButton.addClickListener(foo(firstDictionary, secondDictionary, resultMap, resultDictionary));




        VerticalLayout layout3 = new VerticalLayout(resultDictionary, InterceptButton);

        add(new HorizontalLayout(layout1, layout2, layout3));

    }

    public ComponentEventListener<ClickEvent<Button>> onClickedButton(TextArea textInput, TextArea resultTextArea, TextField countOfWords, Map<String, Integer> list)
    {
        return event -> {
            String[] parStr = textInput.getValue().split("[., !@#$%^&*()_+\\n]");
            list.clear();
            for (String word : parStr) {
                String lowerCaseWord = word.toLowerCase();
                list.put(lowerCaseWord, list.getOrDefault(lowerCaseWord, 0) + 1);
            }
            String sep = ": ";
            StringBuilder resultString = new StringBuilder();
            for (Map.Entry<String, Integer> entry : list.entrySet()) {
                resultString.append(entry.getKey()).append(sep).append(entry.getValue()).append("\n");
            }

            countOfWords.setValue(Integer.toString(list.size()));
            String executable = resultString.toString();
            resultTextArea.setValue(executable);
        };
    }
    public ComponentEventListener<ClickEvent<Button>> foo(Map<String, Integer> firstDictionary, Map<String, Integer> secondDictionary, Map<String, Integer> resultMap, TextArea resultDictionary)
    {
        return event -> {
            for (Map.Entry<String, Integer> entry1 : firstDictionary.entrySet()) {
                for (Map.Entry<String, Integer> entry2 : secondDictionary.entrySet())
                {
                    if(Objects.equals(entry1.getKey(), entry2.getKey()))
                    {
                        resultMap.put(entry1.getKey(), Math.min(entry1.getValue(), entry2.getValue()));
                        System.out.println(entry1.getKey() + " " + entry1.getValue() + "\n");
                    }
                }
            }
            StringBuilder resultString = new StringBuilder();
            String sep = ": ";
            for (Map.Entry<String, Integer> entry : resultMap.entrySet()) {
                resultString.append(entry.getKey()).append(sep).append(entry.getValue()).append("\n");
            }
            String executable = resultString.toString();
            resultDictionary.setValue(executable);
            if(resultMap.isEmpty())
            {
                resultDictionary.setValue("No interceptions");
            }
        };
    }



}
