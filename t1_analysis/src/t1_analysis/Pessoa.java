/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package t1_analysis;

import java.util.List;

/**
 *
 * @author lasaro
 */
public class Pessoa {
    public String nome;
    public List<CordElement> posicoes;

    @Override
    public String toString() {
        return nome + ", movimentos: " + posicoes.size();
    }
}
