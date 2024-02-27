package ej1.tcp;

import java.io.Serializable;

public record Information(int sender, int receiver, int number) implements Serializable {
}
