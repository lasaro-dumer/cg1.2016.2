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
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.StringTokenizer;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javafx.beans.property.MapProperty;

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
            if(args.length == 0)
                throw new Exception("Please provide a filename");
            Map<String,Person> people = new HashMap<String,Person>();
            String fileName = args[0];

            fr = new FileReader(new File(fileName));
            BufferedReader br = new BufferedReader(fr);
            StringTokenizer st;
            String line = br.readLine();
            int ln = 0;
            int pxlsPerMeter = 0;
            System.out.println("Parsing file...");
            while (line != null) {
                line = line.toLowerCase();
                if (ln == 0) {
                    pxlsPerMeter = getPixelsPerMeter(line);
                    System.out.println("Pixels per meter: "+pxlsPerMeter);
                } else {
                    Map<Integer, CordElement> elms = getElementsFromLine(line);                    
                    Person p = new Person();
                    p.name = "Person_"+ln;
                    p.positions = elms;
                    people.put(p.name,p);
                }
                line = br.readLine();
                ln++;
            }
            br.close();
            System.out.println("Parse complete");
            
            System.out.println("Searching events...");
            DetectEvents detector = new DetectEvents(people, pxlsPerMeter,50);
            detector.detectEncounters();
            String results = detector.printResults();
            
            System.out.println("Events found:");
            System.out.println(results);
            
            System.out.println("People in scene:");
            for (Map.Entry<String, Person> entry : people.entrySet()) {
                String name = entry.getKey();
                Person person = entry.getValue();
                //System.out.print("["+nome+"]:");
                System.out.println(person);
            }            
        } catch (Exception ex) {
            Logger.getLogger(T1_analysis.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                if(fr!=null)
                    fr.close();
            } catch (Exception ex) {
                Logger.getLogger(T1_analysis.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    private static Map<Integer,CordElement> getElementsFromLine(String linha) {
        Map<Integer,CordElement> elements = new HashMap<>();
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
                elements.put(ce.T, ce);
            }
        }
        
        return elements;
    }

    private static int getPixelsPerMeter(String line) {
        //pixels por metro :   [0-9]+
        String el = "(?<PXL>\\[(?<D>\\d+)\\])";
        Pattern p = Pattern.compile(el);
        Matcher split = p.matcher(line);
        while (split.find()) {
            if (split.group("PXL").length() > 0) {
                return Integer.parseInt(split.group("D"));
            }
        }
        throw new InvalidParameterException("The line isn't in an acceptable format."); //To change body of generated methods, choose Tools | Templates.
    }

}
