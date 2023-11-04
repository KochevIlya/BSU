package org.example;

public class DBGateForCalculations {
    private DBConnection dbConnection;
    public void setDBConnection(DBConnection dbConnection)
    {
        this.dbConnection = dbConnection;
    }
    public DBGateForCalculations(DBConnection dbConnection) {
        this.dbConnection = dbConnection;
    }

    public int retrieveData() {
        dbConnection.connect();
        dbConnection.disconnect();
        return 5;
    }

    public void updateData(int data) {
        dbConnection.connect();
        return;
    }
}
