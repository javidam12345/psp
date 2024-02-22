package ej3;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class Client {


    private final ObjectOutputStream objectOutputStream;
    private final ObjectInputStream objectInputStream;
    public Client(String address, int port) throws IOException {
        Socket socket = new Socket(address, port);
        objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
        objectInputStream = new ObjectInputStream(socket.getInputStream());
    }


    public void start() throws IOException, ClassNotFoundException {
        Bill bill = new Bill("F-2023-01", "25/02/2023", 100, IVAType.ESP);
        objectOutputStream.writeObject(bill);
        Result result = (Result) objectInputStream.readObject();
        System.out.println(result);
    }

    public static void main(String[] args) {
        try {
            new Client("localhost", 3055).start();
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}
