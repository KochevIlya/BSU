import java.io.*;
import java.util.StringTokenizer;

public class Main {
    public static String consanantLetters = "aoiuye";
    public static void main(String[] args) {
        try {
            BufferedReader bf = new BufferedReader(new FileReader("text.txt"));

            String line, text = "";

            while ((line = bf.readLine()) != null) {
                text = text + line + "\n";
            }
            bf.close();

            System.out.println("Enter a number of letters");
            bf = new BufferedReader(new InputStreamReader(System.in));
            int length = Integer.parseInt(bf.readLine());

            StringTokenizer tokenizer = new StringTokenizer(text);
            String finalText = "";

            while( tokenizer.hasMoreTokens())
            {
                String token = tokenizer.nextToken();
                String tokenInLower = token.toLowerCase();
                char a = tokenInLower.charAt(0);

                if (token.length() == length && !consanantLetters.contains(String.valueOf(a)))
                    continue;
                else
                {
                    finalText = finalText + token + " ";
                }
            }
            System.out.println(finalText);
            System.exit(1);

        }

        catch (NumberFormatException e)
        {
            System.out.println("Number of letters is incorrect");
        }
        catch (FileNotFoundException e)
        {
            System.out.println("File not exists");
            System.exit(2);
        }
        catch (IOException e)
        {
            System.out.println("Can not be parsed to string");
            System.exit(1);
        }
    }
}