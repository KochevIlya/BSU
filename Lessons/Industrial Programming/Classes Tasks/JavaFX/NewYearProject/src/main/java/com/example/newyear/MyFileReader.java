package com.example.newyear;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;

public class MyFileReader {
    static ArrayList<Factory> factoryList = new ArrayList<>();
    static int count;
    public static void read(String fileName) throws Exception {
        FileReader fr = new FileReader(fileName);
        BufferedReader br = new BufferedReader(fr);
        String str = br.readLine();
        count = Integer.parseInt(str);

        for(int i = 0; i < count; i++)
        {
            br.readLine();
            Factory factory = new Factory();
            factory.readFactory(br);
            factoryList.add(factory);
        }
    }
}
