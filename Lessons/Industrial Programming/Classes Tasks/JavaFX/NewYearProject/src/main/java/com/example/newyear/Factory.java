package com.example.newyear;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
public class Factory {
        ArrayList<Gift> giftsList = new ArrayList<>();
        String name;
        int giftsAmmount;

        public void readFactory(BufferedReader br) throws Exception {
            String str = br.readLine();
            String regex = "([\\s\\S]+?)(\\d+)";
            Pattern pattern = Pattern.compile(regex);
            Matcher matcher = pattern.matcher(str);
            if (matcher.find()) {
                name = matcher.group(1);
                giftsAmmount = Integer.parseInt(matcher.group(2));
            } else {
                throw new Exception();
            }
            for (int i = 0; i < giftsAmmount; i++) {
                Gift gift = new Gift();
                gift.readGift(br);
                giftsList.add(gift);
            }
        }

        public class Gift {
            String name;
            int cost;

            public void readGift(BufferedReader br) throws Exception {
                String str = br.readLine();
                String regex = "([\\s\\S]+?)(\\d+)";
                Pattern pattern = Pattern.compile(regex);
                Matcher matcher = pattern.matcher(str);
                if (matcher.find()) {
                    name = matcher.group(1);
                    cost = Integer.parseInt(matcher.group(2));
                } else {
                    throw new Exception();
                }
            }

        }

    }
