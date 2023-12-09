interface ClothesFactory {
    Shirt createShirt();
    Trousers createTrousers();
}
class SummerClothesFactory implements ClothesFactory {
    @Override
    public Shirt createShirt() {
        return new SummerShirt();
    }

    @Override
    public Trousers createTrousers() {
        return new SummerTrousers();
    }
}
class WinterClothesFactory implements ClothesFactory {
    @Override
    public Shirt createShirt() {
        return new WinterShirt();
    }

    @Override
    public Trousers createTrousers() {
        return new WinterTrousers();
    }
}
interface Shirt {
    Object print();
}
class SummerShirt implements Shirt {
    @Override
    public Object print() {
        System.out.println("Летняя Рубашка");
        return null;
    }
}

class WinterShirt implements Shirt {
    @Override
    public Object print() {
        System.out.println("Зимняя Рубашка");
        return null;
    }
}

interface Trousers {
    Object print();
}
class SummerTrousers implements Trousers {
    @Override
    public Object print() {
        System.out.println("Летние брюки");
        return null;
    }
}
class WinterTrousers implements Trousers {
    @Override
    public Object print() {
        System.out.println("Зимние брюки");
        return null;
    }
}

public class Main {
    public static void main(String[] args) {
        ClothesFactory summerFactory = new SummerClothesFactory();

        Shirt summerShirt = summerFactory.createShirt();
        Trousers summerTrousers = summerFactory.createTrousers();

        summerShirt.print();
        summerTrousers.print();

        ClothesFactory winterFactory = new WinterClothesFactory();
        Shirt winterShirt = winterFactory.createShirt();
        Trousers winterTrousers = winterFactory.createTrousers();

        winterShirt.print();
        winterTrousers.print();
    }
}
