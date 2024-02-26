package ej2;

public class HiloSumasRestasEjecutar {
    public static void main(String[] args) throws InterruptedException {
        Thread hiloSuma1 = new Thread(new HiloSumasRestas(100, "+"));
        Thread hiloResta2 = new Thread(new HiloSumasRestas(100, "-"));
        Thread hiloResta3 = new Thread(new HiloSumasRestas(100, "-"));
        Thread hiloSuma3 = new Thread(new HiloSumasRestas(1, "+"));
        Thread hiloResta4 = new Thread(new HiloSumasRestas(1, "-"));

        hiloSuma1.start();
        hiloResta2.start();
        hiloResta3.start();
        hiloSuma3.start();
        hiloResta4.start();


        hiloSuma1.join();
        hiloResta3.join();
        hiloResta2.join();
        hiloSuma3.join();
        hiloResta4.join();

        System.out.println("El valor final de numero es: " + HiloSumasRestas.getNumero());
    }
}
