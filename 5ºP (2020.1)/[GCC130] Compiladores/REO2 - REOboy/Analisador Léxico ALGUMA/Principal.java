import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Scanner;

public class Principal {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        System.out.print("Nome do arquivo: ");
        String arquivo = in.next();
        InputStream is = new FileInputStream("ALGUMA/"+arquivo);
        InputStreamReader isr = new InputStreamReader(is);

        Lexico lexico = new Lexico(isr);
        try
        {
            Token t = null;
            while ( (t = lexico.nextToken()) != null )
            {
                System.out.println(t.toString());
            }
        }
        catch ( LexicalError e )
        {
            System.err.println("ERRO LÉXICO ( " + e.getMessage() + " ) @ " + e.getPosition());
        }
    }
}



