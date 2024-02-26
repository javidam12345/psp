package ej3;

class CuentaBancaria {
    private int saldo = 1000;

    public synchronized void sacarDinero(String nombre, int importe) {
        if (saldo >= importe) {
            saldo -= importe;
            System.out.println(nombre + " sacó de la cuenta " + importe + "€");
        } else {
            System.out.println(nombre + " no puede sacar " + importe + "€ -> NO HAY SALDO SUFICIENTE");
        }
        System.out.println("Saldo actual cuenta= " + saldo + "€");

        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public synchronized void ingresarDinero(String nombre, int importe) {
        saldo += importe;
        System.out.println(nombre + " ingresó en la cuenta " + importe + "€");
        System.out.println("Saldo actual cuenta= " + saldo + "€");

        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

