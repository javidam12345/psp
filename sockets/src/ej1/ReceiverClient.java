package ej1;

import java.io.IOException;
import java.util.Scanner;

public class ReceiverClient extends Client {


    public ReceiverClient(String address, int port, int id) {
        super(address, port, id);
    }

    public static void main(String[]args) {
        try {
            new ReceiverClient("localhost", 3055,1).behaviour();
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }

    }

    @Override
    public void behaviour() throws IOException, ClassNotFoundException {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Introduce un numero: ");
        int number = Integer.parseInt(scanner.nextLine());
        Information information = new Information(id, 2, number);
        objectOutputStream.writeObject(information);
        Information receivedInformation = (Information) objectInputStream.readObject();
        System.out.println(receivedInformation.number());
    }
}
