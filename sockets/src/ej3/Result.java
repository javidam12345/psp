package ej3;

import java.io.Serializable;

public record Result(double IVA, double total) implements Serializable {

    @Override
    public String toString() {
        return "IVA: "+ IVA + " | To pay: "+total;
    }
}
