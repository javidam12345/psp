package ej1;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Server implements Runnable{

    private final ExecutorService executorService = Executors.newFixedThreadPool(2);

    @Override
    public void run() {
        try (ServerSocket serverSocket = new ServerSocket(3055)){
            while (true)
            {
                Socket socket =  serverSocket.accept();
                executorService.submit(new ClientHandler(socket));
            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
