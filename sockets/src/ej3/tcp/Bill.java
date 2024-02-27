package ej3.tcp;

import java.io.Serial;
import java.io.Serializable;

public record Bill(String billNumber, String date, int amount, IVAType IVAType) implements Serializable {

    @Serial
    private static final long serialVersionUID = 1L;



}
