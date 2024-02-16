package ej1;

import java.io.Serializable;

public record Information(int sender, int receiver, int number) implements Serializable {
}
