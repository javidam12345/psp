package ej3;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.EnumMap;
import java.util.HashMap;

public class ClientHandler implements Runnable{

    private final ObjectInputStream objectInputStream;
    private final ObjectOutputStream objectOutputStream;



    public ClientHandler(Socket socket) throws IOException {
        objectInputStream = new ObjectInputStream(socket.getInputStream());
        objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
    }


    @Override
    public void run() {
        try {
            System.out.println("connected");
            Bill bill = (Bill)objectInputStream.readObject();
            double IVA = Server.getIVA(bill.IVAType());
            double total = bill.amount() + ((bill.amount() * IVA) / 100);
            Result result = new Result(IVA, total);
            objectOutputStream.writeObject(result);
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}
