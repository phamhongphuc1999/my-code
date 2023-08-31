import org.apache.jena.ontology.OntModel;
import org.apache.jena.ontology.OntModelSpec;
import org.apache.jena.rdf.model.InfModel;
import org.apache.jena.rdf.model.Model;
import org.apache.jena.rdf.model.ModelFactory;
import org.apache.jena.rdf.model.Property;
import org.apache.jena.rdf.model.ResIterator;
import org.apache.jena.rdf.model.Resource;
import org.apache.jena.rdf.model.Statement;
import org.apache.jena.rdf.model.StmtIterator;
import org.apache.jena.reasoner.Reasoner;
import org.apache.jena.reasoner.ReasonerRegistry;
import org.apache.jena.riot.RDFDataMgr;
import org.apache.jena.util.PrintUtil;
import org.apache.jena.vocabulary.VCARD;

public class App {
    public static void simpleJena() {
        String URL1 = "http://abc/animal1";
        String URL2 = "http://abc/animal2";

        Model m = ModelFactory.createDefaultModel();

        Resource animal1 = m.createResource(URL1);
        animal1.addProperty(VCARD.FN, "Elephant");

        Resource animal2 = m.createResource(URL2);
        animal2.addProperty(VCARD.FN, "Dog");

        ResIterator i = m.listSubjectsWithProperty(VCARD.FN);
        while (i.hasNext()) {
            System.out.println(i.nextResource().getProperty(VCARD.FN).toString());
        }
        m.write(System.out, "Turtle");
    }

    public static void load() {
        Model m = ModelFactory.createDefaultModel();
        // read into the model.
        m.read("documents/family/family.ttl");
        m.write(System.out, "RDF/XML");
    }
    
    public static void ontology() {
        OntModel m = ModelFactory.createOntologyModel(OntModelSpec.OWL_MEM, null);
        m.read("documents/test/owlDemoSchema.rdf");
        m.write(System.out, "RDF/XML");
    }

    public static void printStatements(Model m, Resource s, Property p, Resource o) {
        for (StmtIterator i = m.listStatements(s, p, o); i.hasNext();) {
            Statement stmt = i.nextStatement();
            System.out.println(" - " + PrintUtil.print(stmt));
        }
    }

    public static void statement() {
        // Model schema = RDFDataMgr.loadModel("documents/test/owlDemoSchema.rdf");
        // Model data = RDFDataMgr.loadModel("documents/test/owlDemoData.rdf");
        Model schema = RDFDataMgr.loadModel("documents/family/family.ttl");
        Model data = RDFDataMgr.loadModel("documents/family/docs.ttl");
        Reasoner reasoner = ReasonerRegistry.getOWLReasoner();
        reasoner = reasoner.bindSchema(schema);
        InfModel infoModel = ModelFactory.createInfModel(reasoner, data);

        Resource nForce = infoModel.getResource("http://semweb.edu.vn/family#john");
        System.out.println("nForce *:");
        printStatements(infoModel, nForce, null, null);
    }
    
    public static void main(String[] args) throws Exception {
        // App.ontology();
        App.statement();
    }
}