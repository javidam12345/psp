package ej3;

class HiloSacarDinero extends Thread {
    private CuentaBancaria cuenta;
    private String nombre;
    private int cantidad;

    public HiloSacarDinero(CuentaBancaria micuenta, String nombre, int cantidad) {
        this.cuenta = micuenta;
        this.nombre = nombre;
        this.cantidad = cantidad;
    }

    public void run() {
        cuenta.sacarDinero(nombre, cantidad);
    }
}