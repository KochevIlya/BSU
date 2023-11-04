import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
class Calculate
{
    public double k;
    public double x;

    public Calculate(double k, double x)
    {
        this.k = k;
        this.x = x;
    }

    public double Calculation()
    {
        double eps = Math.pow(10, -(2*k));
        double result = x;
        double koef = 3;
        double slog = (x * x * x ) / 6;
        result += slog;
        long count = 0;
        while (Math.abs(slog) >= eps)
        {
            slog = slog * (x * x) * koef * koef / (koef+1) / (koef+2);
            koef += 2;
            result += slog;
            count++;
        }
        System.out.println(count);
        return result;
    }

    @Override
    public String toString() {
        String str = "Your result: \n" + this.Calculation();
        {
            return str;
        }
    }
}



public class Main {
    public static void main(String[] args) {
        double k;
        double x;
        try {
            System.out.println("Enter number k: ");
            InputStreamReader isr = new InputStreamReader(System.in);
            BufferedReader bf = new BufferedReader(isr);
            String str = bf.readLine();
            k = Double.parseDouble(str);
            System.out.println("Enter number x: ");
            isr = new InputStreamReader(System.in);
            bf = new BufferedReader(isr);
            str = bf.readLine();
            x = Double.parseDouble(str);

            Calculate calc = new Calculate(k,x);
            System.out.println(calc);
            System.out.println(Math.asin(x));
        }
        catch(IOException e)
        {
            System.out.println("Entered not an integer");
        }
    }
}
