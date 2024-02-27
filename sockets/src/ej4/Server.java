package ej4;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {

    private final int port;
    private final int numOfPlayers;

    private final Player[]arrayOfPlayers;
    private long secretNumber;

    public Server(int port, int numOfPlayers) {
        this.port = port;
        this.numOfPlayers = numOfPlayers;
        arrayOfPlayers = new Player[numOfPlayers];
        setSecretNumber();
    }

    private void setSecretNumber() {
       secretNumber = ProcessHandle.current().pid();
       System.out.println("Only server can see: "+secretNumber);
    }

    public void notifyAllExcept(int index) throws IOException {
        for (int i = 0; i < arrayOfPlayers.length; i++) {
            if (i == index) continue;
            arrayOfPlayers[i].sendResponse(new Response(true, "You have lost. Player "+ (i + 1)+ " won!"));
        }
    }

    public void checkForNumbers() throws IOException, ClassNotFoundException {
        int i = 0;
        boolean numberHasBeenFound = false;
        while (!numberHasBeenFound)
        {
            long readNumber = arrayOfPlayers[i].readNumber();
            if (readNumber == secretNumber){
                arrayOfPlayers[i].sendResponse(new Response(true,"You found the number!"));
                notifyAllExcept(i);
                numberHasBeenFound = true;
            } else if (readNumber > secretNumber) {
                arrayOfPlayers[i].sendResponse(new Response(false, "The number is smaller!"));
            } else {
                arrayOfPlayers[i].sendResponse(new Response(false, "The number is bigger!"));
            }
            i = (i == numOfPlayers - 1) ? 0 : i + 1;
        }
    }

    public void start() throws IOException, ClassNotFoundException {
        ServerSocket serverSocket = new ServerSocket(port);
        for (int i = 0; i < numOfPlayers; i++){
            arrayOfPlayers[i] = new Player(serverSocket.accept());
            System.out.println("Player  "+ (i + 1) + " has connected");

        }
        System.out.println("Starting game...");
        checkForNumbers();
        serverSocket.close();

    }

    public static void main(String[] args) {
        try {
            new Server(3055, 4).start();
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}
