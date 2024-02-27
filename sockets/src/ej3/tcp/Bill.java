package ej3.tcp;

import java.io.Serializable;

public record Bill(String billNumber, String date, int amount, IVAType IVAType) implements Serializable {




}
