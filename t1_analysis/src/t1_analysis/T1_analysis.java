/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package t1_analysis;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.security.InvalidParameterException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *
 * @author lasaro
 */
public class T1_analysis {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        FileReader fr = null;
        try {
            System.out.println("Hello World!");
            Map<String,Pessoa> pessoas = new HashMap<String,Pessoa>();
            String fileName = args[0];

            fr = new FileReader(new File(fileName));
            BufferedReader br = new BufferedReader(fr);
            StringTokenizer st;
            String linha = br.readLine();
            int ln = 0;
            int pxlsPorMetro = 0;
            while (linha != null) {
                linha = linha.toLowerCase();
                if (ln == 0) {
                    pxlsPorMetro = getPixelsPorMetro(linha);
                    System.out.println("Pixels por metro: "+pxlsPorMetro);
                } else {
                    List<CordElement> elms = getElementsFromLine(linha);                    
                    Pessoa p = new Pessoa();
                    p.nome = "Pessoa_"+ln;
                    p.posicoes = elms;
                    pessoas.put(p.nome,p);
                }
                linha = br.readLine();
                ln++;
            }
            br.close();
            
            for (Map.Entry<String, Pessoa> entry : pessoas.entrySet()) {
                String nome = entry.getKey();
                Pessoa pessoa = entry.getValue();
                //System.out.print("["+nome+"]:");
                System.out.println(pessoa);
            }
            
        } catch (FileNotFoundException ex) {
            Logger.getLogger(T1_analysis.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(T1_analysis.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                fr.close();
            } catch (IOException ex) {
                Logger.getLogger(T1_analysis.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    private static List<CordElement> getElementsFromLine(String linha) {
        List<CordElement> elements = new ArrayList<>();
        //count elementos
        String ct = "(?<CNT>\\d*+\\s*+)";
        //elemento da linha
        String el = "(?<CORD>\\((?<X>\\d++),(?<Y>\\d++),(?<T>\\d++)\\))";
        Pattern p = Pattern.compile(ct + el);
        Matcher split = p.matcher(linha);
        while (split.find()) {
            if (split.group("CORD").length() > 0) {
                CordElement ce = new CordElement();
                ce.X = Integer.parseInt(split.group("X"));
                ce.Y = Integer.parseInt(split.group("Y"));
                ce.T = Integer.parseInt(split.group("T"));
                elements.add(ce);
            }
        }

        return elements;
    }

    private static int getPixelsPorMetro(String linha) {
        //pixels por metro :   [0-9]+
        String el = "(?<PXL>\\[(?<D>\\d+)\\])";
        Pattern p = Pattern.compile(el);
        Matcher split = p.matcher(linha);
        while (split.find()) {
            if (split.group("PXL").length() > 0) {
                return Integer.parseInt(split.group("D"));
            }
        }
        throw new InvalidParameterException("A linha não está no formato adequado."); //To change body of generated methods, choose Tools | Templates.
    }

}
