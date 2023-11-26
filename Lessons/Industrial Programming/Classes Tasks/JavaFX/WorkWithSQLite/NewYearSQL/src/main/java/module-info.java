module com.example.newyear {
    requires javafx.controls;
    requires javafx.fxml;

    requires com.dlsc.formsfx;
    requires java.sql;

    opens com.example.newyear to javafx.fxml;
    exports com.example.newyear;
}