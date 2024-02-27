package ej4;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Scanner;

public class Client {

    private final ObjectInputStream objectInputStream;

    private final ObjectOutputStream objectOutputStream;

    public Client(String address, int port) throws IOException {
        Socket socket = new Socket(address, port);
        objectInputStream = new ObjectInputStream(socket.getInputStream());
        objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
    }

    public void start() throws IOException, ClassNotFoundException {
        boolean hasBeenFound = false;
        while(!hasBeenFound) {
            Scanner scanner = new Scanner(System.in);
            System.out.print("Introduce number: ");
            long number = Long.parseLong(scanner.nextLine());
            objectOutputStream.writeObject(new Message(number));
            Response response = (Response) objectInputStream.readObject();
            hasBeenFound = response.hasFound();
            System.out.println(response.message());
        }
    }

    public static void main(String[] args) {
        try {
            new Client("localhost", 3055).start();
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("Socket closed!");
        }
    }
}
