public class Deposit {
    private double liters;
    private boolean isCharging = false;

    public synchronized double fillTankTruck() {
        while (liters <= 0) {
            try {
                wait();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
        double toReturn = liters;
        liters = 0;
        notifyAll();
        return toReturn;
    }

    public synchronized void producerFillsDeposit(double liters) {
        this.liters = liters;
        System.out.println("Producer fills the tank with " + liters);
        notifyAll();
        try {
            wait();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

    }
}
