package net.api.connector;

import org.apache.jena.rdfconnection.RDFConnection;

public class FusekiConnector {
  private static FusekiConnector connector;
  public String connectionString;
  public RDFConnection connection; 

  protected FusekiConnector(String connectionString) {
    this.connectionString = connectionString;
    this.connection = RDFConnection.connect(connectionString);
  }

  public static FusekiConnector getInstance(String connectionString) {
    if (connector == null)
      connector = new FusekiConnector(connectionString);
    return connector;
  }

  public static void closeConnection() {
    connector.connection.close();
  }
}
