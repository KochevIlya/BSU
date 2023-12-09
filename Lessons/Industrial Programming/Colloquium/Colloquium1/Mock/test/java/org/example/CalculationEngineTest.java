package org.example;

import org.junit.Before;
import org.junit.Test;
import org.mockito.Mock;
import org.mockito.Mockito;

import static org.mockito.Mockito.*;
import static org.junit.Assert.*;

public class CalculationEngineTest {

    @Mock
    private DBConnection dbConnection;
    @Mock
    private DBGateForCalculations dbGateForCalculations = new DBGateForCalculations(dbConnection);

    private CalculationEngine calculationEngine;

    @Before
    public void setUp() {
        dbConnection = mock(DBConnection.class);
        dbGateForCalculations = mock(DBGateForCalculations.class);
        calculationEngine = new CalculationEngine(dbGateForCalculations);
    }

    @Test
    public void testCalc() {
        when(dbGateForCalculations.retrieveData()).thenReturn(5);
        int result = calculationEngine.calc(2, 3);
        assertEquals(10, result);
    }
    @Test
    public void testProcess() {
        CalculationEngine engine = new CalculationEngine(dbGateForCalculations);
        engine.process();
        Mockito.verify(dbGateForCalculations).updateData(10);
    }
}
