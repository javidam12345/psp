package ej2;


import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Server {

    private final ExecutorService executorService = Executors.newFixedThreadPool(10);

    public void start() {
        try(ServerSocket server = new ServerSocket(3055)) {
            while (true) {
                Socket socket = server.accept();
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
