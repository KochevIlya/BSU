package org.example;

import com.fasterxml.jackson.core.*;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.BufferedReader;
import java.io.IOException;
import java.sql.SQLOutput;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {

        public static class Exam {
            private int averageMark;
            private String name;


            public void readExam(BufferedReader br) throws IOException {

                String str = br.readLine();
                if (str == null)
                    throw new IOException();
                String regex = "(\\d+)(\\s)(\\w+)";

                Pattern pattern = Pattern.compile(regex);
                Matcher matcher = pattern.matcher(str);

                if (matcher.matches())
                {
                    String s = matcher.group(1);
                    this.averageMark = Integer.parseInt(s);
                    this.name = matcher.group(3);
                }
                else
                {
                    throw new IOException();
                }

            }

            public int getAverageMark() {
                return averageMark;
            }

            public void setAverageMark(int averageMark) {
                this.averageMark = averageMark;
            }

            public void setName(String name) {
                this.name = name;
            }
            public String getName() {
                return name;
            }

            @Override
            public String toString() {
                return name + " " + averageMark + " ";
            }
        }

    public static void main(String[] args) throws JsonProcessingException {
        Exam exam = new Exam();
        exam.setName("Math");
        exam.setAverageMark(7);
        ObjectMapper objectMapper = new ObjectMapper();
        String str = objectMapper.writeValueAsString(exam);
        System.out.println(str);
        Exam exam2 = new Exam();
        ArrayList<Exam> array = new ArrayList<>();
        exam2 = objectMapper.readValue(str, Exam.class);
        System.out.println(exam2.getAverageMark());
        System.out.println(exam2.getName());
        }
}