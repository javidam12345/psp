package ej1.tcp;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public abstract class Client {

    public final int id;

    public final ObjectOutputStream objectOutputStream;
    public final ObjectInputStream objectInputStream;

    public final DataOutputStream dataOutputStream;

    public Client (String address, int port, int id) {
        try {
            Socket socket = new Socket(address, port);
            this.id = id;
            objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
            objectInputStream = new ObjectInputStream(socket.getInputStream());
            dataOutputStream = new DataOutputStream(socket.getOutputStream());
            synchronization();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public abstract void behaviour() throws IOException, ClassNotFoundException;


    public void synchronization(){
        try {
            dataOutputStream.writeInt(id);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
