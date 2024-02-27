package ej2.tcp;

import java.io.Serializable;

public record ResultInformation (int sum, int biggest, int smallest) implements Serializable {

    @Override
    public String toString() {
        return  "Suma : " + sum + "| Biggest: "+ biggest + " | Smallest: "+ smallest;
    }

}
