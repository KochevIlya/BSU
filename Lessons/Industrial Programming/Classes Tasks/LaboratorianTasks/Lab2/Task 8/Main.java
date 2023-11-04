import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) {
        try{
            int result = 0;
            int amount = 0;
            int preAmount = 0;
            BufferedReader bf = new BufferedReader(new FileReader("input.txt"));
            String line = bf.readLine();
            String[] words = line.split("\\s+");
            int n = Integer.parseInt(words[0]);
            int m = Integer.parseInt(words[1]);
            int [][] Matr = new int[n][m];
            line = bf.readLine();
            words = line.split("\\s+");
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        Matr[i][j] = Integer.parseInt(words[j]);
                    }
                    line = bf.readLine();
                    if (line == null)
                        break;
                    words = line.split("\\s+");
                }

                for (int i = 0; i < n; i++) {
                    int temp = Matr[i][0];
                    for (int j = 1; j < m; j++)
                    {
                        if (Matr[i][j] == temp)
                        {
                            preAmount++;
                            if(preAmount > amount) {
                                amount = preAmount;
                                result = i+1;
                            }
                        }
                        else
                        {
                            if(preAmount > amount) {
                                amount = preAmount;
                                result = i+1;
                            }
                            preAmount = 0;
                            temp = Matr[i][j];
                        }
                    }
                    preAmount = 0;
                }

            FileWriter fw = new FileWriter("output.txt");
            fw.write(String.valueOf(result));
            fw.close();
        }


        catch(IOException e)
        {
            System.out.println("File Not Found");
        }

    }
}