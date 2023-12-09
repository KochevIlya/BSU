import java.math.BigInteger;
import java.util.ArrayList;


public class MyMath {
    public ArrayList<BigInteger> fibonachiNumbers(BigInteger inputAmount) throws TooBigNumber, NumberFormatException {
        if(inputAmount.compareTo(new BigInteger(Integer.toString(Integer.MAX_VALUE))) > 0)
            throw new TooBigNumber();
        else if(inputAmount.compareTo(new BigInteger(Integer.toString(Integer.MIN_VALUE))) < 0)
            throw new NumberFormatException();

        int amount = inputAmount.intValue();
        ArrayList<BigInteger> fibonachiList = new ArrayList<>();

        if(amount == 0)
            return fibonachiList;
        else if(amount == 1)
        {
            fibonachiList.add(new BigInteger("1"));
            return fibonachiList;
        }
        else
        {
            fibonachiList.add(new BigInteger("1"));
            fibonachiList.add(new BigInteger("1"));
            for(int i = 2; i < amount; i++)
            {
                BigInteger previousNumber = fibonachiList.get(i-1);
                BigInteger prePreviousNumber = fibonachiList.get(i-2);
                BigInteger result = previousNumber.add(prePreviousNumber);
                fibonachiList.add(result);
            }
        }
        return fibonachiList;
    }
}
