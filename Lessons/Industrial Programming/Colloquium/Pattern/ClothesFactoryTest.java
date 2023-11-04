import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

import static org.junit.Assert.assertEquals;

public class ClothesFactoryTest {

    @Test
    public void testSummerClothesFactory() {
        ClothesFactory summerFactory = new SummerClothesFactory();

        Shirt summerShirt = summerFactory.createShirt();
        Trousers summerTrousers = summerFactory.createTrousers();

        assertEquals("Летняя Рубашка", printShirt(summerShirt));
        assertEquals("Летние брюки", printTrousers(summerTrousers));
    }

    @Test
    public void testWinterClothesFactory() {
        ClothesFactory winterFactory = new WinterClothesFactory();
        Shirt winterShirt = winterFactory.createShirt();
        Trousers winterTrousers = winterFactory.createTrousers();

        assertEquals("Зимняя Рубашка", printShirt(winterShirt));
        assertEquals("Зимние брюки", printTrousers(winterTrousers));
    }

    private String printShirt(Shirt shirt) {
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        PrintStream stream = new PrintStream(outputStream);
        PrintStream oldStream = System.out;
        System.setOut(stream);

        shirt.print();

        System.setOut(oldStream);

        return outputStream.toString().trim();
    }

    private String printTrousers(Trousers trousers) {
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        PrintStream stream = new PrintStream(outputStream);
        PrintStream oldStream = System.out;
        System.setOut(stream);

        trousers.print();

        System.setOut(oldStream);

        return outputStream.toString().trim();
    }
}
