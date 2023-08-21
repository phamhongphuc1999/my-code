import org.apache.jena.fuseki.main.FusekiServer;
import org.apache.jena.query.Dataset;
import org.apache.jena.query.DatasetFactory;
import org.apache.jena.query.QueryExecution;
import org.apache.jena.query.QuerySolution;
import org.apache.jena.query.ResultSet;
import org.apache.jena.rdf.model.Resource;
import org.apache.jena.rdfconnection.RDFConnection;

public class FusekiApp {
  public static void connectFuseki(String serviceURI) {
    RDFConnection connection = RDFConnection.connect(serviceURI);
    connection.load("documents/turtle.ttl");
    QueryExecution qExec = connection.query("SELECT DISTINCT ?s { ?s ?p ?o }");
    ResultSet rs = qExec.execSelect();
    while (rs.hasNext()) {
      QuerySolution qs = rs.next();
      Resource subject = qs.getResource("s");
      System.out.println("Subject: " + subject);
    }
    qExec.close();
    connection.close();
  }
  
  public static void createEmbeddedServer() {
    Dataset ds = DatasetFactory.createTxnMem();
    FusekiServer server = FusekiServer.create()
                .port(3333)
                .add("/ds", ds, true)
                .build() ;
    server.start();
    // server.stop();
  }
}