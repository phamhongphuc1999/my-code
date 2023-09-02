package net.api.controller;

import static spark.Spark.get;

import org.apache.jena.query.QueryExecution;
import org.apache.jena.query.QuerySolution;
import org.apache.jena.query.ResultSet;
import org.apache.jena.rdf.model.RDFNode;
import org.apache.jena.rdfconnection.RDFConnection;

import net.api.connector.FusekiConnector;
import spark.Request;
import spark.Response;
import spark.Route;

public class FusekiController {
  public static void init(FusekiConnector connector) {
    RDFConnection conn = connector.connection;
    get("/web-sematic", new Route() {
      public Object handle(Request request, Response response) {
        QueryExecution qExec = conn.query("SELECT * WHERE {\n" + //
        "  ?s ?p ?o.\n" + //
        "}") ;
        ResultSet rs = qExec.execSelect();
        String result = "";
        while(rs.hasNext()) {
          QuerySolution qs = rs.next();
          RDFNode subject = qs.get("s");
          RDFNode pred = qs.get("p");
          RDFNode object = qs.get("o");
          result += subject + " " + pred + " " + object + ";\n";
        }
        qExec.close();
        conn.close();
        return result;
      }
    });
  }
}
