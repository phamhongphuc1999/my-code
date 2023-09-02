package net.api.controller;

import static spark.Spark.get;

import spark.Request;
import spark.Response;
import spark.Route;

public class UserController {
  public static void init(){
    get("/users/:id", new Route() {
      public Object handle(Request request, Response response) {
        String id = request.params("id");
        return  "UserId: " + id;
        }
    });
  }
}
