import org.apache.jena.rdf.model.Model;
import org.apache.jena.rdf.model.ModelFactory;
import org.apache.jena.rdf.model.ResIterator;
import org.apache.jena.rdf.model.Resource;
import org.apache.jena.vocabulary.VCARD;

public class App {
    public static void main(String[] args) throws Exception {
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
    }
}