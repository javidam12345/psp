package ej1;

import javax.xml.crypto.Data;
import java.io.*;
import java.net.Socket;

public class ClientHandler implements Runnable{

    private final Socket socket;

    private final DataInputStream dataInputStream;

    private final DataOutputStream dataOutputStream;

    private final  ObjectOutputStream objectOutputStream;

    private final ObjectInputStream objectInputStream;



    public ClientHandler(Socket socket){
        System.out.println("New client connected "+ socket.getInetAddress());
        this.socket = socket;
        try {
            dataInputStream = new DataInputStream(socket.getInputStream());
            dataOutputStream = new DataOutputStream(socket.getOutputStream());
            objectOutputStream = new ObjectOutputStream(dataOutputStream);
            objectInputStream = new ObjectInputStream(dataInputStream);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }

    private void synchronizeSocket() throws IOException {
        int clientCode = dataInputStream.readInt();
        System.out.println("Syncronized: "+clientCode);
        Server.concurrentHashMap.put(clientCode, this);
    }

    public void sendMessage(Information information)
    {
        try {
            objectOutputStream.writeObject(information);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void run() {
        try {
            synchronizeSocket();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        while (true){
            try {
                Information information = (Information) objectInputStream.readObject();
                ClientHandler clientHandler = Server.concurrentHashMap.get(information.receiver());
                clientHandler.sendMessage(information);
            } catch (IOException | ClassNotFoundException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
