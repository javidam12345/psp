public class Loads {

    private final int numOfLoads;

    public Loads(int numOfLoads){
        this.numOfLoads = numOfLoads;
    }

    public synchronized void incrementLoad()
    {
      //  numOfLoads++;
    }
}
