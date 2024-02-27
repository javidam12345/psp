import java.util.Random;
public class Producer extends Thread {
    private final Deposit deposit;
    private final Random random = new Random();

    public Producer(Deposit deposit) {
        this.deposit = deposit;
    }

    public void run() {
        for (int i = 0; i < Refinery.NUM_OF_LOAD; i++){
            deposit.producerFillsDeposit(generateRandomNumber());
            try {
                sleep(1000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }

    public double generateRandomNumber(){
        return random.nextDouble(Refinery.LITERS_PER_CHARGE_RANDOM_LIMIT) + 1;
    }

}

