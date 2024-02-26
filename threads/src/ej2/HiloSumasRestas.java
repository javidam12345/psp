package ej2;

public class HiloSumasRestas implements Runnable {
    private static int numero = 1000; // Ahora es estático
    private final int numVeces;
    private final String operacion;

    public HiloSumasRestas(int numVeces, String operacion) {
        this.numVeces = numVeces;
        this.operacion = operacion;
    }

    public static synchronized void incrementar(int numVeces) {
        numero += numVeces;
    }

    public static synchronized void decrementar(int numVeces) {
        numero -= numVeces;
    }

    @Override
    public void run() {
        if ("+".equals(operacion)) {
            incrementar(numVeces);
        } else if ("-".equals(operacion)) {
            decrementar(numVeces);
        }
    }

    public static int getNumero() {
        return numero;
    }
}

