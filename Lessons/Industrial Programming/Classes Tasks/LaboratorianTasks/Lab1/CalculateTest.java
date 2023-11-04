import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import java.util.stream.Stream;
import static org.junit.jupiter.api.Assertions.*;

//Regex

class CalculateTest {
    double k = 0;
    double x = 0;
    @Test
    @ParameterizedTest
    @MethodSource("parametersProvider")
    void calculation(double k, double x) {
        Calculate calc = new Calculate(k,x);
        double result = calc.Calculation();
        double expectedResult = Math.asin(x);
        System.out.println(expectedResult + " " + result);
        assertTrue(Math.abs(expectedResult - result) < Math.pow(10, -k+1));
    }
    private static Stream<Arguments> parametersProvider() {
        return Stream.of(
                Arguments.of(5, 0.8),
                Arguments.of(15, 0.9),
                Arguments.of(8, -0.999),
                Arguments.of(5, -0.99999999999),
                Arguments.of(2, -0.99999999999)
        );
    }
}