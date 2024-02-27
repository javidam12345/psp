package ej2.tcp;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class ClientHandler implements Runnable {

    public final ObjectOutputStream objectOutputStream;
    public final ObjectInputStream objectInputStream;

    public ClientHandler(Socket socket) throws IOException {
        System.out.println("New connection! "+socket.getInetAddress());
        objectOutputStream = new ObjectOutputStream(socket.getOutputStream());
        objectInputStream = new ObjectInputStream(socket.getInputStream());
    }

    private static ResultInformation getInformationFromArray(int[] array) {
        int total = 0;
        int biggest = array[0];
        int smallest = array[0];
        for (int j = 0; j < array.length; j++) {
            if (array[j] > biggest) {
                biggest = array[j];
            } else if (array[j] < smallest) {
                smallest = array[j];
            }
            total += array[j];
        }
        return new ResultInformation(total, biggest, smallest);

    }

    @Override
    public void run() {
        try {
            int[] array = (int[]) objectInputStream.readObject();
            ResultInformation resultInformation = getInformationFromArray(array);
            objectOutputStream.writeObject(resultInformation);
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}
