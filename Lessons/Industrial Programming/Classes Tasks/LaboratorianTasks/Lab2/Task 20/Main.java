import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.*;

public class Main {
    public static void main(String[] args) {
        try {
            int colums = 0;
            int rows = 0;
            int checkNumber = 0;
            int temp = 0;
            int indexTemp = 0;

            FileReader fr = new FileReader("input.txt");
            BufferedReader bf = new BufferedReader(fr);
            String str = bf.readLine();
            String regex = "\\d+";
            Pattern pattern = Pattern.compile(regex);
            Matcher matcher = pattern.matcher(str);
            if (matcher.find()) {
                String match = matcher.group();
                rows = Integer.parseInt(match);
            }
            if (matcher.find()) {
                String match = matcher.group();
                colums = Integer.parseInt(match);
            }
            int[][] Matr = new int[rows][colums];
            for (int i = 0; i < rows; i++)
            {
                str = bf.readLine();
                matcher = pattern.matcher(str);
                for (int j = 0; j < colums; j++) {
                    if (matcher.find()) {
                        String match = matcher.group();
                        Matr[i][j] = Integer.parseInt(match);
                    }
                    if (Matr[i][j] >= temp) {
                        temp = Matr[i][j];
                        if (j > indexTemp) {
                            indexTemp = j;
                        }
                    }
                }
                if (indexTemp < checkNumber)
                {
                    System.out.println("this Matr not match the rule");
                    System.exit(1);
                }
                checkNumber = indexTemp;
                temp = 0;
                indexTemp = 0;
            }
            System.out.println("Matr Match the rule");
        } catch (IOException e) {
            System.out.println("Can not read the file");
        }
    }
}