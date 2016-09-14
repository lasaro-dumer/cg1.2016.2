/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package t1_analysis;

import java.util.Map;

/**
 *
 * @author lasaro
 */
public class Person {
    public String name;
    public Map<Integer,CordElement> positions;

    @Override
    public String toString() {
        return name + ", move count: " + positions.size();
    }
}
