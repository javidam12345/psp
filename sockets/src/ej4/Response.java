package ej4;

import java.io.Serial;
import java.io.Serializable;

public record Response(boolean hasFound, String message) implements Serializable {
    @Serial
    private static final long serialVersionUID = 1L;
}
