package ej4;

import java.io.Serial;
import java.io.Serializable;

public record Message (long number) implements Serializable {
    @Serial
    private static final long serialVersionUID = 1L;
}
