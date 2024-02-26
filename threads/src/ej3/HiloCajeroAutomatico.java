package ej3;


public class HiloCajeroAutomatico {
    public static void main(String[] args) {
        CuentaBancaria cuentaCompartida = new CuentaBancaria();

        Thread padre = new HiloSacarDinero(cuentaCompartida, "Padre", 200);
        Thread madre = new HiloSacarDinero(cuentaCompartida, "Madre", 400);
        Thread hijo1 = new HiloIngresarDinero(cuentaCompartida, "Hijo1", 300);
        Thread hijo2 = new HiloSacarDinero(cuentaCompartida, "Hijo2", 800);
        Thread abuelo = new HiloSacarDinero(cuentaCompartida, "Abuelo", 600);

        padre.start();
        madre.start();
        hijo1.start();
        hijo2.start();
        abuelo.start();
    }
}
