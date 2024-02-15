package ej1;

import javax.xml.crypto.Data;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

public class Client implements Runnable{


    @Override
    public void run() {
        try (Socket socket = new Socket("localhost", 3055)){
            Scanner scanner = new Scanner(System.in);
            System.out.print("Introduce un numero: ");
            int number = Integer.parseInt(scanner.nextLine());

            DataOutputStream dataOutputStream = new DataOutputStream(socket.getOutputStream());

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
