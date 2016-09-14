/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package t1_analysis;

import java.util.Collections;
import java.util.Comparator;
import java.util.Map;
import java.util.Set;
import java.util.SortedSet;
import java.util.TreeSet;

/**
 *
 * @author lasarod
 */
public class DetectEvents {

    private Map<String, Person> people;
    private int pixelsfactor;
    private double minDistance;

    public DetectEvents(Map<String, Person> people, int pixelsFactor, double minCentimeters) {
        this.people = people;
        this.pixelsfactor = pixelsFactor;
        this.minDistance = pixelsFactor * (minCentimeters / 100.0);
        System.out.println("Minimun distance pixels: " + this.minDistance);
    }

    public void detectEncounters() {
        for (Map.Entry<String, Person> entry : people.entrySet()) {
            String name = entry.getKey();
            Person person = entry.getValue();
            for (Map.Entry<String, Person> entry2 : people.entrySet()) {
                String fellowName = entry2.getKey();
                if (!fellowName.equals(name)) {
                    Person fellow = entry2.getValue();
                    SortedSet<Integer> keySet = new TreeSet<>(person.positions.keySet());
                    for (Integer time : keySet) {
                        if (fellow.positions.get(time) != null) {
                            CordElement p1 = person.positions.get(time);
                            CordElement p2 = fellow.positions.get(time);
                            double distance = Math.sqrt(Math.pow(p2.X - p1.X, 2) + Math.pow(p2.Y - p1.Y, 2));
                            if (distance <= this.minDistance) {
                                System.out.println(name + " move in " + time + " " + p1 + " , and " + fellowName + " too " + p2);
                            }
                        }
                    }
                }
            }
        }
    }

    public String printResults() {
        return "";
    }
}
