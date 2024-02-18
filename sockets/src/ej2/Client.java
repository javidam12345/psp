package ej2;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Scanner;

public class Client {
    private final ObjectOutputStream objectOutputStream;
    private final ObjectInputStream objectInputStream;
    public Client(String address, int port) throws IOException {
        Socket socket = new Socket(address, port);
        objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
        objectInputStream = new ObjectInputStream(socket.getInputStream());
    }

    public void sendArray() throws IOException {
        Scanner scanner = new Scanner(System.in);
        int ARRAY_SIZE = 10;
        int[] array = new int[ARRAY_SIZE];
        for (int i = 0; i < ARRAY_SIZE; i++) {
            System.out.print("Introduce number " +(i + 1)+ " : ");
            array[i] = Integer.parseInt(scanner.nextLine());
        }
        objectOutputStream.writeObject(array);
    }

    public void readArray() throws IOException, ClassNotFoundException {
        ResultInformation resultInformation = (ResultInformation) objectInputStream.readObject();
        System.out.println(resultInformation);
    }


    public static void main(String[] args) {
        try {
           Client client =  new Client("localhost", 3055);
           client.sendArray();
           client.readArray();
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}
