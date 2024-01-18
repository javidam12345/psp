public class Refinery {
    public static final int NUM_OF_TRUCKS = 3;
    public static final int LITERS_PER_CHARGE_RANDOM_LIMIT = 1000;
    public static final int NUM_OF_LOAD = 15;
    public static final int NUM_OF_LOAD_PER_TRUCK = 5;

    private static final Deposit DEPOSIT = new Deposit();

    public static void main(String[] args) {
        Producer producer = new Producer(DEPOSIT);
        producer.start();
        for (int i = 0; i < NUM_OF_TRUCKS; i++)
        {
            Truck truck = new Truck(DEPOSIT, i + 1);
            truck.start();
        }
    }
}
