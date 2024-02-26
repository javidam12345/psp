package ej1;

public class HiloParImparEjecutar {
    public static void main(String[] args) {
        Thread hilo1 = new Thread(new HiloParImpar(2), "Hilo yy");
        Thread hilo2 = new Thread(new HiloParImpar(1), "Hilo xx");

        hilo1.start();
        try {
            hilo1.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        hilo2.start();
    }
}
