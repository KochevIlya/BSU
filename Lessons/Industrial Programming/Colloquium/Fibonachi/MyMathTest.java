import org.junit.Test;
import java.math.BigInteger;
import java.util.ArrayList;
import static org.junit.Assert.*;

public class MyMathTest {

    @Test
    public void testFibonacciNumbersFirstSix() throws NullElementsException, TooBigNumber, NumberFormatException {
        MyMath myMath = new MyMath();
        ArrayList<BigInteger> expectedList = new ArrayList<>();
        expectedList.add(new BigInteger("1"));
        expectedList.add(new BigInteger("1"));
        expectedList.add(new BigInteger("2"));
        expectedList.add(new BigInteger("3"));
        expectedList.add(new BigInteger("5"));
        expectedList.add(new BigInteger("8"));

        ArrayList<BigInteger> resultList = myMath.fibonachiNumbers(new BigInteger("6"));

        for (int i = 0; i < expectedList.size(); i++) {
            assertEquals(expectedList.get(i), resultList.get(i));
        }
    }

    @Test
    public void testFibonacciNumbersEmptyList() {
        MyMath myMath = new MyMath();
        try {
            ArrayList<BigInteger> result = myMath.fibonachiNumbers(BigInteger.ZERO);
            assertTrue(result.isEmpty());
        } catch (Exception e) {
            fail("Выброшено исключение");
        }
    }

    @Test
    public void testFibonacciNumbersLargeInput() {
        MyMath myMath = new MyMath();
        try {
            myMath.fibonachiNumbers(new BigInteger("100000"));
        } catch (TooBigNumber e) {
            fail("Число было слишком большое");
        } catch (Exception e) {
            fail("Выброшено исключение");
        }
    }
}
