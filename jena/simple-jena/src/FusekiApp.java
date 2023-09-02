import org.apache.jena.query.QueryExecution;
import org.apache.jena.query.QuerySolution;
import org.apache.jena.query.ResultSet;
import org.apache.jena.rdf.model.RDFNode;
import org.apache.jena.rdfconnection.RDFConnection;

public class FusekiApp {
  public static void ConnectTo() {
    RDFConnection conn = RDFConnection.connect("http://localhost:3030/ds/");
    QueryExecution qExec = conn.query("SELECT * WHERE {\n" + //
        "  ?s ?p ?o.\n" + //
        "}") ;
    ResultSet rs = qExec.execSelect();
    while(rs.hasNext()) {
      QuerySolution qs = rs.next();
      RDFNode subject = qs.get("s");
      RDFNode pred = qs.get("p");
      RDFNode object = qs.get("o");
      System.out.println("Subject: " + subject + " pred: " + pred + " object: " + object);
    }
    qExec.close();
    conn.close();
  }
}
