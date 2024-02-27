package ej4;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class Player {

    private final ObjectOutputStream objectOutputStream;
    private final ObjectInputStream objectInputStream;
    public Player(Socket socket) throws IOException {
        objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
        objectInputStream = new ObjectInputStream(socket.getInputStream());
    }

    public long readNumber() throws IOException, ClassNotFoundException {
        return ((Message)objectInputStream.readObject()).number();
    }

    public void sendResponse(Response response) throws IOException {
        objectOutputStream.writeObject(response);
    }

}
