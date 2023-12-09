import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.ArrayList;


public class Main {
    public static void main(String[] args){
        System.out.println("Введите количество первых чисел Фибоначи (натуральное число от 1 до 200000):");
        InputStreamReader inputStreamReader = new InputStreamReader(System.in);
        BufferedReader bufferedReader = new BufferedReader(inputStreamReader);

        ArrayList<BigInteger> fibonachiList = new ArrayList<>();
        try {
            String inputStr = bufferedReader.readLine();
            BigInteger bigNumbersAmount = new BigInteger(inputStr);
            MyMath myMath = new MyMath();
            fibonachiList = myMath.fibonachiNumbers(bigNumbersAmount);
        }
        catch(TooBigNumber exception)
        {
            System.out.println("Число слишком большое");
            System.exit(0);
        }
        catch(NumberFormatException exception)
        {
            System.out.println("Неверный формат числа.");
            System.exit(0);
        }
        catch(IOException exception)
        {
            System.out.println("Введено неверное число");
            System.exit(0);
        }
        for (BigInteger element : fibonachiList)
        {
            System.out.print(element + " ");
        }

    }
}