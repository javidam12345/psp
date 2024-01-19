public class Truck extends Thread {
    private final Deposit dep;
    private final int truckId;
    private double totalOfLitersObtained;

    public Truck(Deposit dep, int truckId) {
        this.dep = dep;
        this.truckId = truckId;
    }

    public void run() {
        int i = 0;

        while (i < Refinery.NUM_OF_LOAD_PER_TRUCK){
            double receivedLiters = dep.fillTankTruck();
            totalOfLitersObtained += receivedLiters;
            System.out.println("Truck  "+ truckId +" load => "+receivedLiters + " liters");
            i++;
        }

        System.out.println("Truck "+ truckId +" => Total Volume Collected = "+ totalOfLitersObtained +" Loading operation completed!!");
    }
}

