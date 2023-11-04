import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args)
    {
         try{
             FileReader fr = new FileReader("Input.txt");
             BufferedReader br = new BufferedReader(fr);
             String allStr = "";
             String str = br.readLine();
             while(str != null)
             {
                 allStr += str;
                 str = br.readLine();
             }
             String regex = "-?\\d+";
             Pattern pattern = Pattern.compile(regex);
             Matcher matcher = pattern.matcher(allStr);
             long sum = 0;
             while(matcher.find())
             {
                 String number = matcher.group();
                 sum += Integer.parseInt(number);
             }
             System.out.println(sum);
         }
         catch(FileNotFoundException e)
         {
             System.out.println("Can not find Input text");
         }
         catch(IOException e )
         {
             System.out.println("Wrong input");
             System.exit(1);
         }
    }
}
