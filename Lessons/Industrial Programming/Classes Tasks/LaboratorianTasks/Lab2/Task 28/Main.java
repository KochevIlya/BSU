import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
    int rows = 0;
    int colums = 0;
try {
    FileReader fr = new FileReader("input.txt");
    BufferedReader bf = new BufferedReader(fr);
    String str = bf.readLine();
    String[] newStr = str.split("\\s+");
    rows = Integer.parseInt(newStr[0]);
    colums = Integer.parseInt(newStr[1]);

    double[][] Matr = new double[rows][colums];
    for(int i = 0; i < rows; i++)
    {
        str = bf.readLine();
        newStr = str.split(" ");
        double mul = 0.0;
        for (int j = 0; j < colums; j++)
        {
            Matr[i][j] = Double.parseDouble(newStr[j]);
            mul += Matr[i][j] * Matr[i][j];
        }
        if (mul != 1.0)
        {
            System.out.println("The Matr is not Scalar");
            System.exit(1);
        }
    }
    for (int i = 0; i < rows; i++)
    {
        double sMull = 0;
        for (int j = i+1; j < rows; j++)
        {
            for( int z = 0; z < colums; z++)
            {
                sMull += Matr[i][z] * Matr[j][z];
            }
            if (sMull != 0)
            {
                System.out.println("The Matrix is not scalar");
                System.exit(1);
            }
        }
    }
    System.out.println("The Matrix is scalar");
}

catch(IOException e)
{
    System.out.println("There are problems with reading/writing data");
    System.exit(1);
}
    }
}
