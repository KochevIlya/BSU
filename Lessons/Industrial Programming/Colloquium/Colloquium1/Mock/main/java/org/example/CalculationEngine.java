package org.example;

public class CalculationEngine {
    private final DBGateForCalculations dbGate;

    public CalculationEngine(DBGateForCalculations dbGate) {
        this.dbGate = dbGate;
    }

    public int calc(int a, int b) {
        return dbGate.retrieveData() + a + b;
    }

    public void process() {
        //For checking this method correctly I use parameter
        dbGate.updateData(10);
    }
}
