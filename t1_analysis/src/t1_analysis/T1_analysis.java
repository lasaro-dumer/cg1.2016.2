/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package t1_analysis;

import java.util.ArrayList;
import java.util.List;
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
        System.out.println("Hello World!");
        String linha = "2 (123,345,567)(789,654,321)";
        List<CordElement> elms = getElementsFromLine(linha);
        for (CordElement elm : elms) {
            System.out.println(elm);
        }        
        linha = "97	(950,421,1)(950,421,2)(950,421,3)(950,421,4)(949,419,5)(949,416,6)(947,410,7)(945,410,8)(944,400,9)(941,403,10)(938,394,11)(939,394,12)(935,389,13)(928,387,14)(929,383,15)(926,383,16)(926,385,17)(925,376,18)(925,376,19)(916,372,20)(913,360,21)(907,358,22)(907,356,23)(903,351,24)(901,352,25)(899,349,26)(897,345,27)(897,342,28)(896,340,29)(893,338,30)(893,338,31)(890,333,32)(888,329,33)(886,327,34)(885,322,35)(883,317,36)(881,315,37)(879,310,38)(879,301,39)(877,301,40)(879,296,41)(878,291,42)(874,289,43)(874,289,44)(875,282,45)(873,282,46)(873,280,47)(871,275,48)(872,270,49)(870,268,50)(867,263,51)(865,261,52)(863,256,53)(862,251,54)(860,249,55)(860,244,56)(858,242,57)(857,239,58)(857,235,59)(855,232,60)(853,230,61)(852,228,62)(852,223,63)(850,220,64)(848,218,65)(851,218,66)(851,213,67)(848,211,68)(851,206,69)(851,203,70)(852,198,71)(850,196,72)(850,191,73)(851,189,74)(850,181,75)(848,179,76)(848,176,77)(847,172,78)(845,172,79)(843,169,80)(843,167,81)(843,164,82)(840,162,83)(840,159,84)(838,155,85)(836,152,86)(837,147,87)(833,147,88)(831,142,89)(830,140,90)(827,140,91)(826,135,92)(827,130,93)(823,128,94)(823,128,95)(825,125,96)(821,120,97)";
        elms = getElementsFromLine(linha);
        for (CordElement elm : elms) {
            System.out.println(elm);
        }
    }

    private static List<CordElement> getElementsFromLine(String linha) {
        List<CordElement> elements = new ArrayList<>();
        //count elementos
        String ct = "(?<CNT>\\d*+\\s*+)";
        //elemento da linha
        String el = "(?<CORD>\\((?<X>\\d++),(?<Y>\\d++),(?<T>\\d++)\\))";
        /*
        Paths_D.txt e contém as posições de cada pessoa acompanhada no vídeo no formato (x,y,tempo).
        A coordenada (0,0) no mundo encontra-se no canto superior-esquerdo.
        Bem no início do arquivo Paths_D.txt,
        o dado entre [,] indica o número de pixels que equivale a um metro, quando da conversão de coordenadas de imagens para mundo.
        */
        System.out.println("pattern:    "+ct+el);
        Pattern p = Pattern.compile(ct+el);
        Matcher split = p.matcher(linha);
        //System.out.println("matches:"+split.matches());
        while (split.find()) {            
            if(split.group("CNT").length()>0){
                System.out.println("COUNT: " + split.group("CNT"));
            }
            if(split.group("CORD").length()>0){
                CordElement ce = new CordElement();
                ce.X = Integer.parseInt(split.group("X"));
                ce.Y = Integer.parseInt(split.group("Y"));
                ce.T = Integer.parseInt(split.group("T"));
                elements.add(ce);
            }
        }
        
        return elements;
    }
    
}
