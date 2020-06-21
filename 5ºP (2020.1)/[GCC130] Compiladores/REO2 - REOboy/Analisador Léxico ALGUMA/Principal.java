import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class Principal {
    public static void main(String[] args) throws IOException {
        InputStream is = new FileInputStream("ALGUMA/somafibonacci.alguma");
        InputStreamReader isr = new InputStreamReader(is);

        Lexico lexico = new Lexico();
        //...
        lexico.setInput(isr);
        //...
        try
        {
            Token t = null;
            while ( (t = lexico.nextToken()) != null )
            {
                System.out.println(t.getLexeme());
            }
        }
        catch ( LexicalError e )
        {
            System.err.println(e.getMessage() + "e;, em " + e.getPosition());
        }
    }
}