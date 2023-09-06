import java.util.List;

import org.apache.jena.ontology.OntModel;
import org.apache.jena.ontology.OntModelSpec;
import org.apache.jena.rdf.model.InfModel;
import org.apache.jena.rdf.model.Model;
import org.apache.jena.rdf.model.ModelFactory;
import org.apache.jena.rdf.model.Property;
import org.apache.jena.rdf.model.RDFNode;
import org.apache.jena.rdf.model.ResIterator;
import org.apache.jena.rdf.model.Resource;
import org.apache.jena.rdf.model.Statement;
import org.apache.jena.rdf.model.StmtIterator;
import org.apache.jena.reasoner.Reasoner;
import org.apache.jena.reasoner.ReasonerRegistry;
import org.apache.jena.reasoner.rulesys.GenericRuleReasoner;
import org.apache.jena.reasoner.rulesys.Rule;
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
        m.read("documents/ontology.ttl");
        m.write(System.out, "RDF/XML");
    }

    public static void printStatements(Model m, Resource s, Property p, Resource o) {
        for (StmtIterator i = m.listStatements(s, p, o); i.hasNext();) {
            Statement stmt = i.nextStatement();
            System.out.println(" - " + PrintUtil.print(stmt));
        }
    }

    public static void statement() {
        Model schema = RDFDataMgr.loadModel("documents/driver.ttl");
        Model data = RDFDataMgr.loadModel("documents/driver.ttl");
        Reasoner reasoner = ReasonerRegistry.getOWLReasoner();
        reasoner = reasoner.bindSchema(schema);
        InfModel infoModel = ModelFactory.createInfModel(reasoner, data);

        Resource nForce = infoModel.getResource("http://example.org/NVA");
        System.out.println("nForce *:");
        printStatements(infoModel, nForce, null, null);
    }

    public static void rule() {
        Model rawData = RDFDataMgr.loadModel("documents/rule.ttl");
        String ruleSrc = "@prefix : <http://semweb.edu.vn/rule-demo#> .\n" + //
                "[rule1: (?a :p ?b) (?b :p ?c) -> (?a :p ?c)]";
        List<Rule> rules = Rule.parseRules(ruleSrc);
        Reasoner reasoner = new GenericRuleReasoner(rules);
        InfModel inf = ModelFactory.createInfModel(reasoner, rawData);
        System.out.println("A * * =>");
        Resource nForce = inf.getResource("http://semweb.edu.vn/rule-demo#a");
        StmtIterator list = inf.listStatements(nForce, null, (RDFNode)null);
        while (list.hasNext()) {
            System.out.println(" - " + list.next());
        }
    }
    
    public static void main(String[] args) throws Exception {
        App.rule();
    }
}