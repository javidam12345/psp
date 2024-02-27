public class Deposit {
    private double liters;
    private boolean isFull = false;

    public synchronized double fillTankTruck() {
        while (!isFull) {
            try {
                if (Truck.getNumOfLoadsDone() == Refinery.NUM_OF_LOAD) return 0;
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                throw new RuntimeException(e);
            }
        }
        double toReturn = liters;
        Truck.incrementLoads();
        liters = 0;
        isFull = false;
        notifyAll();
        return toReturn;
    }

    public synchronized void producerFillsDeposit(double liters) {
        while (isFull) {
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                throw new RuntimeException(e);
            }
        }
        this.liters = liters;
        System.out.println("Producer fills the tank with " + liters);
        isFull = true;
        notifyAll();
    }
}
// segunda version

/*
public class Deposit {
    private double liters = 0; // Inicializamos la cantidad de litros en el depósito.

    // Método para que el camión cisterna llene su tanque.
    public synchronized double fillTankTruck() {
        // Espera hasta que haya litros suficientes en el depósito.
        while (liters <= 0) {
            try {
                wait(); // Espera a que el productor llene el depósito.
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Restablece el estado de interrupción.
                throw new RuntimeException(e);
            }
        }
        double toReturn = liters; // Toma todos los litros disponibles.
        liters = 0; // Vacía el depósito.
        System.out.println("Tank truck is filled with " + toReturn + " liters.");
        notifyAll(); // Notifica al productor que el depósito está vacío.
        return toReturn;
    }

    // Método para que el productor llene el depósito.
    public synchronized void producerFillsDeposit(double liters) {
        // Espera hasta que el depósito esté vacío para volver a llenarlo.
        while (this.liters > 0) {
            try {
                wait(); // Espera a que un camión cisterna vacíe el depósito.
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt(); // Restablece el estado de interrupción.
                throw new RuntimeException(e);
            }
        }
        this.liters = liters; // Llena el depósito con la cantidad especificada.
        System.out.println("Producer fills the deposit with " + liters + " liters.");
        notifyAll(); // Notifica a los camiones cisterna que hay combustible disponible.
    }
}


 */
/*

public class Almacen {
    private int cantidad; // Cantidad actual de chocolates en el almacén.

    // Método sincronizado para agregar chocolates al almacén (Productor).
    public synchronized void ponerChocolate(int cantidad) throws InterruptedException {
        // Espera si hay una cantidad significativa de chocolates para asegurar que se consuman primero.
        while (this.cantidad + cantidad > 1000) {
            wait();
        }
        this.cantidad += cantidad; // Agrega chocolates al almacén.
        System.out.println("Se agregaron " + cantidad + " chocolates al almacén. Total actual: " + this.cantidad);
        // Notifica a los consumidores que hay chocolates disponibles.
        notifyAll();
    }

    // Método sincronizado para retirar chocolates del almacén (Consumidor).
    public synchronized void tomarChocolate(int cantidad) throws InterruptedException {
        // Espera si no hay suficientes chocolates disponibles para retirar.
        while (this.cantidad < cantidad) {
            wait();
        }
        this.cantidad -= cantidad; // Retira chocolates del almacén.
        System.out.println("Se retiraron " + cantidad + " chocolates del almacén. Total actual: " + this.cantidad);
        // Notifica al productor que puede haber espacio para más chocolates.
        notifyAll();
    }
}

 */
