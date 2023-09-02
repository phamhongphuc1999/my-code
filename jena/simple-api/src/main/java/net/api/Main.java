package net.api;

import net.api.connector.FusekiConnector;
import net.api.controller.FusekiController;
import net.api.controller.UserController;

public class Main {
    public static void main(String[] args) {
        FusekiConnector connector = FusekiConnector.getInstance("http://localhost:3030/ds/");
        UserController.init();
        FusekiController.init(connector);
    }
}