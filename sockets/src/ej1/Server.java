package ej1;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Server {

    private final ExecutorService executorService = Executors.newFixedThreadPool(2);

    public static final ConcurrentHashMap<Integer, ClientHandler> concurrentHashMap = new ConcurrentHashMap<>();


    public void start() {
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

    public static void main(String[] args) {
        new Server().start();
    }
}
