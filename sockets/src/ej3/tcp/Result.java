package ej3.tcp;

import java.io.Serial;
import java.io.Serializable;

public record Result(double IVA, double total) implements Serializable {
    @Serial
    private static final long serialVersionUID = 1L;
    @Override
    public String toString() {
        return "IVA: "+ IVA + " | To pay: "+total;
    }
}
