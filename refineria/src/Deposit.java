public class Deposit {
    private double liters;
    private boolean isFull = false;

    public synchronized double fillTankTruck() {
        while (!isFull) {
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                throw new RuntimeException(e);
            }
        }
        double toReturn = liters;
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
