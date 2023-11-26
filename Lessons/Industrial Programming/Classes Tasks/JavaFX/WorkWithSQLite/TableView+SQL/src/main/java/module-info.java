module com.example.tablefx {
    requires javafx.controls;
    requires javafx.fxml;

    requires com.dlsc.formsfx;
    requires java.sql;

    opens com.example.tablefx to javafx.fxml;
    exports com.example.tablefx;
}